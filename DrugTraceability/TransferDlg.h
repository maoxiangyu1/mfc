#pragma once
#include "Login.h"

// CTransfer �Ի���

class CTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CTransfer)

public:
	CLogin *m_login;
	CTransfer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTransfer();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_TRANSFER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDrugprod();
	afx_msg void OnBnClickedDrugsearch();
	afx_msg void OnBnClickedDicread();
};
