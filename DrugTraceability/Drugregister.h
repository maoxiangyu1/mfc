#pragma once
#include "Admin.h"

// CDrugregister �Ի���

class CDrugregister : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugregister)

public:
	CAdmin *m_admin;
	CDrugregister(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrugregister();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DURGREGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_DID;
	CString m_Dname;
	CString m_Dinfo;
};
