#pragma once
#include "Login.h"
//#include "WriteIc.h"
// CProducer �Ի���

class CProducer : public CDialogEx
{
	DECLARE_DYNAMIC(CProducer)

public:
	//price p;
	//����������
	//CWriteIc m_WriteIC;
	//unsigned int snr;
	//==========
	CLogin *m_login;
	CProducer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProducer();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_PRODUCER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDrugprod();
	afx_msg void OnClose();
	afx_msg void OnBnClickedDrugsearch();
	afx_msg void OnBnClickedDicread();
};
