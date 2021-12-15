// AccomplishFlow.h: interface for the CAccomplishFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCOMPLISHFLOW_H__2F222B44_315B_4D0D_8085_5E359E6A5A26__INCLUDED_)
#define AFX_ACCOMPLISHFLOW_H__2F222B44_315B_4D0D_8085_5E359E6A5A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Flow.h"

class CDbConnection;
class SACommand;

class CAccomplishFlow : public CFlow  
{
public:
	CAccomplishFlow();
	virtual ~CAccomplishFlow();

	bool ConnectDB(const char *pszDatabaseName, const char *pszUserName, 
		const char *pszPassword);

	/**��ȡ�����Ѿ��еĶ���ĸ���
	*@return ����ĸ���
	*/
	virtual int GetCount(void);
	
	/**��ȡָ��������ȵ�ָ��
	*@return	ָ��������ȵ�ָ��
	*/
	virtual const int *GetCountPtr(void);

	/**��ȡ����ͨѶ�׶����
	*@return ����ͨѶ�׶����
	*/
	virtual WORD GetCommPhaseNo();

	/**��ȡָ����ŵĶ���
	*@param	id	�������
	*@param pObject ��ȡ����Ļ�����
	*@param length ��������С
	*@return ȡ������ĳ���
	*/
 	virtual int Get(int id, void *pObject, int length);

	/**��������ͨѶ�׶����
	*@param nCommPhaseNo Ҫ���õ�����ͨѶ�׶����
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);

	/**����β���Ķ���ص�
	*@param nCount �����Ķ���ĸ���
	*@return true �����ɹ��� false ����ʧ��
	*/
	virtual bool Truncate(int nCount); 

	/**����������һ������
	*@param	pObject Ҫ���ӵĶ���
	*@param length �������ݵĳ���
	*@return ���������е���ţ�С��0��ʾ����ʧ��
	*/
	virtual int Append(void *pObject, int length);

	void SetSystemID(const char *pSystemID);

	int GetSystemID(CDbConnection *pDbConnection,char *systemid);

private:
	bool Load();
	bool Save();

private:
	CDbConnection *m_pDbConnection;
	SACommand *m_pSACommand;

	WORD m_wCommPhaseNo;
	int m_nCount;
	char m_pSystemID[5];
};

#endif // !defined(AFX_ACCOMPLISHFLOW_H__2F222B44_315B_4D0D_8085_5E359E6A5A26__INCLUDED_)
