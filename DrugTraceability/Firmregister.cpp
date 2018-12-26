// Firmregister.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "DrugTraceability.h"
#include "Firmregister.h"
#include "afxdialogex.h"
#include <time.h>

// CFirmregister �Ի���

IMPLEMENT_DYNAMIC(CFirmregister, CDialogEx)

CFirmregister::CFirmregister(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirmregister::IDD, pParent)
{

	EnableAutomation();

	m_Fname = _T("");
	m_Fboss = _T("");
	m_Faddress = _T("");
	m_Ftel = _T("");
	m_Finfo = _T("");
	m_Ftype = _T("");
}

CFirmregister::~CFirmregister()
{
}

void CFirmregister::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialogEx::OnFinalRelease();
}

void CFirmregister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Fname);
	DDX_Text(pDX, IDC_EDIT2, m_Fboss);
	DDX_Text(pDX, IDC_EDIT3, m_Faddress);
	DDX_Text(pDX, IDC_EDIT4, m_Ftel);
	DDX_Text(pDX, IDC_EDIT6, m_Finfo);
	DDX_CBString(pDX, IDC_COMBO5, m_Ftype);
}


BEGIN_MESSAGE_MAP(CFirmregister, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFirmregister::OnBnClickedOk)
	ON_BN_CLICKED(IDRESET, &CFirmregister::OnBnClickedReset)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirmregister, CDialogEx)
END_DISPATCH_MAP()

// ע��: ������� IID_IFirmregister ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {DB93E26D-1CBC-4EA4-8FB3-9FE92733DC42}
static const IID IID_IFirmregister =
{ 0xDB93E26D, 0x1CBC, 0x4EA4, { 0x8F, 0xB3, 0x9F, 0xE9, 0x27, 0x33, 0xDC, 0x42 } };

BEGIN_INTERFACE_MAP(CFirmregister, CDialogEx)
	INTERFACE_PART(CFirmregister, IID_IFirmregister, Dispatch)
END_INTERFACE_MAP()


// CFirmregister ��Ϣ�������


void CFirmregister::OnBnClickedOk()
{
	UpdateData(true);
	if(m_Fname==""||m_Fboss==""||m_Faddress==""||m_Ftel==""||m_Finfo==""||m_Ftype=="")
	{
		AfxMessageBox("��˾��Ϣ��������");
		return;
	}
	int dwRet = 0;	
	BYTE seed[32];
	char AdminPin [] = "FFFFFFFFFFFFFFFF";
	char UserPin [] = "12345678";
	char cPid[9];
	char cAdminPin[17];
	dwRet = Dongle_Enum(NULL, &m_admin->m_login->nCount);
	if (dwRet != DONGLE_SUCCESS && m_admin->m_login->nCount!=1)
	{
		AfxMessageBox("���Ӽ��ܹ�ʧ�ܣ�");
		return ;
	}
	dwRet = Dongle_Enum(m_admin->m_login->pDongleInfo, &m_admin->m_login->nCount);
	if(m_admin->m_login->pDongleInfo->m_PID!=0xFFFFFFFF)
	{
		AfxMessageBox("�����ռ��ܹ���");
		return;
	}
	GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд����ܹ���Ϣ������γ����ܹ���");
	dwRet = Dongle_Open(&(m_admin->m_login->hDongle),0 );
	*m_admin->m_login->pRemain=255;
	dwRet = Dongle_VerifyPIN(m_admin->m_login->hDongle, FLAG_ADMINPIN, AdminPin, m_admin->m_login->pRemain);
	memset(cPid, 0, 9);
	memset(cAdminPin, 0, 17);
	if(m_Ftype=="������")
	{
		memset(seed, 0x11, 32);
	}
	if(m_Ftype=="��תվ")
	{
		memset(seed, 0x22, 32);
	}
	if(m_Ftype=="ҩ��")
	{
		memset(seed, 0x33, 32);
	}
	dwRet = Dongle_GenUniqueKey(m_admin->m_login->hDongle, 32, seed, cPid, cAdminPin);
	dwRet = Dongle_ResetState(m_admin->m_login->hDongle);
	dwRet = Dongle_VerifyPIN(m_admin->m_login->hDongle, FLAG_ADMINPIN, cAdminPin,m_admin->m_login->pRemain );
	CString s,CHID="";
	//��ȡ���ܹ�HID
	for (int i = 0; i < 8; i++)
	{
		s.Format(_T("%02X"),m_admin->m_login->pDongleInfo->m_HID[i]);
		CHID=CHID+s;
	}
	for (int i = 0; i < 8; i++)
	{
		s.Format(_T("%02X"),m_admin->m_login->pDongleInfo->m_HID[i] & 0xAF);
		m_admin->m_login->HID=m_admin->m_login->HID+s;
	}
	char Upin[9];
	for(int i=0;i<8;i++)
	{
		Upin[i]=m_admin->m_login->HID[2*i];
	}
	Upin[8]='\0';
	dwRet = Dongle_ChangePIN(m_admin->m_login->hDongle, FLAG_USERPIN , UserPin,Upin , 255);
	dwRet = Dongle_ChangePIN(m_admin->m_login->hDongle, FLAG_ADMINPIN, cAdminPin,AdminPin ,255);
	dwRet = Dongle_ResetState(m_admin->m_login->hDongle);
	dwRet = Dongle_VerifyPIN(m_admin->m_login->hDongle, FLAG_ADMINPIN,AdminPin,m_admin->m_login->pRemain );
	if(m_Ftype=="������")
	{
		dwRet = Dongle_SetUserID(m_admin->m_login->hDongle,0x11111111);
	}
	if(m_Ftype=="��תվ")
	{
		dwRet = Dongle_SetUserID(m_admin->m_login->hDongle,0x22222222);
	}
	if(m_Ftype=="ҩ��")
	{
		dwRet = Dongle_SetUserID(m_admin->m_login->hDongle,0x33333333);
	}
	PRIKEY_FILE_ATTR priAttr;
	priAttr.m_Size = 1024;//Ҳ������2048
	priAttr.m_Type = FILE_PRIKEY_RSA;
	priAttr.m_Lic.m_Count =0xFFFFFFFF;//�ɵ��ô���
	priAttr.m_Lic.m_IsDecOnRAM = FALSE;//�Ƿ�Ϊ���ڴ��еݼ�
	priAttr.m_Lic.m_IsReset = FALSE;//��������Ƿ�ָ�������̬
	priAttr.m_Lic.m_Priv = 0;//�ɵ��õ���СȨ��
	dwRet = Dongle_CreateFile(m_admin->m_login->hDongle, FILE_PRIKEY_RSA, 0x0001, (void*)&priAttr);
	dwRet = Dongle_RsaGenPubPriKey(m_admin->m_login->hDongle, 0x0001, &m_admin->m_login->rsaPub, &m_admin->m_login->rsaPri);
	memcpy(m_admin->m_login->Rsapub,&m_admin->m_login->rsaPub,sizeof(RSA_PUBLIC_KEY));
	memcpy(m_admin->m_login->Rsapri,&m_admin->m_login->rsaPri,sizeof(RSA_PRIVATE_KEY));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 6656,m_admin->m_login->Rsapub , sizeof(RSA_PUBLIC_KEY));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 6920,m_admin->m_login->Rsapri , sizeof(RSA_PRIVATE_KEY));
	int nInDataLen = (128 -11);
	int nOutDataLen = 128;
	memcpy(m_admin->m_login->UKEY,Upin,sizeof(Upin));
	dwRet = Dongle_RsaPri(m_admin->m_login->hDongle, 0x0001, FLAG_ENCODE, m_admin->m_login->UKEY, nInDataLen,m_admin->m_login->UKEY , &nOutDataLen);
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 5632, m_admin->m_login->UKEY, 128);
	memset(m_admin->m_login->Uinfo1,0x00,sizeof(m_admin->m_login->Uinfo1));
	memset(m_admin->m_login->Uinfo2,0x00,sizeof(m_admin->m_login->Uinfo2));
	memset(m_admin->m_login->Uinfo3,0x00,sizeof(m_admin->m_login->Uinfo3));
	memset(m_admin->m_login->Uinfo4,0x00,sizeof(m_admin->m_login->Uinfo4));
	memset(m_admin->m_login->Uinfo5,0x00,sizeof(m_admin->m_login->Uinfo5));
	memcpy(m_admin->m_login->Uinfo1,m_Fname,m_Fname.GetLength());
	memcpy(m_admin->m_login->Uinfo2,m_Fboss,m_Fboss.GetLength());
	memcpy(m_admin->m_login->Uinfo3,m_Faddress,m_Faddress.GetLength());
	memcpy(m_admin->m_login->Uinfo4,m_Ftel,m_Ftel.GetLength());
	memcpy(m_admin->m_login->Uinfo5,m_Finfo,m_Finfo.GetLength());
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 4096,m_admin->m_login->Uinfo1 , sizeof(m_admin->m_login->Uinfo1));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 3584,m_admin->m_login->Uinfo2 , sizeof(m_admin->m_login->Uinfo2));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 4608,m_admin->m_login->Uinfo3 , sizeof(m_admin->m_login->Uinfo3));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 3072,m_admin->m_login->Uinfo4 , sizeof(m_admin->m_login->Uinfo4));
	dwRet = Dongle_WriteData(m_admin->m_login->hDongle, 0,m_admin->m_login->Uinfo5 , sizeof(m_admin->m_login->Uinfo5));
	GetDlgItem(IDC_STATIC23)->SetWindowText("��ʼд�����ݿ���Ϣ�����ʧ�������ü��ܹ���");
	CString m_Time;
	CTime t=CTime::GetCurrentTime();
	m_Time = t.Format("%Y-%m-%d");
	s.Format("insert into Firm values('%s','%s','%s','%s','%s','%s','%s','%s')",CHID,m_Fname,m_Fboss,m_Faddress,m_Ftel,m_Ftype,m_Finfo,m_Time);
	if(m_admin->m_login->pDB->Execute(s)==TRUE)
	{
		GetDlgItem(IDC_STATIC23)->SetWindowText("���ݿ���Ϣд��ɹ���");
		AfxMessageBox("ע��ɹ���");
		GetDlgItem(IDC_STATIC23)->SetWindowText("");
		this->EndDialog(0);
		return;
	}
	else
	{
		GetDlgItem(IDC_STATIC23)->SetWindowText("д�����ݿ�ʧ�ܣ������ü��ܹ���");
		AfxMessageBox("ע��ʧ�ܣ�");
		return;
	}
}


void CFirmregister::OnBnClickedReset()
{
	char AdminPin [] = "FFFFFFFFFFFFFFFF";
	if(!Dongle_VerifyPIN(m_admin->m_login->hDongle, FLAG_ADMINPIN,AdminPin,m_admin->m_login->pRemain) &&!Dongle_RFS(m_admin->m_login->hDongle))
	{
		GetDlgItem(IDC_STATIC23)->SetWindowText("���ܹ����óɹ���");
		AfxMessageBox("���óɹ���");
	}
	else
	{
		GetDlgItem(IDC_STATIC23)->SetWindowText("���ܹ�����ʧ�ܣ�");
		AfxMessageBox("����ʧ�ܣ�");
	}

}
