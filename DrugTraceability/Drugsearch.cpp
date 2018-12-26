// Drugsearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugsearch.h"
#include "afxdialogex.h"
#include "Drugchange.h"

// CDrugsearch �Ի���

IMPLEMENT_DYNAMIC(CDrugsearch, CDialogEx)

CDrugsearch::CDrugsearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrugsearch::IDD, pParent)
{

	EnableAutomation();

	m_type = _T("");
	m_key = _T("");
}

CDrugsearch::~CDrugsearch()
{
}

void CDrugsearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CDrugsearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_Text(pDX, IDC_EDIT2, m_key);
}


BEGIN_MESSAGE_MAP(CDrugsearch, CDialogEx)
	ON_BN_CLICKED(IDSEARCH, &CDrugsearch::OnBnClickedSearch)
	ON_BN_CLICKED(IDDEL, &CDrugsearch::OnBnClickedDel)
	ON_BN_CLICKED(IDCHANGE, &CDrugsearch::OnBnClickedChange)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDrugsearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IDrugsearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {C826B5CD-4E6F-4C94-8D26-6D8504BA87ED}
static const IID IID_IDrugsearch =
{ 0xC826B5CD, 0x4E6F, 0x4C94, { 0x8D, 0x26, 0x6D, 0x85, 0x4, 0xBA, 0x87, 0xED } };

BEGIN_INTERFACE_MAP(CDrugsearch, CDialogEx)
	INTERFACE_PART(CDrugsearch, IID_IDrugsearch, Dispatch)
END_INTERFACE_MAP()


// CDrugsearch ��Ϣ�������


BOOL CDrugsearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listPerson.ModifyStyle(0L,LVS_REPORT);   
	m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
	m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //������ʾ��ѡ����
	m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //��������ѡ��
		LVS_EX_HEADERDRAGDROP|  //���������϶�
		LVS_EX_GRIDLINES|     //����������
		LVS_EX_ONECLICKACTIVATE|     //����ѡ����
		LVS_EX_FLATSB);    //��ƽ�����ʾ������
	m_listPerson.InsertColumn(0,"ҩƷ���",LVCFMT_LEFT,214,0);
	m_listPerson.InsertColumn(1,"ҩƷ����",LVCFMT_LEFT,230,1);
	m_listPerson.InsertColumn(2,"ҩƷ���",LVCFMT_LEFT,230,2);
	CString strsql;
	strsql.Format("SELECT * FROM Drug");
	m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
	if(!m_admin->m_login->pRs->GetRecordCount())
	{
		m_listPerson.DeleteAllItems();
		return TRUE;
	}
	m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
	RefreshList(*(m_admin->m_login->pRs));
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
BOOL CDrugsearch::RefreshList(CADORecordset& recordset)
{
	m_listPerson.DeleteAllItems();
	
	if(!recordset.IsOpen())
		return false;
	
	recordset.MoveFirst();
    CString DID,Dname,Dinfo;
	int indexofList=0;
	while( !(recordset.IsEOF()) )
	{    
		recordset.GetFieldValue("DID",DID);
		recordset.GetFieldValue("Dname",Dname);
		recordset.GetFieldValue("Dinfo",Dinfo);
		
		m_listPerson.InsertItem(indexofList,DID);
		m_listPerson.SetItemText(indexofList,1, Dname);
		m_listPerson.SetItemText(indexofList,2,Dinfo);

		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
	
	return true;
}

void CDrugsearch::OnBnClickedSearch()
{
	UpdateData(true);
	CString strsql;
	if(m_key=="")
	{
		strsql.Format("SELECT * FROM Drug");
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="ҩƷ���")
	{
		strsql.Format("SELECT * FROM Drug where DID='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="ҩƷ����")
	{
		strsql.Format("SELECT * FROM Drug where Dname='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="ҩƷ���")
	{
		//strsql.Format("SELECT * FROM Drug where Dinfo like '\%%s\%'",m_key);
		strsql = "select * from Drug where Dinfo like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
}


void CDrugsearch::OnBnClickedDel()
{
	POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
	int nItem = m_listPerson.GetNextSelectedItem(pos);
	CString s=m_listPerson.GetItemText(nItem,0);
	if(s=="")
	{
		AfxMessageBox("��ѡ����Ҫɾ������Ϣ��");
		return;
	}
	CString S;
	S.Format("delete Drug where DID='%s'",s);
	if(m_admin->m_login->pDB->Execute(S)==TRUE)
	{
		m_listPerson.DeleteItem(nItem);
		AfxMessageBox("ɾ��ҩƷ��Ϣ�ɹ���");	
		return;
	}
	else
	{
		AfxMessageBox("ɾ��ҩƷ��Ϣʧ�ܣ�");
		return;
	}
}


void CDrugsearch::OnBnClickedChange()
{
	POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
	int nItem = m_listPerson.GetNextSelectedItem(pos);
	m_DID=m_listPerson.GetItemText(nItem,0);
	if(m_DID=="")
	{
		AfxMessageBox("��ѡ��Ҫ���ĵ�ҩƷ��Ϣ��");
		return;
	}
	m_Dname=m_listPerson.GetItemText(nItem,1);
	m_Dinfo=m_listPerson.GetItemText(nItem,2);
	CDrugchange dlg;
	dlg.m_drugsearch=this;
	if(dlg.DoModal()==0)
	{
		CString s;
		s.Format("SELECT * from Drug");
		m_admin->m_login->pRs->Open(_bstr_t(s),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		m_admin->m_login->pRs->Open(_bstr_t(s),1);
		RefreshList(*(m_admin->m_login->pRs));
	}
}
