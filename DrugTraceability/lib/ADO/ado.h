#ifndef _ADO_H_
#define _ADO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


//����ado��
CString IntToStr(int nVal);

CString LongToStr(long lVal);
/////////////////////////////////////////////////////////////////////////////
//  CADODatabase class
class CADODatabase
{
public:
	/////////////////////////////////////////////////////////////////////////////
	// �������������
	CADODatabase()
	{
		//��ʼCOM��
		::CoInitialize(NULL);
			
		m_pConnection = NULL;
		m_strConnection = _T("");
		m_pConnection.CreateInstance(__uuidof(Connection));
	}
	
	~CADODatabase()
	{
		Close();
		m_pConnection.Release();
		m_pConnection = NULL;
		::CoUninitialize();
	}
	/////////////////////////////////////////////////////////////////////////////
	//�򿪹ر����ӡ��ж��Ƿ�򿪡�ִ�в����ؼ�¼��SQL����
	BOOL Open(LPCTSTR lpstrConnection = _T(""));
	void Close();
	BOOL IsOpen();	
	BOOL Execute(LPCTSTR lpstrExec);

	/////////////////////////////////////////////////////////////////////////////
	// ������
	long BeginTransaction() ;
	BOOL CommitTransaction();
	BOOL RollbackTransaction();
	/////////////////////////////////////////////////////////////////////////////
	//���úͻ�����Ӵ����������ָ�롢������Ϣ
	_ConnectionPtr GetActiveConnection() {return m_pConnection;};
	void SetConnectionString(LPCTSTR lpstrConnection)
		{m_strConnection = lpstrConnection;};
	CString GetConnectionString()
		{return m_strConnection;};
	CString GetLastError() 
		{return m_strLastError;};
protected:
	void dump_com_error(_com_error &e);

protected:
	_ConnectionPtr m_pConnection;
	CString m_strConnection;
	CString m_strLastError;
};

class CADORecordset
{
public:
	//δ֪��SQL��䡢���洢����
	enum cadoOpenEnum
	{
		openUnknown = 0,
		openQuery = 1,
		openTable = 2,
		openStoredProc = 3
	};
	enum cadoPositionEnum
	{
	
		positionUnknown = -1,
		positionBOF = -2,
		positionEOF = -3
	};
	//�������򣬶�Ӧ��ADO��
	enum cadoSearchEnum
	{	
		searchForward = 1,
		searchBackward = -1
	};
	/////////////////////////////////////////////////////////////////////////////
	//���졢��������
	CADORecordset()
	{
		m_pRecordset = NULL;
		m_strQuery = _T("");
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		m_nSearchDirection = CADORecordset::searchForward;
	}
	//����CADODatabase�������ʼ��
	CADORecordset(CADODatabase* pAdoDatabase);	
	~CADORecordset()
	{
		Close();
		m_pRecordset.Release();
		m_pRecordset = NULL;
		m_strQuery = _T("");
	}	
	/////////////////////////////////////////////////////////////////////////////
	//�򿪹رռ�¼��
	BOOL Open(_ConnectionPtr mpdb, LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	BOOL Open(LPCTSTR lpstrExec = _T(""), int nOption = CADORecordset::openUnknown);
	void Close();
	/////////////////////////////////////////////////////////////////////////////
	//��ü�¼�������жϼ�¼���Ƿ��
	DWORD GetRecordCount();
	BOOL IsOpen();
	/////////////////////////////////////////////////////////////////////////////
	//��ȡ�ֶ�
	BOOL SetFieldValue(int nIndex, CString strValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, CString strValue);
	BOOL SetFieldValue(int nIndex, int nValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, int nValue);
	BOOL SetFieldValue(int nIndex, long lValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, long lValue);
	BOOL SetFieldValue(int nIndex, double dblValue);
	BOOL SetFieldValue(LPCTSTR lpFieldName, double dblValue);
	BOOL SetFieldValue(int nIndex, COleDateTime time);
	BOOL SetFieldValue(LPCTSTR lpFieldName, COleDateTime time);

	BOOL GetFieldValue(LPCTSTR lpFieldName, double& dbValue);
	BOOL GetFieldValue(int nIndex, double& dbValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, long& lValue);
	BOOL GetFieldValue(int nIndex, long& lValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, int& nValue);
	BOOL GetFieldValue(int nIndex, int& nValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, CString& strValue);
	BOOL GetFieldValue(int nIndex, CString& strValue);
	BOOL GetFieldValue(LPCTSTR lpFieldName, COleDateTime& time);
	BOOL GetFieldValue(int nIndex, COleDateTime& time);
	/////////////////////////////////////////////////////////////////////////////
	//���¼�¼���ļ�¼
	BOOL Update();
	BOOL AddNew();
	BOOL Requery(long Options);
	BOOL Delete();
/*	
	BOOL IsFieldNull(LPCTSTR lpFieldName);
	BOOL IsFieldNull(int nIndex);
	BOOL IsFieldEmpty(LPCTSTR lpFieldName);
	BOOL IsFieldEmpty(int nIndex);	*/
	/////////////////////////////////////////////////////////////////////////////
	//�ж�λ��
	BOOL IsEOF();
	BOOL IsBOF();
	/////////////////////////////////////////////////////////////////////////////
	//������¼
	BOOL MoveFirst();		
	BOOL MoveNext(); 	
	BOOL MovePrevious();		
	BOOL MoveLast(); 	
	/////////////////////////////////////////////////////////////////////////////
	//������¼����õ�ǰ��¼��λ�����
	BOOL Find(LPCTSTR lpFind, int nSearchDirection);
	long GetAbsolutePosition();			
/*		void SetAbsolutePosition(int nPosition)
			{m_pRecordset->PutAbsolutePosition((enum PositionEnum)nPosition);};
		*/
	/////////////////////////////////////////////////////////////////////////////
	//����
	CString GetQuery() 
	{return m_strQuery;};
	void SetQuery(LPCSTR strQuery) 
	{m_strQuery = strQuery;};	
	/////////////////////////////////////////////////////////////////////////////
	//��ǩ����
	void GetBookmark();
	BOOL SetBookmark();	
	/////////////////////////////////////////////////////////////////////////////
	//������
	CString GetLastError() {return m_strLastError;};
protected:
	void dump_com_error(_com_error &e);

protected:
	_ConnectionPtr m_pConnection;	
	_RecordsetPtr m_pRecordset;
	int m_nSearchDirection;
	CString m_strFind;
//	_variant_t m_varBookFind;
	_variant_t m_varBookmark;
	CString m_strLastError;	
	CString m_strQuery;
	
};

#endif

