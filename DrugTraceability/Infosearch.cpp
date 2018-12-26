// Infosearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Infosearch.h"
#include "afxdialogex.h"


// CInfosearch �Ի���

IMPLEMENT_DYNAMIC(CInfosearch, CDialogEx)

CInfosearch::CInfosearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInfosearch::IDD, pParent)
{

	EnableAutomation();

}

CInfosearch::~CInfosearch()
{
}

void CInfosearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CInfosearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
}


BEGIN_MESSAGE_MAP(CInfosearch, CDialogEx)
	ON_BN_CLICKED(IDSEARCH, &CInfosearch::OnBnClickedSearch)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CInfosearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IInfosearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {4A678955-9438-4F4E-AFE0-1A2816873E6A}
static const IID IID_IInfosearch =
{ 0x4A678955, 0x9438, 0x4F4E, { 0xAF, 0xE0, 0x1A, 0x28, 0x16, 0x87, 0x3E, 0x6A } };

BEGIN_INTERFACE_MAP(CInfosearch, CDialogEx)
	INTERFACE_PART(CInfosearch, IID_IInfosearch, Dispatch)
END_INTERFACE_MAP()


// CInfosearch ��Ϣ�������


BOOL CInfosearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strsql;
	if(this->m_Producer!=NULL)
	{
		pDB=m_Producer->m_login->pDB;
		pRs=m_Producer->m_login->pRs;
		HID=m_Producer->m_login->HID;
		this->SetWindowTextA("������¼��ѯ");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //������ʾ��ѡ����
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //��������ѡ��
			LVS_EX_HEADERDRAGDROP|  //���������϶�
			LVS_EX_GRIDLINES|     //����������
			LVS_EX_ONECLICKACTIVATE|     //����ѡ����
			LVS_EX_FLATSB);    //��ƽ�����ʾ������
		m_listPerson.InsertColumn(0,"ҩƷ���",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"ҩƷ����",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"��������",LVCFMT_LEFT,134,2);
		m_listPerson.InsertColumn(3,"�����ɱ�",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"�۳��۸�",LVCFMT_LEFT,134,4);
	}
	if(this->m_Transfer!=NULL)
	{
		pDB=m_Transfer->m_login->pDB;
		pRs=m_Transfer->m_login->pRs;
		HID=m_Transfer->m_login->HID;
		this->SetWindowTextA("��ר��¼��ѯ");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //������ʾ��ѡ����
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //��������ѡ��
			LVS_EX_HEADERDRAGDROP|  //���������϶�
			LVS_EX_GRIDLINES|     //����������
			LVS_EX_ONECLICKACTIVATE|     //����ѡ����
			LVS_EX_FLATSB);    //��ƽ�����ʾ������
		m_listPerson.InsertColumn(0,"ҩƷ���",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"ҩƷ����",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"��ת����",LVCFMT_LEFT,134,2);
		m_listPerson.InsertColumn(3,"�����ɱ�",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"�۳��۸�",LVCFMT_LEFT,134,4);
	}
	if(this->m_Drugstore!=NULL)
	{
		pDB=m_Drugstore->m_login->pDB;
		pRs=m_Drugstore->m_login->pRs;
		HID=m_Drugstore->m_login->HID;
		this->SetWindowTextA("���ۼ�¼��ѯ");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //������ʾ��ѡ����
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //��������ѡ��
			LVS_EX_HEADERDRAGDROP|  //���������϶�
			LVS_EX_GRIDLINES|     //����������
			LVS_EX_ONECLICKACTIVATE|     //����ѡ����
			LVS_EX_FLATSB);    //��ƽ�����ʾ������
		m_listPerson.InsertColumn(0,"ҩƷ���",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"ҩƷ����",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"�ϼ�����",LVCFMT_LEFT,134,2);	
		m_listPerson.InsertColumn(3,"�����ɱ�",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"�۳��۸�",LVCFMT_LEFT,134,4);
	}
	strsql.Format("SELECT * FROM view1 where FID = '%s'",HID);
		pRs->Open(_bstr_t(strsql),1);
		if(!pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return TRUE;
		}
		pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(pRs));
		return TRUE;
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BOOL CInfosearch::RefreshList(CADORecordset& recordset)
{
	m_listPerson.DeleteAllItems();
	
	if(!recordset.IsOpen())
		return FALSE;
	
	recordset.MoveFirst();
    CString DID,Dname,Ddate,Iprice,Oprice;
	int indexofList=0;
	while( !(recordset.IsEOF()) )
	{    
		recordset.GetFieldValue("DID",DID);
		recordset.GetFieldValue("Dname",Dname);
		recordset.GetFieldValue("Tdate",Ddate);
		recordset.GetFieldValue("Inprice",Iprice);
		recordset.GetFieldValue("Outprice",Oprice);

		m_listPerson.InsertItem(indexofList,DID);
		m_listPerson.SetItemText(indexofList,1, Dname);
		m_listPerson.SetItemText(indexofList,2,Ddate);
		m_listPerson.SetItemText(indexofList,3,Iprice);
		m_listPerson.SetItemText(indexofList,4,Oprice);
		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
	
	return TRUE;
}

void CInfosearch::OnBnClickedSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
