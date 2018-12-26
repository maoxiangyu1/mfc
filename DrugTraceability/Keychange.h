#pragma once
#include "Admin.h"

// CKeychange 对话框

class CKeychange : public CDialogEx
{
	DECLARE_DYNAMIC(CKeychange)

public:
	CAdmin *m_admin;
	CKeychange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKeychange();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_CHANGEKEY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:

	afx_msg void OnBnClickedOk();
	CString m_key1;
	CString m_key2;
	CString m_key3;
};
