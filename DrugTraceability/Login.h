
// Login.h : ͷ�ļ�
//

#include"lib\ADO\ado.h"
#include"lib\Dongle\Dongle_API.h"
#pragma comment (lib,"lib\\Dongle\\Dongle_s.lib")
#pragma once


// CLogin �Ի���
class CLogin : public CDialogEx
{
// ����
public:
	//CWriteIc m_WriteIC;
	CString HID;
	int*pRemain;
	int UType;
	RSA_PUBLIC_KEY  rsaPub;
	RSA_PRIVATE_KEY rsaPri;
	BYTE Rsapri[520];   //˽Կ
	BYTE Rsapub[264];   //��Կ
	BYTE UKEY[128];   //����
	BYTE Uinfo1[512];   //��˾����
	BYTE Uinfo2[512];   //������
	BYTE Uinfo3[1024]; //��ַ
	BYTE Uinfo4[512]; //TEL
	BYTE Uinfo5[3072]; //���
	int nCount;
	DONGLE_HANDLE hDongle;
	DONGLE_INFO *pDongleInfo;
	CADODatabase * pDB;
    CADORecordset* pRs;
	CLogin(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRUGTRACEABILITY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedLogin();
};
