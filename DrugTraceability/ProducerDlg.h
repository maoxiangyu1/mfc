#pragma once
#include "Login.h"
//#include "WriteIc.h"
// CProducer 对话框

class CProducer : public CDialogEx
{
	DECLARE_DYNAMIC(CProducer)

public:
	//price p;
	//读卡器数据
	//CWriteIc m_WriteIC;
	//unsigned int snr;
	//==========
	CLogin *m_login;
	CProducer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProducer();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_PRODUCER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDrugprod();
	afx_msg void OnClose();
	afx_msg void OnBnClickedDrugsearch();
	afx_msg void OnBnClickedDicread();
};
