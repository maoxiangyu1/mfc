#pragma once
#include "Admin.h"

// CDrugregister 对话框

class CDrugregister : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugregister)

public:
	CAdmin *m_admin;
	CDrugregister(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugregister();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DURGREGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_DID;
	CString m_Dname;
	CString m_Dinfo;
};
