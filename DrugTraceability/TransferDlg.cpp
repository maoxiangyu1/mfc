// TransferDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "TransferDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include"ICread.h"
// CTransfer 对话框

IMPLEMENT_DYNAMIC(CTransfer, CDialogEx)

CTransfer::CTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTransfer::IDD, pParent)
{

	EnableAutomation();

}

CTransfer::~CTransfer()
{
}

void CTransfer::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTransfer, CDialogEx)
	ON_BN_CLICKED(IDDRUGPROD, &CTransfer::OnBnClickedDrugprod)
	ON_BN_CLICKED(IDDRUGSEARCH, &CTransfer::OnBnClickedDrugsearch)
	ON_BN_CLICKED(IDDICREAD, &CTransfer::OnBnClickedDicread)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTransfer, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITransfer 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {5395C244-9192-492F-83DC-D178C5BAAB9C}
static const IID IID_ITransfer =
{ 0x5395C244, 0x9192, 0x492F, { 0x83, 0xDC, 0xD1, 0x78, 0xC5, 0xBA, 0xAB, 0x9C } };

BEGIN_INTERFACE_MAP(CTransfer, CDialogEx)
	INTERFACE_PART(CTransfer, IID_ITransfer, Dispatch)
END_INTERFACE_MAP()


// CTransfer 消息处理程序


void CTransfer::OnBnClickedDrugprod()
{
	CDrugp dlg;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Transfer=NULL;
	dlg.m_Transfer=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}
}


void CTransfer::OnBnClickedDrugsearch()
{
	CInfosearch dlg;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Transfer=NULL;
	dlg.m_Transfer=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}
}


void CTransfer::OnBnClickedDicread()
{
	CICread dlg;
	dlg.DoModal();
}
