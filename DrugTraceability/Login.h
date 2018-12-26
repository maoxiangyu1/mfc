
// Login.h : 头文件
//

#include"lib\ADO\ado.h"
#include"lib\Dongle\Dongle_API.h"
#pragma comment (lib,"lib\\Dongle\\Dongle_s.lib")
#pragma once


// CLogin 对话框
class CLogin : public CDialogEx
{
// 构造
public:
	//CWriteIc m_WriteIC;
	CString HID;
	int*pRemain;
	int UType;
	RSA_PUBLIC_KEY  rsaPub;
	RSA_PRIVATE_KEY rsaPri;
	BYTE Rsapri[520];   //私钥
	BYTE Rsapub[264];   //公钥
	BYTE UKEY[128];   //密码
	BYTE Uinfo1[512];   //公司名称
	BYTE Uinfo2[512];   //负责人
	BYTE Uinfo3[1024]; //地址
	BYTE Uinfo4[512]; //TEL
	BYTE Uinfo5[3072]; //简介
	int nCount;
	DONGLE_HANDLE hDongle;
	DONGLE_INFO *pDongleInfo;
	CADODatabase * pDB;
    CADORecordset* pRs;
	CLogin(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRUGTRACEABILITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedLogin();
};
