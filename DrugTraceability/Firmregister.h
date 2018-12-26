#pragma once
#include "Admin.h"

// CFirmregister 对话框

class CFirmregister : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmregister)

public:
	CAdmin *m_admin;
	CFirmregister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirmregister();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_REGISTERFIRM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	
	afx_msg void OnBnClickedOk();
	CString m_Fname;
	CString m_Fboss;
	CString m_Faddress;
	CString m_Ftel;
	CString m_Finfo;
	CString m_Ftype;
	afx_msg void OnBnClickedReset();
};
