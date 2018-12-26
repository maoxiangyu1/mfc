#pragma once
#include "Admin.h"

// CDrugsearch �Ի���

class CDrugsearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugsearch)

public:
	CAdmin *m_admin;
	CDrugsearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugsearch();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DRUGSEARCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
