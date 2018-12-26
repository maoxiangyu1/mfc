// Drugchange.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugchange.h"
#include "afxdialogex.h"


// CDrugchange 对话框

IMPLEMENT_DYNAMIC(CDrugchange, CDialogEx)

CDrugchange::CDrugchange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugchange::IDD, pParent)
{

	EnableAutomation();

	m_did = _T("");
	m_dname = _T("");
	m_dinfo = _T("");
}

CDrugchange::~CDrugchange()
{
}

void CDrugchange::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugchange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_did);
	DDX_Text(pDX, IDC_EDIT2, m_dname);
	DDX_Text(pDX, IDC_EDIT3, m_dinfo);
}


BEGIN_MESSAGE_MAP(CDrugchange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDrugchange::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugchange, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugchange 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {4172FE89-F734-4094-84AC-C3F656CEF32C}
static const IID IID_IDrugchange =
{ 0x4172FE89, 0xF734, 0x4094, { 0x84, 0xAC, 0xC3, 0xF6, 0x56, 0xCE, 0xF3, 0x2C } };

BEGIN_INTERFACE_MAP(CDrugchange, CDialogEx)
	INTERFACE_PART(CDrugchange, IID_IDrugchange, Dispatch)
END_INTERFACE_MAP()


// CDrugchange 消息处理程序


void CDrugchange::OnBnClickedOk()
{
	UpdateData(true);
	CString s;
	s.Format("update dbo.Drug set DID='%s',Dname='%s',Dinfo='%s' where DID='%s'",m_did,m_dname,m_dinfo,m_drugsearch->m_DID);
	if(m_drugsearch->m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("更改成功！");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("更改失败！");
		return;
	}
}


BOOL CDrugchange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_did=m_drugsearch->m_DID;
	m_dname=m_drugsearch->m_Dname;
	m_dinfo=m_drugsearch->m_Dinfo;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
