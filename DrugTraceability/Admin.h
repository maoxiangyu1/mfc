#pragma once
#include "Login.h"

// CAdmin �Ի���

class CAdmin : public CDialogEx
{
	DECLARE_DYNAMIC(CAdmin)

public:
	CLogin *m_login;
	CAdmin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdmin();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_ADMIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedChangekey();
	afx_msg void OnBnClickedRegsiterfirm();
	afx_msg void OnBnClickedSearchfirm();
	afx_msg void OnBnClickedRegsiterdrug();
	afx_msg void OnBnClickedSearchdrug();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedDa();
	afx_msg void OnBnClickedReadic();
};
