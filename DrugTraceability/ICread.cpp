// ICread.cpp : 实现文件
//

#include "stdafx.h"
#include "DrugTraceability.h"
#include "ICread.h"
#include "afxdialogex.h"


// CICread 对话框

IMPLEMENT_DYNAMIC(CICread, CDialogEx)

CICread::CICread(CWnd* pParent /*=NULL*/)
	: CDialogEx(CICread::IDD, pParent)
{

	EnableAutomation();

	//  m_info = _T("");
	//  m_info = _T("");
}

CICread::~CICread()
{
}

void CICread::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CICread::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT2, m_info);
	//  DDX_Control(pDX, IDC_EDIT2, m_c);
	//  DDX_Text(pDX, IDC_EDIT2, m_info);
	//  DDV_MaxChars(pDX, m_info, 30000);
}


BEGIN_MESSAGE_MAP(CICread, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CICread, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IICread 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {CD18A75D-4FEE-4CD9-998E-2479158E8F85}
static const IID IID_IICread =
{ 0xCD18A75D, 0x4FEE, 0x4CD9, { 0x99, 0x8E, 0x24, 0x79, 0x15, 0x8E, 0x8F, 0x85 } };

BEGIN_INTERFACE_MAP(CICread, CDialogEx)
	INTERFACE_PART(CICread, IID_IICread, Dispatch)
END_INTERFACE_MAP()


// CICread 消息处理程序


BOOL CICread::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		m_info="";
	CString buffer;
	// TODO:  在此添加额外的初始化
	char ickey[]={0xff,0xff,0xff,0xff,0xff,0xff};
	m_WriteIC.Set_port(0,254,1);
	if (0 != m_WriteIC.Detect_Fkj())
	{
		AfxMessageBox(_T("未检测到发卡机!"));
		this->EndDialog(0);
		this->EndDialog(1);
	}
	m_WriteIC.Beep(200);
		int CardType=-1;
	int again=1;
a:	if ( 0 == m_WriteIC.RFRequest(0,&CardType))
	{
		if (CardType != 4)
		{
			AfxMessageBox(_T("不是M1卡!"));
			this->EndDialog(0);
			return TRUE;
		}

		if (0 != m_WriteIC.RFAnticoll(0,&snr))
		{
			AfxMessageBox(_T("读卡号失败!"));
			this->EndDialog(0);
			return TRUE;
		}
	}
	else
	{
		if (again == 1)
		{
			again--;
			goto a;
		}
		else
		{
			AfxMessageBox(_T("无IC卡！"));
			this->EndDialog(0);
			return TRUE;
		}
	}
	unsigned long sn=0;
	CString step;
	char Buffer[16];
	char atime[11];
	int ret=m_WriteIC.RFReadA(sn,1 ,(LPSTR)(LPCTSTR)step,ickey);
	for(int i=1;i<=_ttoi(step);i++)
	{
		buffer.Format("----第%d站----\n",i);
		m_info=m_info+buffer;
		ret=m_WriteIC.RFReadA(sn,i*4 ,(LPSTR)(LPCTSTR)buffer,ickey);
		m_info=m_info+"公司编号："+buffer+"\n";
		ret=m_WriteIC.RFReadA(sn,i*4+1 ,(LPSTR)(LPCTSTR)buffer,ickey);
		m_info=m_info+"药品编号："+buffer+"\n";
		ret=m_WriteIC.RFReadA(sn,i*4+2 ,Buffer,ickey);
		memcpy(&p,Buffer,sizeof(Buffer));
		int j1=0;
		for(int j=0;j<10;j++)
		{
			
			if(j==4)
			{
				atime[j]='-';
				continue;
			}
			if(j==7)
			{
				atime[j]='-';
				continue;
			}
			atime[j]=p.date[j1];
			j1=j1+1;
		}
		atime[10]='\0';
		buffer.Format("成本价格：%.2f \n出售价格：%.2f \n交易时间：%s \n",p.inp,p.outp,atime);
		m_info=m_info+buffer;
	}
	GetDlgItem(IDC_STATIC)->SetWindowText(m_info);
	UpdateData(FALSE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CICread::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//dc.TextOutA(20,20,m_info);
}
