// DrugstoreDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "DrugstoreDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include "ICread.h"
// CDrugstore �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDrugstore ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {169EFD76-5A07-4C94-9787-8104538B58B4}
static const IID IID_IDrugstore =
{ 0x169EFD76, 0x5A07, 0x4C94, { 0x97, 0x87, 0x81, 0x4, 0x53, 0x8B, 0x58, 0xB4 } };

BEGIN_INTERFACE_MAP(CDrugstore, CDialogEx)
	INTERFACE_PART(CDrugstore, IID_IDrugstore, Dispatch)
END_INTERFACE_MAP()


// CDrugstore ��Ϣ�������


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
