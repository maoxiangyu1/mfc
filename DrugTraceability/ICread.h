#pragma once
#include "WriteIc.h"

// CICread �Ի���

class CICread : public CDialogEx
{
	DECLARE_DYNAMIC(CICread)

public:
	price p;
	//CAdmin *m_admin;
	CWriteIc m_WriteIC;
	unsigned int snr;
	CICread(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CICread();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_ICREAD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	virtual BOOL OnInitDialog();
//	CString m_info;
//	CEdit m_c;
	CString m_info;
	afx_msg void OnPaint();
};
