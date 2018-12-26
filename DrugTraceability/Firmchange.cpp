// Firmchange.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Firmchange.h"
#include "afxdialogex.h"


// CFirmchange 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

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

// 注意: 我们添加 IID_IFirmchange 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {6A6F2358-1AED-43B2-818A-A8DFB282B8EE}
static const IID IID_IFirmchange =
{ 0x6A6F2358, 0x1AED, 0x43B2, { 0x81, 0x8A, 0xA8, 0xDF, 0xB2, 0x82, 0xB8, 0xEE } };

BEGIN_INTERFACE_MAP(CFirmchange, CDialogEx)
	INTERFACE_PART(CFirmchange, IID_IFirmchange, Dispatch)
END_INTERFACE_MAP()


// CFirmchange 消息处理程序


void CFirmchange::OnBnClickedOk()
{
	UpdateData(true);
	CString s;
	s.Format("update Firm set Fname='%s',Fboss='%s',Faddress='%s',Ftel='%s',Finfo='%s' where FID='%s'",m_fname,m_fboss,m_faddress,m_ftel,m_finfo,m_firmsearch->m_FID);
	if(m_firmsearch->m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		AfxMessageBox("更改成功！");
		this->EndDialog(0);
		return;
	}
	else
	{
		AfxMessageBox("更改失败！");
		return;
	}
}


BOOL CFirmchange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_fname=m_firmsearch->m_Fname;
	m_fboss=m_firmsearch->m_Fboss;
	m_faddress=m_firmsearch->m_Faddress;
	m_ftel=m_firmsearch->m_Ftel;
	m_finfo=m_firmsearch->m_Finfo;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
