
// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Login.h"
#include "afxdialogex.h"
#include "ProducerDlg.h"
#include "TransferDlg.h"
#include "DrugstoreDlg.h"
#include "Admin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogin 对话框




CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDLOGIN, &CLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CLogin 消息处理程序

BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	CString s;
	s=_T("File Name=.\\lib\\ADO\\linkDB.udl");
		pDB=new CADODatabase;
		if(!pDB->Open(s))
		{
			AfxMessageBox("数据库链接失败！单击退出！");
			this->EndDialog(0);
			return TRUE;
		}
		pRs=new CADORecordset(pDB);
	int dwRet = Dongle_Enum(NULL, &nCount);//枚举锁的数量
	if (dwRet != DONGLE_SUCCESS && nCount!=1)
	{
		AfxMessageBox("连接加密狗失败！");
		GetDlgItem(IDLOGIN)->SetWindowTextA("重试");
		return TRUE;
	}
	GetDlgItem(IDLOGIN)->SetWindowTextA("身份校验");
	pDongleInfo = (DONGLE_INFO *)malloc(sizeof(DONGLE_INFO));
	dwRet = Dongle_Enum(pDongleInfo, &nCount);//获取加密锁的相关信息
	//获取加密狗HID
	for (int i = 0; i < 8; i++)
	{
		s.Format(_T("%02X"),pDongleInfo->m_HID[i]);
		HID=HID+s;
	}
	if(pDongleInfo->m_UserID==0xFFFFFFFF)    //药监局
	{
		UType = 0;
		s.Format("药监局ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//打开第1把锁
		//读加密狗数据
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("药监局简介:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("公司电话:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("公司负责人:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("公司名称:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("公司所在地:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE;  
	}
	if(pDongleInfo->m_UserID==0x11111111)    //生产商
	{
		UType = 1;
		s.Format("生产商ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//打开第1把锁
		//读加密狗数据
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("生产商简介:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("公司电话:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("公司负责人:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("公司名称:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("公司所在地:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE;  
	}
	if(pDongleInfo->m_UserID==0x22222222)   //中转站
	{
		UType = 2;
		s.Format("中转站ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//打开第1把锁
		//读加密狗数据
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("中转站简介:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("公司电话:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("公司负责人:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("公司名称:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("公司所在地:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE; 
	}
	if(pDongleInfo->m_UserID==0x33333333)    //药店
	{
		UType = 3;
		s.Format("药   店ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//打开第1把锁
		//读加密狗数据
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("药店简介:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("公司电话:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("公司负责人:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("公司名称:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("公司所在地:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub)) ;
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);

		
		return TRUE;  
	}
	AfxMessageBox("无确定您的身份信息！");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogin::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLogin::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLogin::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLogin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Dongle_Close(hDongle);//关闭加密锁
	if (NULL != pDongleInfo)
	{
		free(pDongleInfo);
		pDongleInfo = NULL;
	}	

	CDialogEx::OnClose();
}
/* 写数据
	char s1[4095]="打开加密狗失败！abcd";
	memcpy(Uinfo,s1,sizeof(s1));
	dwRet = Dongle_WriteData(hDongle, 0, Uinfo, 4095);
	//s.Format("%s",(wchar_t*)Uinfo);
	*/

void CLogin::OnBnClickedLogin()
{
	CString s;
	GetDlgItemText(IDLOGIN,s);
	if(s=="重试")
	{
		OnInitDialog();
		UpdateWindow();
		return;
	}
	else
	{
		
		unsigned long UID;
		
		pRemain=(int*)malloc(sizeof(int));
		*pRemain=255;
		//获取加密狗UId
		UID=pDongleInfo->m_UserID;
		//获取登陆密码UKEY   //公钥解密
		int nInDataLen = 128;
		int nOutDataLen = (128-11);
		Dongle_RsaPub(hDongle, FLAG_DECODE, &rsaPub, UKEY, nInDataLen, UKEY, &nOutDataLen);
		char*UKey=(char*)UKEY;
		if(UType==0)
		{
			if(Dongle_VerifyPIN(hDongle,FLAG_ADMINPIN,UKey,pRemain)==DONGLE_SUCCESS)
			{
				AfxMessageBox("登陆成功！");
				this->ShowWindow(SW_HIDE);
				CAdmin dlg;
				dlg.m_login=this;
				if(dlg.DoModal()!=0)
				{
					this->EndDialog(0);
				}
				this->ShowWindow(SW_SHOW);
				return;
			}
			else
			{
				AfxMessageBox("身份验证失败！");
				return;
			}
			
		}
		//检验数据库身份
		s.Format("select * from Firm where FID = '%s'",HID);
		pRs->Open(_bstr_t(s),1);
		UINT total= pRs->GetRecordCount();
		if (total == 1 && Dongle_VerifyPIN(hDongle,FLAG_USERPIN,UKey,pRemain)==DONGLE_SUCCESS)
		{
			AfxMessageBox("登陆成功！");
			this->ShowWindow(SW_HIDE);
			switch(UType)
			{
			case 1:
				{
					CProducer Dlg1;
					Dlg1.m_login=this;
					Dlg1.DoModal();
					break;
				}
			case 2:
				{
					CTransfer Dlg2;
					Dlg2.m_login=this;
					Dlg2.DoModal();
					break;
				}
			case 3:
				{
					CDrugstore Dlg3;
					Dlg3.m_login=this;
					Dlg3.DoModal();
					break;
				}
			default:
				AfxMessageBox("无法识别您的身份！");
				break;
			}	
			this->EndDialog(0);
			return;
		}
		else
		{
			AfxMessageBox("登陆失败！");
			return;
		}
	}
}
