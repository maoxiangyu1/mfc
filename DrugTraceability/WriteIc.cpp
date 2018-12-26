// WriteIc.cpp: implementation of the CWriteIc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrugTraceability.h"
#include "Drugp.h"
#include "ICread.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWriteIc::CWriteIc()
{
	LoadDll();
}

CWriteIc::~CWriteIc()
{
	
}
void CWriteIc::initData()
{
	hDll1 =NULL;
	hDll2 =NULL;
	Set_port=NULL;
	Detect_Fkj=NULL;
	Get_Fkj_Type=NULL;
	Get_Fkj_Ver=NULL;
	Beep=NULL;
	Lamp=NULL;
	RFConfig=NULL;
	RFRequest=NULL;
	RFAnticoll=NULL;
	RFSelect=NULL;
	RFLoadKey=NULL;
	RFAuthentication=NULL;
	RFRead=NULL;
	RFWrite=NULL;
	RFHalt=NULL;
	RFReset=NULL;
	RFReadA=NULL;
	RFWriteA=NULL;
	
}
BOOL CWriteIc::LoadDll()
{
	initData();
	hDll3=::LoadLibrary(".\\lib\\Card\\pOne.dll");
	hDll4=::LoadLibrary(".\\lib\\Card\\pSer.dll");
	hDll1=::LoadLibrary(".\\lib\\Card\\PAgt.dll");
	hDll2=::LoadLibrary(".\\lib\\Card\\PFkj.dll");
	
	if (!hDll1 && !hDll2 && !hDll3 && !hDll4)
	{
		AfxMessageBox("µº»Î–¥ø®∆˜dll ß∞‹!");
		return FALSE;
	}	
	
	Set_port=(Set_PortAdrr)GetProcAddress(hDll1,"Set_Port");
	Detect_Fkj=(Detect_FkjAdrr)GetProcAddress(hDll2,"Detect_Fkj");
	Get_Fkj_Type=(Get_Fkj_TypeAdrr)GetProcAddress(hDll2,"Get_Fkj_Type");
	Get_Fkj_Ver=(Get_Fkj_VerAdrr)GetProcAddress(hDll2,"Get_Fkj_Ver");
	Beep=(Beep1Adrr)GetProcAddress(hDll2,"Beep");
	Lamp=(LampAdrr)GetProcAddress(hDll2,"Lamp");
	RFConfig=(RFConfigAdrr)GetProcAddress(hDll2,"RFConfig");
	RFRequest=(RFRequestAdrr)GetProcAddress(hDll2,"RFRequest");
	RFAnticoll=(RFAnticollAdrr)GetProcAddress(hDll2,"RFAnticoll");
    RFSelect=(RFSelectAdrr)GetProcAddress(hDll2,"RFSelect");
	RFLoadKey=(RFLoadKeyAdrr)GetProcAddress(hDll2,"RFLoadKey");
	RFAuthentication=(RFAuthenticationAdrr)GetProcAddress(hDll2,"RFAuthentication");
	RFRead=(RFReadAdrr)GetProcAddress(hDll2,"RFRead");
	RFWrite=(RFWriteAdrr)GetProcAddress(hDll2,"RFWrite");
	RFHalt=(RFHaltAdrr)GetProcAddress(hDll2,"RFHalt");
	RFReset=(RFResetAdrr)GetProcAddress(hDll2,"RFReset");
	RFReadA=(RFReadAAdrr)GetProcAddress(hDll2,"RFReadA");
	RFWriteA=(RFWriteAAdrr)GetProcAddress(hDll2,"RFWriteA");
//	TRACE( "Integer = %d", Set_port );
	return true;
}
