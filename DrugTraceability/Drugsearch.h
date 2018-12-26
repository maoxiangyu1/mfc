#pragma once
#include "Admin.h"

// CDrugsearch 对话框

class CDrugsearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugsearch)

public:
	CAdmin *m_admin;
	CDrugsearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugsearch();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DRUGSEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_DID;
	CString m_Dname;
	CString m_Dinfo;
	BOOL RefreshList(CADORecordset& recordset);
	virtual BOOL OnInitDialog();
	CListCtrl m_listPerson;
	CString m_type;
	CString m_key;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedChange();
};
