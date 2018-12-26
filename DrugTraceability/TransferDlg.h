#pragma once
#include "Login.h"

// CTransfer 对话框

class CTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CTransfer)

public:
	CLogin *m_login;
	CTransfer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTransfer();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_TRANSFER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedDrugprod();
	afx_msg void OnBnClickedDrugsearch();
	afx_msg void OnBnClickedDicread();
};
