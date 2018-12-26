#pragma once
#include "Admin.h"

// CAD 对话框

class CAD : public CDialogEx
{
	DECLARE_DYNAMIC(CAD)

public:
	CAdmin *m_admin;
	CADODatabase * pDB;
    CADORecordset* pRs;
	CAD(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAD();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_AD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CComboBox m_cbox1;
	CComboBox m_cbox2;
	CString m_time;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_FID;
	CString m_DID;
	CString m_Fname;
	CString m_Dname;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo2();
};
