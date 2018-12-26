#pragma once
#include "ProducerDlg.h"
#include "DrugstoreDlg.h"
#include "TransferDlg.h"
// CInfosearch �Ի���

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
	CInfosearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfosearch();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_INFOSEARCK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	BOOL RefreshList(CADORecordset& recordset);
	virtual BOOL OnInitDialog();
	CListCtrl m_listPerson;
	afx_msg void OnBnClickedSearch();
};
