// Drugsearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugsearch.h"
#include "afxdialogex.h"
#include "Drugchange.h"

// CDrugsearch 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_IDrugsearch 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {C826B5CD-4E6F-4C94-8D26-6D8504BA87ED}
static const IID IID_IDrugsearch =
{ 0xC826B5CD, 0x4E6F, 0x4C94, { 0x8D, 0x26, 0x6D, 0x85, 0x4, 0xBA, 0x87, 0xED } };

BEGIN_INTERFACE_MAP(CDrugsearch, CDialogEx)
	INTERFACE_PART(CDrugsearch, IID_IDrugsearch, Dispatch)
END_INTERFACE_MAP()


// CDrugsearch 消息处理程序


BOOL CDrugsearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listPerson.ModifyStyle(0L,LVS_REPORT);   
	m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
	m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //高亮显示被选中项
	m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //允许整行选中
		LVS_EX_HEADERDRAGDROP|  //允许整列拖动
		LVS_EX_GRIDLINES|     //画出网格线
		LVS_EX_ONECLICKACTIVATE|     //单击选中项
		LVS_EX_FLATSB);    //扁平风格显示滚动条
	m_listPerson.InsertColumn(0,"药品编号",LVCFMT_LEFT,214,0);
	m_listPerson.InsertColumn(1,"药品名称",LVCFMT_LEFT,230,1);
	m_listPerson.InsertColumn(2,"药品简介",LVCFMT_LEFT,230,2);
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
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	if(m_type=="药品编号")
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
	if(m_type=="药品名称")
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
	if(m_type=="药品简介")
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
		AfxMessageBox("请选中您要删除的信息！");
		return;
	}
	CString S;
	S.Format("delete Drug where DID='%s'",s);
	if(m_admin->m_login->pDB->Execute(S)==TRUE)
	{
		m_listPerson.DeleteItem(nItem);
		AfxMessageBox("删除药品信息成功！");	
		return;
	}
	else
	{
		AfxMessageBox("删除药品信息失败！");
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
		AfxMessageBox("请选中要更改的药品信息！");
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
