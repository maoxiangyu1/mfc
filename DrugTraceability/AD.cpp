// AD.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "AD.h"
#include "afxdialogex.h"


// CAD 对话框

IMPLEMENT_DYNAMIC(CAD, CDialogEx)

CAD::CAD(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAD::IDD, pParent)
{

	EnableAutomation();

	m_time = _T("");
	m_FID = _T("");
	m_DID = _T("");
	m_Fname = _T("");
	m_Dname = _T("");
}

CAD::~CAD()
{
}

void CAD::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CAD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbox1);
	DDX_Control(pDX, IDC_COMBO2, m_cbox2);
	DDX_Text(pDX, IDC_EDIT1, m_time);
	DDX_CBString(pDX, IDC_COMBO1, m_FID);
	DDX_CBString(pDX, IDC_COMBO2, m_DID);
	DDX_Text(pDX, IDC_EDIT3, m_Fname);
	DDX_Text(pDX, IDC_EDIT2, m_Dname);
}


BEGIN_MESSAGE_MAP(CAD, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAD::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAD::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CAD::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAD, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IAD 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {55984657-AE8A-4370-81E6-C66F56DC78B5}
static const IID IID_IAD =
{ 0x55984657, 0xAE8A, 0x4370, { 0x81, 0xE6, 0xC6, 0x6F, 0x56, 0xDC, 0x78, 0xB5 } };

BEGIN_INTERFACE_MAP(CAD, CDialogEx)
	INTERFACE_PART(CAD, IID_IAD, Dispatch)
END_INTERFACE_MAP()


// CAD 消息处理程序


BOOL CAD::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	pDB=m_admin->m_login->pDB;
	pRs=m_admin->m_login->pRs;
	CString DID,FID;
	CString strsql;
	//公司ID
	strsql.Format("SELECT * FROM Firm");
	pRs->Open(_bstr_t(strsql),1);
	if(!pRs->GetRecordCount())
	{
		return TRUE;
	}
	
	pRs->MoveFirst();
	int indexofList=0;
	while( !(pRs->IsEOF()) )
	{
		pRs->GetFieldValue("FID",FID);
		m_cbox1.AddString(FID);
		pRs->MoveNext();
	}
	pRs->MoveFirst();
	//药品ID
	strsql.Format("SELECT * FROM Drug");
	pRs->Open(_bstr_t(strsql),1);
	if(!pRs->GetRecordCount())
	{
		return TRUE;
	}
	
	pRs->MoveFirst();
	indexofList=0;
	while( !(pRs->IsEOF()) )
	{
		pRs->GetFieldValue("DID",DID);
		m_cbox2.AddString(DID);
		pRs->MoveNext();
	}
	pRs->MoveFirst();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAD::OnBnClickedOk()
{
	UpdateData(true);
	if(m_FID==""||m_DID==""||m_time==""||m_Fname==""||m_Dname=="")
	{

		AfxMessageBox("请填写完整信息!");
		return;
	}
	CString s;
	CString m_Time;
	CTime t=CTime::GetCurrentTime();
	m_Time = t.Format("%Y-%m-%d");
	s.Format("insert into DAuthorization values('%s','%s','%s','%s')",m_FID,m_DID,m_time,m_Time);
	if(pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("授权成功！");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("授权失败！");
		return;
	}
	//CDialogEx::OnOK();
}


void CAD::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	CString strsql;
	strsql.Format("SELECT * FROM firm where FID='%s'",m_FID);
	pRs->Open(_bstr_t(strsql),1);
	if(!pRs->GetRecordCount())
	{
		AfxMessageBox("无法获取公司信息！");
		return;
	}
	pRs->MoveFirst();
	pRs->GetFieldValue("Fname",m_Fname);
	UpdateData(false);
	return;
}


void CAD::OnCbnSelchangeCombo2()
{
	UpdateData(true);
	CString strsql;
	strsql.Format("SELECT * FROM Drug where DID='%s'",m_DID);
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
