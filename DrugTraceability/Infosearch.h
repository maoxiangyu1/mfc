#pragma once
#include "ProducerDlg.h"
#include "DrugstoreDlg.h"
#include "TransferDlg.h"
// CInfosearch 对话框

class CInfosearch : public CDialogEx
{
	DECLARE_DYNAMIC(CInfosearch)

public:
	CADODatabase * pDB;
    CADORecordset* pRs;
	CString HID;
	CProducer *m_Producer;
	CDrugstore *m_Drugstore;
	CTransfer *m_Transfer;
	CInfosearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInfosearch();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_INFOSEARCK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	BOOL RefreshList(CADORecordset& recordset);
	virtual BOOL OnInitDialog();
	CListCtrl m_listPerson;
	afx_msg void OnBnClickedSearch();
};
