#pragma once
#include "Login.h"

// CDrugstore �Ի���

class CDrugstore : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugstore)

public:
	CLogin *m_login;
	CDrugstore(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugstore();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DRUGSTORE_DIALOG };

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
