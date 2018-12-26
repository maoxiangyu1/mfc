// Drugregister.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugregister.h"
#include "afxdialogex.h"


// CDrugregister �Ի���

IMPLEMENT_DYNAMIC(CDrugregister, CDialogEx)

CDrugregister::CDrugregister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugregister::IDD, pParent)
{

	EnableAutomation();

	m_DID = _T("");
	m_Dname = _T("");
	m_Dinfo = _T("");
}

CDrugregister::~CDrugregister()
{
}

void CDrugregister::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CDrugregister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_DID);
	DDX_Text(pDX, IDC_EDIT2, m_Dname);
	DDX_Text(pDX, IDC_EDIT3, m_Dinfo);
}


BEGIN_MESSAGE_MAP(CDrugregister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDrugregister::OnBnClickedOk)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugregister, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IDrugregister ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {876C82D0-D5C2-434B-A0B7-6D8DCFB37452}
static const IID IID_IDrugregister =
{ 0x876C82D0, 0xD5C2, 0x434B, { 0xA0, 0xB7, 0x6D, 0x8D, 0xCF, 0xB3, 0x74, 0x52 } };

BEGIN_INTERFACE_MAP(CDrugregister, CDialogEx)
	INTERFACE_PART(CDrugregister, IID_IDrugregister, Dispatch)
END_INTERFACE_MAP()


// CDrugregister ��Ϣ�������


void CDrugregister::OnBnClickedOk()
{
	UpdateData(true);
	if(m_DID==""||m_Dname==""||m_Dinfo=="")
	{
		AfxMessageBox("ҩƷ��Ϣ����Ϊ�գ�");
		return;
	}
	CString s;
	s.Format("insert into Drug values('%s','%s','%s')",m_DID,m_Dname,m_Dinfo);
	if(m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("ע��ɹ���");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("ע��ʧ�ܣ�");
		return;
	}
}
