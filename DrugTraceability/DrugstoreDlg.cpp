// DrugstoreDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugstoreDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include "ICread.h"
// CDrugstore 对话框

IMPLEMENT_DYNAMIC(CDrugstore, CDialogEx)

CDrugstore::CDrugstore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugstore::IDD, pParent)
{

	EnableAutomation();

}

CDrugstore::~CDrugstore()
{
}

void CDrugstore::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CDrugstore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrugstore, CDialogEx)
	ON_BN_CLICKED(IDDRUGPROD, &CDrugstore::OnBnClickedDrugprod)
	ON_BN_CLICKED(IDDRUGSEARCH, &CDrugstore::OnBnClickedDrugsearch)
	ON_BN_CLICKED(IDDICREAD, &CDrugstore::OnBnClickedDicread)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugstore, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IDrugstore 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {169EFD76-5A07-4C94-9787-8104538B58B4}
static const IID IID_IDrugstore =
{ 0x169EFD76, 0x5A07, 0x4C94, { 0x97, 0x87, 0x81, 0x4, 0x53, 0x8B, 0x58, 0xB4 } };

BEGIN_INTERFACE_MAP(CDrugstore, CDialogEx)
	INTERFACE_PART(CDrugstore, IID_IDrugstore, Dispatch)
END_INTERFACE_MAP()


// CDrugstore 消息处理程序


void CDrugstore::OnBnClickedDrugprod()
{
	CDrugp dlg;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Transfer=NULL;
	dlg.m_Drugstore=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}
}


void CDrugstore::OnBnClickedDrugsearch()
{
	CInfosearch dlg;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Transfer=NULL;
	dlg.m_Drugstore=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}
}


void CDrugstore::OnBnClickedDicread()
{
	CICread dlg;
	//dlg.m_admin=this;
	dlg.DoModal();
}
