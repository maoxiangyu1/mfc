// ProducerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "ProducerDlg.h"
#include "afxdialogex.h"
#include "Drugp.h"
#include "Infosearch.h"
#include "ICread.h"
// CProducer �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IProducer ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {7357AA29-8CEE-4D2C-94DC-27278E045DF6}
static const IID IID_IProducer =
{ 0x7357AA29, 0x8CEE, 0x4D2C, { 0x94, 0xDC, 0x27, 0x27, 0x8E, 0x4, 0x5D, 0xF6 } };

BEGIN_INTERFACE_MAP(CProducer, CDialogEx)
	INTERFACE_PART(CProducer, IID_IProducer, Dispatch)
END_INTERFACE_MAP()


// CProducer ��Ϣ�������


void CProducer::OnBnClickedDrugprod()
{
/*
	m_WriteIC.Set_port(0,254,1);
	if (0 != m_WriteIC.Detect_Fkj())
	{
		AfxMessageBox(_T("δ��⵽������!"));
		return;
	}
	m_WriteIC.Beep(200);
	int CardType=-1;
	int again=1;
a:	if ( 0 == m_WriteIC.RFRequest(0,&CardType))
	{
		if (CardType != 4)
		{
			AfxMessageBox(_T("����M1��!"));
			return ;
		}

		if (0 == m_WriteIC.RFAnticoll(0,&snr))
		{
			return ;
		}
		else
		{
			AfxMessageBox(_T("������ʧ��!"));
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
			AfxMessageBox(_T("��ſ�"));
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CProducer::OnBnClickedDicread()
{
	CICread dlg;
	dlg.DoModal();
}
