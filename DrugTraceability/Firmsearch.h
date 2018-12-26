#pragma once
#include "Admin.h"

// CFirmsearch �Ի���

class CFirmsearch : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmsearch)

public:
	CAdmin *m_admin;
	CFirmsearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirmsearch();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_FIRMSEARCK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_FID;
	CString m_Fname;
	CString m_Fboss;
	CString m_Faddress;
	CString m_Ftel;
	CString m_Finfo;
	CString m_key;
	CString m_type;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSearch();
	CListCtrl m_listPerson;
	BOOL RefreshList(CADORecordset& recordset);
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedChange();
};
