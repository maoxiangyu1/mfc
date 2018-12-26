// Drugregister.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugregister.h"
#include "afxdialogex.h"


// CDrugregister 对话框

IMPLEMENT_DYNAMIC(CDrugregister, CDialogEx)

CDrugregister::CDrugregister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugregister::IDD, pParent)
{

	EnableAutomation();

	m_DID = _T("");
	m_Dname = _T("");
	m_Dinfo = _T("");
}

CDrugregister::~CDrugregister()
{
}

void CDrugregister::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugregister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DID);
	DDX_Text(pDX, IDC_EDIT2, m_Dname);
	DDX_Text(pDX, IDC_EDIT3, m_Dinfo);
}


BEGIN_MESSAGE_MAP(CDrugregister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDrugregister::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugregister, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugregister 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {876C82D0-D5C2-434B-A0B7-6D8DCFB37452}
static const IID IID_IDrugregister =
{ 0x876C82D0, 0xD5C2, 0x434B, { 0xA0, 0xB7, 0x6D, 0x8D, 0xCF, 0xB3, 0x74, 0x52 } };

BEGIN_INTERFACE_MAP(CDrugregister, CDialogEx)
	INTERFACE_PART(CDrugregister, IID_IDrugregister, Dispatch)
END_INTERFACE_MAP()


// CDrugregister 消息处理程序


void CDrugregister::OnBnClickedOk()
{
	UpdateData(true);
	if(m_DID==""||m_Dname==""||m_Dinfo=="")
	{
		AfxMessageBox("药品信息不能为空！");
		return;
	}
	CString s;
	s.Format("insert into Drug values('%s','%s','%s')",m_DID,m_Dname,m_Dinfo);
	if(m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("注册成功！");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("注册失败！");
		return;
	}
}
