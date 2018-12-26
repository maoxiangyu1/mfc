// Drugchange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugchange.h"
#include "afxdialogex.h"


// CDrugchange �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IDrugchange ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4172FE89-F734-4094-84AC-C3F656CEF32C}
static const IID IID_IDrugchange =
{ 0x4172FE89, 0xF734, 0x4094, { 0x84, 0xAC, 0xC3, 0xF6, 0x56, 0xCE, 0xF3, 0x2C } };

BEGIN_INTERFACE_MAP(CDrugchange, CDialogEx)
	INTERFACE_PART(CDrugchange, IID_IDrugchange, Dispatch)
END_INTERFACE_MAP()


// CDrugchange ��Ϣ�������


void CDrugchange::OnBnClickedOk()
{
	UpdateData(true);
	CString s;
	s.Format("update dbo.Drug set DID='%s',Dname='%s',Dinfo='%s' where DID='%s'",m_did,m_dname,m_dinfo,m_drugsearch->m_DID);
	if(m_drugsearch->m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("���ĳɹ���");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("����ʧ�ܣ�");
		return;
	}
}


BOOL CDrugchange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_did=m_drugsearch->m_DID;
	m_dname=m_drugsearch->m_Dname;
	m_dinfo=m_drugsearch->m_Dinfo;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
