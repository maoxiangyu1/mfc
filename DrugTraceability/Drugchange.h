#pragma once
#include "Drugsearch.h"

// CDrugchange 对话框

class CDrugchange : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugchange)

public:
	CDrugsearch *m_drugsearch;
	CDrugchange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugchange();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DRUGCHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_did;
	CString m_dname;
	CString m_dinfo;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
