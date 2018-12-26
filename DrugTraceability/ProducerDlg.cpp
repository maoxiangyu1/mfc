// ProducerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "ProducerDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include "ICread.h"
// CProducer 对话框

IMPLEMENT_DYNAMIC(CProducer, CDialogEx)

CProducer::CProducer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProducer::IDD, pParent)
{

	EnableAutomation();

}

CProducer::~CProducer()
{
}

void CProducer::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CProducer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProducer, CDialogEx)
	ON_BN_CLICKED(IDDRUGPROD, &CProducer::OnBnClickedDrugprod)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDDRUGSEARCH, &CProducer::OnBnClickedDrugsearch)
	ON_BN_CLICKED(IDDICREAD, &CProducer::OnBnClickedDicread)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CProducer, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IProducer 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {7357AA29-8CEE-4D2C-94DC-27278E045DF6}
static const IID IID_IProducer =
{ 0x7357AA29, 0x8CEE, 0x4D2C, { 0x94, 0xDC, 0x27, 0x27, 0x8E, 0x4, 0x5D, 0xF6 } };

BEGIN_INTERFACE_MAP(CProducer, CDialogEx)
	INTERFACE_PART(CProducer, IID_IProducer, Dispatch)
END_INTERFACE_MAP()


// CProducer 消息处理程序


void CProducer::OnBnClickedDrugprod()
{
/*
	m_WriteIC.Set_port(0,254,1);
	if (0 != m_WriteIC.Detect_Fkj())
	{
		AfxMessageBox(_T("未检测到发卡机!"));
		return;
	}
	m_WriteIC.Beep(200);
	int CardType=-1;
	int again=1;
a:	if ( 0 == m_WriteIC.RFRequest(0,&CardType))
	{
		if (CardType != 4)
		{
			AfxMessageBox(_T("不是M1卡!"));
			return ;
		}

		if (0 == m_WriteIC.RFAnticoll(0,&snr))
		{
			return ;
		}
		else
		{
			AfxMessageBox(_T("读卡号失败!"));
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
			AfxMessageBox(_T("请放卡"));
			return;
		}
	}
*/
	CDrugp dlg;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Transfer=NULL;
	dlg.m_Producer=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}


}


void CProducer::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void CProducer::OnBnClickedDrugsearch()
{
	CInfosearch dlg;
	dlg.m_Transfer=NULL;
	dlg.m_Producer=NULL;
	dlg.m_Drugstore=NULL;
	dlg.m_Producer=this;
	if(dlg.DoModal()==0)
	{
		this->EndDialog(0);
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CProducer::OnBnClickedDicread()
{
	CICread dlg;
	dlg.DoModal();
}
