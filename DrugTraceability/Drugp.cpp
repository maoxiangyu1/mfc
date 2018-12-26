// Drugp.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugp.h"
#include "afxdialogex.h"
#include <iostream>
// CDrugp 对话框

IMPLEMENT_DYNAMIC(CDrugp, CDialogEx)

CDrugp::CDrugp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugp::IDD, pParent)
	, m_Dname(_T(""))
{

	EnableAutomation();

	m_did = _T("");
	m_Dname = _T("");
	//  m_Ip = _T("");
	//  m_Ip = 0.0f;
	//  m_Op = 0.0f;
	//  m_Ip = _T("");
	//  m_Op = _T("");
	m_Ip = 0.0f;
	m_Op = 0.0f;
}

CDrugp::~CDrugp()
{
}

void CDrugp::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbox);
	DDX_CBString(pDX, IDC_COMBO1, m_did);
	//  DDX_Text(pDX, IDC_EDIT3, m_Dname);
	DDX_Text(pDX, IDC_EDIT1, m_Dname);
	//  DDX_Text(pDX, IDC_EDIT3, m_Ip);
	//  DDX_Text(pDX, IDC_EDIT3, m_Ip);
	//  DDX_Text(pDX, IDC_EDIT4, m_Op);
	//  DDX_Text(pDX, IDC_EDIT3, m_Ip);
	//  DDX_Text(pDX, IDC_EDIT4, m_Op);
	DDX_Text(pDX, IDC_EDIT3, m_Ip);
	DDV_MinMaxFloat(pDX, m_Ip, 0, 3.4E38);
	DDX_Text(pDX, IDC_EDIT4, m_Op);
	DDV_MinMaxFloat(pDX, m_Op, 0, 3.4E38);
}


BEGIN_MESSAGE_MAP(CDrugp, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CDrugp::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CDrugp::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDrugp::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugp, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugp 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {164D4D2B-F742-4CE0-9E52-C9E88939AB8D}
static const IID IID_IDrugp =
{ 0x164D4D2B, 0xF742, 0x4CE0, { 0x9E, 0x52, 0xC9, 0xE8, 0x89, 0x39, 0xAB, 0x8D } };

BEGIN_INTERFACE_MAP(CDrugp, CDialogEx)
	INTERFACE_PART(CDrugp, IID_IDrugp, Dispatch)
END_INTERFACE_MAP()


// CDrugp 消息处理程序


BOOL CDrugp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	if(m_Producer!=NULL)
	{
		this->SetWindowTextA("药品生产");
		pDB=m_Producer->m_login->pDB;
		pRs=m_Producer->m_login->pRs;
		HID=m_Producer->m_login->HID;
	}
	if(m_Transfer!=NULL)
	{
		this->SetWindowTextA("药品中转");
		pDB=m_Transfer->m_login->pDB;
		pRs=m_Transfer->m_login->pRs;
		HID=m_Transfer->m_login->HID;
	}
	if(m_Drugstore!=NULL)
	{
		this->SetWindowTextA("药品出售");
		pDB=m_Drugstore->m_login->pDB;
		pRs=m_Drugstore->m_login->pRs;
		HID=m_Drugstore->m_login->HID;
	}
	m_WriteIC.Set_port(0,254,1);
	if (0 != m_WriteIC.Detect_Fkj())
	{
		AfxMessageBox(_T("未检测到发卡机!"));
		this->EndDialog(1);
	}
	m_WriteIC.Beep(200);
	CString strsql;
	strsql.Format("SELECT * FROM DAuthorization where FID='%s'",HID);
	pRs->Open(_bstr_t(strsql),1);
	if(!pRs->GetRecordCount())
	{
		return TRUE;
	}
	
	pRs->MoveFirst();
    CString DID;
	int indexofList=0;
	while( !(pRs->IsEOF()) )
	{
		pRs->GetFieldValue("DID",DID);
		m_cbox.AddString(DID);
		pRs->MoveNext();
	}
	pRs->MoveFirst();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDrugp::OnBnClickedOk()
{
	char ickey[]={0xff,0xff,0xff,0xff,0xff,0xff};
	UpdateData(true);
	if(m_Ip==NULL||m_Op==NULL||m_Dname=="")
	{
		AfxMessageBox("请填写完整信息！");
		return;
	}
	GetDlgItem(IDC_STATIC23)->SetWindowText("开始连接ic卡");
	int CardType=-1;
	int again=1;
a:	if ( 0 == m_WriteIC.RFRequest(0,&CardType))
	{
		if (CardType != 4)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText(_T("不是M1卡!"));
			return ;
		}

		if (0 != m_WriteIC.RFAnticoll(0,&snr))
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText(_T("读卡号失败!"));
			return ;
		}
	}
	else
	{
		if (again == 1)
		{
			again--;
			goto a;
		}
		else
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText(_T("无IC卡！"));
			return;
		}
	}
	GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入药品信息，请勿移动IC卡！");
	//写入信息
	p.inp=m_Ip;
	p.outp=m_Op;
	CString m_Time;
	CTime t=CTime::GetCurrentTime();
	m_Time = t.Format("%Y%m%d");
	for(int i=0;i<8;i++)
	{
		p.date[i]=m_Time[i];
	}
	char buffer[16];
	memcpy(buffer,&p,sizeof(buffer));
	//======
	CString step,s;
	unsigned long sn=0;
	if(m_Producer!=NULL)
	{
		step="1";
		if(!(m_WriteIC.RFWriteA(snr,1 ,(LPSTR)(LPCTSTR)step,ickey)==0
			&&m_WriteIC.RFWriteA(snr,1*4 ,(LPSTR)(LPCTSTR)HID,ickey)==0
			&&m_WriteIC.RFWriteA(snr,1*4+1 ,(LPSTR)(LPCTSTR)m_did,ickey)==0
			&&m_WriteIC.RFWriteA(snr,1*4+2 ,buffer,ickey)==0))
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("写入IC信息失败！");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
		s.Format("insert into Transfer values('%s','%s','%f','%f','%s')",HID,m_did,m_Ip,m_Op,m_Time);
		if(pDB->Execute(s)==TRUE)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入成功！");
			return;
		}
		else
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入失败！");
			return;
		}
	}
	else
	{
		CString check;
		m_WriteIC.RFReadA(sn,1*4+1 ,(LPSTR)(LPCTSTR)check,ickey);
		if(check!=m_did)
		{
			AfxMessageBox("中转信息与IC卡内信息不一致！写入失败");
			return;
		}
		m_WriteIC.RFReadA(sn,1 ,(LPSTR)(LPCTSTR)step,ickey);
		if((_ttoi(step)+1)>15)
		{
			AfxMessageBox("该药品超过可中转上限！写入失败！");
			return;
		}
		step.Format("%d",(_ttoi(step)+1));
		
		if(!(m_WriteIC.RFWriteA(snr,1 ,(LPSTR)(LPCTSTR)step,ickey)==0
			&&m_WriteIC.RFWriteA(snr,(_ttoi(step))*4 ,(LPSTR)(LPCTSTR)(HID),ickey)==0
			&&m_WriteIC.RFWriteA(snr,(_ttoi(step))*4+1 ,(LPSTR)(LPCTSTR)m_did,ickey)==0
			&&m_WriteIC.RFWriteA(snr,(_ttoi(step))*4+2 ,buffer,ickey)==0))
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("写入IC信息失败！");
			return;
		}
		GetDlgItem(IDC_STATIC23)->SetWindowText("开始写入数据库信息！");
		s.Format("insert into Transfer values('%s','%s','%f','%f','%s')",HID,m_did,m_Ip,m_Op,m_Time);
		if(pDB->Execute(s)==TRUE)
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入成功！");
			return;
		}
		else
		{
			GetDlgItem(IDC_STATIC23)->SetWindowText("数据库写入失败！");
			return;
		}
		
	}
	
}

void CDrugp::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	CString strsql;
	strsql.Format("SELECT * FROM Drug where DID='%s'",m_did);
	pRs->Open(_bstr_t(strsql),1);
	if(!pRs->GetRecordCount())
	{
		AfxMessageBox("无法获取药品信息！");
		return;
	}
	pRs->MoveFirst();
	pRs->GetFieldValue("Dname",m_Dname);
	UpdateData(false);
	return;
}
