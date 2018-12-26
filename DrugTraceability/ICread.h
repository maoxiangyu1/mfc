#pragma once
#include "WriteIc.h"

// CICread 对话框

class CICread : public CDialogEx
{
	DECLARE_DYNAMIC(CICread)

public:
	price p;
	//CAdmin *m_admin;
	CWriteIc m_WriteIC;
	unsigned int snr;
	CICread(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CICread();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_ICREAD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CString m_info;
//	CEdit m_c;
	CString m_info;
	afx_msg void OnPaint();
};
