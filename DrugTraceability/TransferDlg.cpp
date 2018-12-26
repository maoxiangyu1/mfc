// TransferDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "TransferDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include"ICread.h"
// CTransfer �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ITransfer ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {5395C244-9192-492F-83DC-D178C5BAAB9C}
static const IID IID_ITransfer =
{ 0x5395C244, 0x9192, 0x492F, { 0x83, 0xDC, 0xD1, 0x78, 0xC5, 0xBA, 0xAB, 0x9C } };

BEGIN_INTERFACE_MAP(CTransfer, CDialogEx)
	INTERFACE_PART(CTransfer, IID_ITransfer, Dispatch)
END_INTERFACE_MAP()


// CTransfer ��Ϣ�������


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
