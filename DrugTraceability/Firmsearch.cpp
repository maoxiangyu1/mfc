// Firmsearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Firmsearch.h"
#include "afxdialogex.h"
#include "Firmchange.h"

// CFirmsearch �Ի���

IMPLEMENT_DYNAMIC(CFirmsearch, CDialogEx)

CFirmsearch::CFirmsearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirmsearch::IDD, pParent)
{

	EnableAutomation();

	m_key = _T("");
	m_type = _T("");
}

CFirmsearch::~CFirmsearch()
{
}

void CFirmsearch::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CFirmsearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_key);
	DDX_CBString(pDX, IDC_COMBO1, m_type);
	DDX_Control(pDX, IDC_LIST1, m_listPerson);
}


BEGIN_MESSAGE_MAP(CFirmsearch, CDialogEx)
	ON_BN_CLICKED(IDSEARCH, &CFirmsearch::OnBnClickedSearch)
	ON_BN_CLICKED(IDDEL, &CFirmsearch::OnBnClickedDel)
	ON_BN_CLICKED(IDCHANGE, &CFirmsearch::OnBnClickedChange)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmsearch, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IFirmsearch ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {F1FE3C91-F101-4ABF-A0FE-26F0FEA2B290}
static const IID IID_IFirmsearch =
{ 0xF1FE3C91, 0xF101, 0x4ABF, { 0xA0, 0xFE, 0x26, 0xF0, 0xFE, 0xA2, 0xB2, 0x90 } };

BEGIN_INTERFACE_MAP(CFirmsearch, CDialogEx)
	INTERFACE_PART(CFirmsearch, IID_IFirmsearch, Dispatch)
END_INTERFACE_MAP()


// CFirmsearch ��Ϣ�������


BOOL CFirmsearch::OnInitDialog()
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
	m_listPerson.InsertColumn(0,"��˾���",LVCFMT_LEFT,130,0);
	m_listPerson.InsertColumn(1,"��˾����",LVCFMT_LEFT,130,1);
	m_listPerson.InsertColumn(2,"��˾������",LVCFMT_LEFT,130,2);
	m_listPerson.InsertColumn(3,"��˾��ַ",LVCFMT_LEFT,130,3);
	m_listPerson.InsertColumn(4,"��˾�绰",LVCFMT_LEFT,130,4);
	m_listPerson.InsertColumn(5,"��˾���",LVCFMT_LEFT,130,5);
	m_listPerson.InsertColumn(6,"��˾���",LVCFMT_LEFT,130,6);
	m_listPerson.InsertColumn(7,"ע��ʱ��",LVCFMT_LEFT,130,7);
	CString strsql;
	strsql.Format("SELECT * FROM Firm");
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
BOOL CFirmsearch::RefreshList(CADORecordset& recordset)
{
	m_listPerson.DeleteAllItems();
	
	if(!recordset.IsOpen())
		return FALSE;
	
	recordset.MoveFirst();
    CString FID,Fname,Fboss,Faddress,Ftel,Finfo,Fdate,Ftype;
	int indexofList=0;
	while( !(recordset.IsEOF()) )
	{    
		recordset.GetFieldValue("FID",FID);
		recordset.GetFieldValue("Fname",Fname);
		recordset.GetFieldValue("Fboss",Fboss);
		recordset.GetFieldValue("Faddress",Faddress);
		recordset.GetFieldValue("Ftel",Ftel);
		recordset.GetFieldValue("Ftype",Ftype);
		recordset.GetFieldValue("Finfo",Finfo);
		recordset.GetFieldValue("Fdate",Fdate);
		
		

		
		m_listPerson.InsertItem(indexofList,FID);
		m_listPerson.SetItemText(indexofList,1, Fname);
		m_listPerson.SetItemText(indexofList,2,Fboss);
		m_listPerson.SetItemText(indexofList,3,Faddress);
		m_listPerson.SetItemText(indexofList,4,Ftel);
		m_listPerson.SetItemText(indexofList,5,Ftype);
		m_listPerson.SetItemText(indexofList,6,Finfo);
		m_listPerson.SetItemText(indexofList,7,Fdate);

		indexofList+=1;
		recordset.MoveNext();
	}
	recordset.MoveFirst();
	
	return TRUE;
}

void CFirmsearch::OnBnClickedSearch()
{
	UpdateData(true);
	CString strsql;
	if(m_key=="")
	{
		strsql.Format("SELECT * FROM Firm");
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
	if(m_type=="��˾ID")
	{
		strsql.Format("SELECT * FROM Firm where FID='%s'",m_key);
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
	if(m_type=="��˾����")
	{
		strsql.Format("SELECT * FROM Firm where Fname='%s'",m_key);
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
	if(m_type=="��˾������")
	{
		strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
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
	if(m_type=="��˾���")
	{
		strsql = "select * from Firm where Ftype like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="��˾��ַ")
	{
		strsql = "select * from Firm where Faddress like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
	if(m_type=="��˾���")
	{
		strsql = "select * from Firm where Finfo like '%"+m_key+"%'";
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		if(!m_admin->m_login->pRs->GetRecordCount())
		{
			m_listPerson.DeleteAllItems();
			return;
		}
		//strsql.Format("SELECT * FROM Firm where Fboss='%s'",m_key);
		m_admin->m_login->pRs->Open(_bstr_t(strsql),1);
		RefreshList(*(m_admin->m_login->pRs));
		return;
	}
}


void CFirmsearch::OnBnClickedDel()
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
	S.Format("delete Firm where FID='%s'",s);
	if(m_admin->m_login->pDB->Execute(S)==TRUE)
	{
		m_listPerson.DeleteItem(nItem);
		AfxMessageBox("ɾ����˾��Ϣ�ɹ���");
		return;
	}
	else
	{
		AfxMessageBox("ɾ����˾��Ϣʧ�ܣ�");
		return;
	}
	
}


void CFirmsearch::OnBnClickedChange()
{
	POSITION pos = m_listPerson.GetFirstSelectedItemPosition();
	int nItem = m_listPerson.GetNextSelectedItem(pos);
	m_FID=m_listPerson.GetItemText(nItem,0);
	if(m_FID=="")
	{
		AfxMessageBox("��ѡ��Ҫ���ĵĹ�˾��Ϣ��");
		return;
	}
	m_Fname=m_listPerson.GetItemText(nItem,1);
	m_Fboss=m_listPerson.GetItemText(nItem,2);
	m_Faddress=m_listPerson.GetItemText(nItem,3);
	m_Ftel=m_listPerson.GetItemText(nItem,4);
	m_Finfo=m_listPerson.GetItemText(nItem,6);
	CFirmchange dlg;
	dlg.m_firmsearch=this;
	if(dlg.DoModal()==0)
	{
		CString s;
		s.Format("SELECT * FROM Firm");
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
