#pragma once
#include "Firmsearch.h"

// CFirmchange �Ի���

class CFirmchange : public CDialogEx
{
	DECLARE_DYNAMIC(CFirmchange)

public:
	CFirmsearch *m_firmsearch;
	CFirmchange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFirmchange();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_FIRMCHANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	CString m_fname;
	CString m_fboss;
	CString m_faddress;
	CString m_ftel;
	CString m_finfo;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
