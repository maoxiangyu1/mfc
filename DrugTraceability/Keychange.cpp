// Keychange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Keychange.h"
#include "afxdialogex.h"


// CKeychange �Ի���

IMPLEMENT_DYNAMIC(CKeychange, CDialogEx)

CKeychange::CKeychange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeychange::IDD, pParent)
{

	EnableAutomation();
	m_key1 = _T("");
	m_key2 = _T("");
	m_key3 = _T("");
}

CKeychange::~CKeychange()
{
}

void CKeychange::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CKeychange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_key1);
	DDV_MaxChars(pDX, m_key1, 16);
	DDX_Text(pDX, IDC_EDIT2, m_key2);
	DDV_MaxChars(pDX, m_key2, 16);
	DDX_Text(pDX, IDC_EDIT3, m_key3);
	DDV_MaxChars(pDX, m_key3, 16);
}


BEGIN_MESSAGE_MAP(CKeychange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CKeychange::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CKeychange, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IKeychange ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C348D560-B46D-4869-8F85-C3CC2D16810B}
static const IID IID_IKeychange =
{ 0xC348D560, 0xB46D, 0x4869, { 0x8F, 0x85, 0xC3, 0xCC, 0x2D, 0x16, 0x81, 0xB } };

BEGIN_INTERFACE_MAP(CKeychange, CDialogEx)
	INTERFACE_PART(CKeychange, IID_IKeychange, Dispatch)
END_INTERFACE_MAP()


// CKeychange ��Ϣ�������


void CKeychange::OnBnClickedOk()
{
	UpdateData(true);
	if(m_key1=="" || m_key2=="" ||m_key3=="")
	{
		AfxMessageBox("���벻��Ϊ�գ�");
		return;
	}
	if(m_key2!=m_key3)
	{
		AfxMessageBox("�����������벻һ�£�");
		m_key2="";
		m_key3="";
		UpdateData(false);
		return;
	}
	if(m_key2.GetLength ()!=16)
	{
		AfxMessageBox("����Ա�������Ϊ16λ��");
	}
	if(Dongle_VerifyPIN(m_admin->m_login->hDongle,FLAG_ADMINPIN,(char*)(LPCTSTR)m_key1,m_admin->m_login->pRemain)==DONGLE_SUCCESS)
	{
		memcpy(m_admin->m_login->UKEY,(char*)(LPCTSTR)m_key2,128);
		int nInDataLen = (128 -11);
		int nOutDataLen = 128;
		if(!Dongle_RsaPri(m_admin->m_login->hDongle, 0x0001, FLAG_ENCODE, m_admin->m_login->UKEY, nInDataLen, m_admin->m_login->UKEY, &nOutDataLen))
		{
			char a[17],b[17];
			for(int i=0;i<16;i++)
			{
				a[i]=m_key1[i];
				b[i]=m_key2[i];
			}
			a[16]='\0';
			b[16]='\0';
			int n=Dongle_ChangePIN(m_admin->m_login->hDongle,FLAG_ADMINPIN,a,b,255);
			if(n==0xF0000006)
			{
				AfxMessageBox("���豸δ��ʼ����");
				return;
			}
			if(!n)
			{
				if(!Dongle_WriteData(m_admin->m_login->hDongle, 5632, m_admin->m_login->UKEY, 128))
				{
					AfxMessageBox("�����޸ĳɹ��������µ�½��");
					this->EndDialog(0);
					m_admin->EndDialog(0);
					return;
				}
				else
				{
					AfxMessageBox("�����޸�ʧ�ܣ������ԣ�");
					return;
				}	
			}
			else
			{
				AfxMessageBox("�����޸�ʧ�ܣ������ԣ�");
				return;
			}		
		}
		else
		{
			AfxMessageBox("�����޸�ʧ�ܣ������ԣ�");
			return;
		}

	}
	else
	{
		AfxMessageBox("��ǰ���벻��ȷ��");
	}
	
}
