#pragma once
#include "Admin.h"

// CKeychange �Ի���

class CKeychange : public CDialogEx
{
	DECLARE_DYNAMIC(CKeychange)

public:
	CAdmin *m_admin;
	CKeychange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CKeychange();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_CHANGEKEY_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:

	afx_msg void OnBnClickedOk();
	CString m_key1;
	CString m_key2;
	CString m_key3;
};
