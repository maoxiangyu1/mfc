// WriteIc.h: interface for the CWriteIc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WRITEIC_H__76FBFAC9_BF6D_4CAF_AF9A_290854649404__INCLUDED_)
#define AFX_WRITEIC_H__76FBFAC9_BF6D_4CAF_AF9A_290854649404__INCLUDED_



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef int (__stdcall *Set_PortAdrr)(int zh,int jh,int port);
typedef int (__stdcall *Detect_FkjAdrr)(); 
typedef int (__stdcall *Get_Fkj_TypeAdrr)(char *s); 
typedef int (__stdcall *Get_Fkj_VerAdrr)(char *s);
typedef int (__stdcall *Beep1Adrr)(int itime);
typedef int (__stdcall *LampAdrr)(int itime);
typedef int (__stdcall *RFConfigAdrr)(int mode,int baud);
typedef int (__stdcall *RFRequestAdrr)(int mode,int *tagtype);
typedef int (__stdcall *RFAnticollAdrr)(int bcnt,unsigned int *snr); 
typedef int (__stdcall *RFSelectAdrr)(unsigned long int snr,int *size);
typedef int (__stdcall *RFLoadKeyAdrr)(int mode,int secnr,char *nkey); 
typedef int (__stdcall *RFAuthenticationAdrr)(int mode,int secnr); 
typedef int (__stdcall *RFReadAdrr)(int addr,char *data);
typedef int (__stdcall *RFWriteAdrr)(int addr,char *data);
typedef int (__stdcall *RFHaltAdrr)();
typedef int (__stdcall *RFResetAdrr)(int itime); 
typedef int (__stdcall *RFReadAAdrr)(unsigned long int &snr,int addr,char *data,char *key);
typedef int (__stdcall *RFWriteAAdrr)(unsigned long int snr,int addr,char *data,char *key);



class CWriteIc
{
public:
	CWriteIc();
	virtual ~CWriteIc();
	void initData();
	BOOL LoadDll();

public:
	Set_PortAdrr Set_port;
    Detect_FkjAdrr Detect_Fkj;
    Get_Fkj_TypeAdrr Get_Fkj_Type;
    Get_Fkj_VerAdrr Get_Fkj_Ver;
    Beep1Adrr Beep;
    LampAdrr Lamp;
    RFConfigAdrr RFConfig;
    RFRequestAdrr RFRequest;
	RFAnticollAdrr RFAnticoll;
	RFSelectAdrr RFSelect;
	RFLoadKeyAdrr RFLoadKey;
	RFAuthenticationAdrr RFAuthentication;
	RFReadAdrr RFRead;
	RFWriteAdrr RFWrite;
	RFHaltAdrr RFHalt;
	RFResetAdrr RFReset;
	RFReadAAdrr RFReadA;
	RFWriteAAdrr RFWriteA;

private:
	HINSTANCE hDll1;
	HINSTANCE hDll2;   
	HINSTANCE hDll3;
	HINSTANCE hDll4;
};

#endif // !defined(AFX_WRITEIC_H__76FBFAC9_BF6D_4CAF_AF9A_290854649404__INCLUDED_)
