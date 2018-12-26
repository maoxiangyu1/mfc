// Infosearch.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Infosearch.h"
#include "afxdialogex.h"


// CInfosearch 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_IInfosearch 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {4A678955-9438-4F4E-AFE0-1A2816873E6A}
static const IID IID_IInfosearch =
{ 0x4A678955, 0x9438, 0x4F4E, { 0xAF, 0xE0, 0x1A, 0x28, 0x16, 0x87, 0x3E, 0x6A } };

BEGIN_INTERFACE_MAP(CInfosearch, CDialogEx)
	INTERFACE_PART(CInfosearch, IID_IInfosearch, Dispatch)
END_INTERFACE_MAP()


// CInfosearch 消息处理程序


BOOL CInfosearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strsql;
	if(this->m_Producer!=NULL)
	{
		pDB=m_Producer->m_login->pDB;
		pRs=m_Producer->m_login->pRs;
		HID=m_Producer->m_login->HID;
		this->SetWindowTextA("生产记录查询");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //高亮显示被选中项
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //允许整行选中
			LVS_EX_HEADERDRAGDROP|  //允许整列拖动
			LVS_EX_GRIDLINES|     //画出网格线
			LVS_EX_ONECLICKACTIVATE|     //单击选中项
			LVS_EX_FLATSB);    //扁平风格显示滚动条
		m_listPerson.InsertColumn(0,"药品编号",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"药品名称",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"生产日期",LVCFMT_LEFT,134,2);
		m_listPerson.InsertColumn(3,"生产成本",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"售出价格",LVCFMT_LEFT,134,4);
	}
	if(this->m_Transfer!=NULL)
	{
		pDB=m_Transfer->m_login->pDB;
		pRs=m_Transfer->m_login->pRs;
		HID=m_Transfer->m_login->HID;
		this->SetWindowTextA("中专记录查询");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //高亮显示被选中项
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //允许整行选中
			LVS_EX_HEADERDRAGDROP|  //允许整列拖动
			LVS_EX_GRIDLINES|     //画出网格线
			LVS_EX_ONECLICKACTIVATE|     //单击选中项
			LVS_EX_FLATSB);    //扁平风格显示滚动条
		m_listPerson.InsertColumn(0,"药品编号",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"药品名称",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"中转日期",LVCFMT_LEFT,134,2);
		m_listPerson.InsertColumn(3,"生产成本",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"售出价格",LVCFMT_LEFT,134,4);
	}
	if(this->m_Drugstore!=NULL)
	{
		pDB=m_Drugstore->m_login->pDB;
		pRs=m_Drugstore->m_login->pRs;
		HID=m_Drugstore->m_login->HID;
		this->SetWindowTextA("出售记录查询");
		m_listPerson.ModifyStyle(0L,LVS_REPORT);   
		m_listPerson.ModifyStyle(LVS_SHOWSELALWAYS,0L);
		m_listPerson.ModifyStyle(0L,LVS_SHOWSELALWAYS);    //高亮显示被选中项
		m_listPerson.SetExtendedStyle(LVS_EX_FULLROWSELECT| //允许整行选中
			LVS_EX_HEADERDRAGDROP|  //允许整列拖动
			LVS_EX_GRIDLINES|     //画出网格线
			LVS_EX_ONECLICKACTIVATE|     //单击选中项
			LVS_EX_FLATSB);    //扁平风格显示滚动条
		m_listPerson.InsertColumn(0,"药品编号",LVCFMT_LEFT,138,0);
		m_listPerson.InsertColumn(1,"药品名称",LVCFMT_LEFT,134,1);
		m_listPerson.InsertColumn(2,"上架日期",LVCFMT_LEFT,134,2);	
		m_listPerson.InsertColumn(3,"生产成本",LVCFMT_LEFT,134,3);
		m_listPerson.InsertColumn(4,"售出价格",LVCFMT_LEFT,134,4);
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
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
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
	// TODO: 在此添加控件通知处理程序代码
}
