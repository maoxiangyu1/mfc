#pragma once
#include "ProducerDlg.h"
#include "WriteIc.h"
#include "DrugstoreDlg.h"
#include "TransferDlg.h"
// CDrugp 对话框

class CDrugp : public CDialogEx
{
	DECLARE_DYNAMIC(CDrugp)

public:
	CADODatabase * pDB;
    CADORecordset* pRs;
	CString HID;
	CWriteIc m_WriteIC;
	unsigned int snr;
	CDrugstore *m_Drugstore;
	CTransfer *m_Transfer;
	CProducer *m_Producer;
	price p;
	CDrugp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrugp();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DRUGP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:

//	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_cbox;
	CString m_did;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeCombo1();
//	CString m_Dname;
	CString m_Dname;
//	CString m_Ip;
//	float m_Ip;
//	float m_Op;
//	CString m_Ip;
//	CString m_Op;
	float m_Ip;
	float m_Op;
};
