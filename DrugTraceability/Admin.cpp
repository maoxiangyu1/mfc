// Admin.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Admin.h"
#include "afxdialogex.h"
#include "Keychange.h"
#include "Firmregister.h"
#include "Firmsearch.h"
#include "Drugregister.h"
#include "Drugsearch.h"
#include "AD.h"
#include "ICread.h"
// CAdmin 对话框

IMPLEMENT_DYNAMIC(CAdmin, CDialogEx)

CAdmin::CAdmin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdmin::IDD, pParent)
{

	EnableAutomation();

}

CAdmin::~CAdmin()
{
}

void CAdmin::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdmin, CDialogEx)
	ON_BN_CLICKED(IDCHANGEKEY, &CAdmin::OnBnClickedChangekey)
	ON_BN_CLICKED(IDREGSITERFIRM, &CAdmin::OnBnClickedRegsiterfirm)
	ON_BN_CLICKED(IDSEARCHFIRM, &CAdmin::OnBnClickedSearchfirm)
	ON_BN_CLICKED(IDREGSITERDRUG, &CAdmin::OnBnClickedRegsiterdrug)
	ON_BN_CLICKED(IDSEARCHDRUG, &CAdmin::OnBnClickedSearchdrug)
	ON_BN_CLICKED(IDCANCEL, &CAdmin::OnBnClickedCancel)
	ON_BN_CLICKED(IDDA, &CAdmin::OnBnClickedDa)
	ON_BN_CLICKED(IDREADIC, &CAdmin::OnBnClickedReadic)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAdmin, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IAdmin 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {E494533E-9777-45CB-A406-BA1E91B8F977}
static const IID IID_IAdmin =
{ 0xE494533E, 0x9777, 0x45CB, { 0xA4, 0x6, 0xBA, 0x1E, 0x91, 0xB8, 0xF9, 0x77 } };

BEGIN_INTERFACE_MAP(CAdmin, CDialogEx)
	INTERFACE_PART(CAdmin, IID_IAdmin, Dispatch)
END_INTERFACE_MAP()


// CAdmin 消息处理程序


void CAdmin::OnBnClickedChangekey()
{
	CKeychange dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedRegsiterfirm()
{
	CFirmregister dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedSearchfirm()
{
	CFirmsearch dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedRegsiterdrug()
{
	CDrugregister dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedSearchdrug()
{
	CDrugsearch dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CAdmin::OnBnClickedDa()
{
	CAD dlg;
	dlg.m_admin=this;
	dlg.DoModal();
}


void CAdmin::OnBnClickedReadic()
{
	CICread dlg;
	dlg.DoModal();
}
