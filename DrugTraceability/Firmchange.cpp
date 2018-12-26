// Firmchange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Firmchange.h"
#include "afxdialogex.h"


// CFirmchange �Ի���

IMPLEMENT_DYNAMIC(CFirmchange, CDialogEx)

CFirmchange::CFirmchange(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirmchange::IDD, pParent)
{

	EnableAutomation();

	m_fname = _T("");
	m_fboss = _T("");
	m_faddress = _T("");
	m_ftel = _T("");
	m_finfo = _T("");
}

CFirmchange::~CFirmchange()
{
}

void CFirmchange::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CFirmchange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_fname);
	DDX_Text(pDX, IDC_EDIT2, m_fboss);
	DDX_Text(pDX, IDC_EDIT3, m_faddress);
	DDX_Text(pDX, IDC_EDIT4, m_ftel);
	DDX_Text(pDX, IDC_EDIT5, m_finfo);
}


BEGIN_MESSAGE_MAP(CFirmchange, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFirmchange::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmchange, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IFirmchange ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {6A6F2358-1AED-43B2-818A-A8DFB282B8EE}
static const IID IID_IFirmchange =
{ 0x6A6F2358, 0x1AED, 0x43B2, { 0x81, 0x8A, 0xA8, 0xDF, 0xB2, 0x82, 0xB8, 0xEE } };

BEGIN_INTERFACE_MAP(CFirmchange, CDialogEx)
	INTERFACE_PART(CFirmchange, IID_IFirmchange, Dispatch)
END_INTERFACE_MAP()


// CFirmchange ��Ϣ�������


void CFirmchange::OnBnClickedOk()
{
	UpdateData(true);
	CString s;
	s.Format("update Firm set Fname='%s',Fboss='%s',Faddress='%s',Ftel='%s',Finfo='%s' where FID='%s'",m_fname,m_fboss,m_faddress,m_ftel,m_finfo,m_firmsearch->m_FID);
	if(m_firmsearch->m_admin->m_login->pDB->Execute(s)==TRUE)
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


BOOL CFirmchange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_fname=m_firmsearch->m_Fname;
	m_fboss=m_firmsearch->m_Fboss;
	m_faddress=m_firmsearch->m_Faddress;
	m_ftel=m_firmsearch->m_Ftel;
	m_finfo=m_firmsearch->m_Finfo;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
