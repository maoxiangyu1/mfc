
// Login.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLogin �Ի���




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


// CLogin ��Ϣ�������

BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	CString s;
	s=_T("File Name=.\\lib\\ADO\\linkDB.udl");
		pDB=new CADODatabase;
		if(!pDB->Open(s))
		{
			AfxMessageBox("���ݿ�����ʧ�ܣ������˳���");
			this->EndDialog(0);
			return TRUE;
		}
		pRs=new CADORecordset(pDB);
	int dwRet = Dongle_Enum(NULL, &nCount);//ö����������
	if (dwRet != DONGLE_SUCCESS && nCount!=1)
	{
		AfxMessageBox("���Ӽ��ܹ�ʧ�ܣ�");
		GetDlgItem(IDLOGIN)->SetWindowTextA("����");
		return TRUE;
	}
	GetDlgItem(IDLOGIN)->SetWindowTextA("���У��");
	pDongleInfo = (DONGLE_INFO *)malloc(sizeof(DONGLE_INFO));
	dwRet = Dongle_Enum(pDongleInfo, &nCount);//��ȡ�������������Ϣ
	//��ȡ���ܹ�HID
	for (int i = 0; i < 8; i++)
	{
		s.Format(_T("%02X"),pDongleInfo->m_HID[i]);
		HID=HID+s;
	}
	if(pDongleInfo->m_UserID==0xFFFFFFFF)    //ҩ���
	{
		UType = 0;
		s.Format("ҩ���ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//�򿪵�1����
		//�����ܹ�����
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("ҩ��ּ��:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("��˾�绰:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("��˾������:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("��˾����:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("��˾���ڵ�:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE;  
	}
	if(pDongleInfo->m_UserID==0x11111111)    //������
	{
		UType = 1;
		s.Format("������ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//�򿪵�1����
		//�����ܹ�����
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("�����̼��:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("��˾�绰:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("��˾������:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("��˾����:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("��˾���ڵ�:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE;  
	}
	if(pDongleInfo->m_UserID==0x22222222)   //��תվ
	{
		UType = 2;
		s.Format("��תվID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//�򿪵�1����
		//�����ܹ�����
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("��תվ���:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("��˾�绰:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("��˾������:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("��˾����:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("��˾���ڵ�:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub));
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);
		return TRUE; 
	}
	if(pDongleInfo->m_UserID==0x33333333)    //ҩ��
	{
		UType = 3;
		s.Format("ҩ   ��ID:\t%s",HID);
		GetDlgItem(IDC_EDIT1)->SetWindowText(s);
		dwRet = Dongle_Open(&hDongle, 0);//�򿪵�1����
		//�����ܹ�����
		dwRet = Dongle_ReadData(hDongle, 0, Uinfo5, sizeof(Uinfo5)); 
			s.Format("ҩ����:\t%s",(char*)Uinfo5);
			GetDlgItem(IDC_EDIT6)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3072, Uinfo4, sizeof(Uinfo4));
			s.Format("��˾�绰:\t%s",(char*)Uinfo4);
			GetDlgItem(IDC_EDIT5)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 3584, Uinfo2, sizeof(Uinfo2));
			s.Format("��˾������:\t%s",(char*)Uinfo2);
			GetDlgItem(IDC_EDIT3)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4096, Uinfo1, sizeof(Uinfo1));
			s.Format("��˾����:\t%s",(char*)Uinfo1);
			GetDlgItem(IDC_EDIT2)->SetWindowText(s);
		dwRet = Dongle_ReadData(hDongle, 4608, Uinfo3, sizeof(Uinfo3));
			s.Format("��˾���ڵ�:\t%s",(char*)Uinfo3);
			GetDlgItem(IDC_EDIT4)->SetWindowText(s);

		dwRet = Dongle_ReadData(hDongle, 5632, UKEY, sizeof(UKEY));
		dwRet = Dongle_ReadData(hDongle, 6656, Rsapub, sizeof(Rsapub)) ;
		dwRet = Dongle_ReadData(hDongle, 6920, Rsapub, sizeof(Rsapub));
		memcpy(&rsaPri,Rsapri,520);
		memcpy(&rsaPub,Rsapub,264);

		
		return TRUE;  
	}
	AfxMessageBox("��ȷ�����������Ϣ��");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLogin::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLogin::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLogin::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Dongle_Close(hDongle);//�رռ�����
	if (NULL != pDongleInfo)
	{
		free(pDongleInfo);
		pDongleInfo = NULL;
	}	

	CDialogEx::OnClose();
}
/* д����
	char s1[4095]="�򿪼��ܹ�ʧ�ܣ�abcd";
	memcpy(Uinfo,s1,sizeof(s1));
	dwRet = Dongle_WriteData(hDongle, 0, Uinfo, 4095);
	//s.Format("%s",(wchar_t*)Uinfo);
	*/

void CLogin::OnBnClickedLogin()
{
	CString s;
	GetDlgItemText(IDLOGIN,s);
	if(s=="����")
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
		//��ȡ���ܹ�UId
		UID=pDongleInfo->m_UserID;
		//��ȡ��½����UKEY   //��Կ����
		int nInDataLen = 128;
		int nOutDataLen = (128-11);
		Dongle_RsaPub(hDongle, FLAG_DECODE, &rsaPub, UKEY, nInDataLen, UKEY, &nOutDataLen);
		char*UKey=(char*)UKEY;
		if(UType==0)
		{
			if(Dongle_VerifyPIN(hDongle,FLAG_ADMINPIN,UKey,pRemain)==DONGLE_SUCCESS)
			{
				AfxMessageBox("��½�ɹ���");
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
				AfxMessageBox("�����֤ʧ�ܣ�");
				return;
			}
			
		}
		//�������ݿ����
		s.Format("select * from Firm where FID = '%s'",HID);
		pRs->Open(_bstr_t(s),1);
		UINT total= pRs->GetRecordCount();
		if (total == 1 && Dongle_VerifyPIN(hDongle,FLAG_USERPIN,UKey,pRemain)==DONGLE_SUCCESS)
		{
			AfxMessageBox("��½�ɹ���");
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
				AfxMessageBox("�޷�ʶ��������ݣ�");
				break;
			}	
			this->EndDialog(0);
			return;
		}
		else
		{
			AfxMessageBox("��½ʧ�ܣ�");
			return;
		}
	}
}
