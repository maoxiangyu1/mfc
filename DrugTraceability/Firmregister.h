#pragma once
#include "Admin.h"

// CFirmregister �Ի���

class CFirmregister : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmregister)

public:
	CAdmin *m_admin;
	CFirmregister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirmregister();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_REGISTERFIRM_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
