#pragma once
#include "Firmsearch.h"

// CFirmchange 对话框

class CFirmchange : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmchange)

public:
	CFirmsearch *m_firmsearch;
	CFirmchange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFirmchange();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_FIRMCHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_fname;
	CString m_fboss;
	CString m_faddress;
	CString m_ftel;
	CString m_finfo;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
