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

	/**获取流中已经有的对象的个数
	*@return 对象的个数
	*/
	virtual int GetCount(void);
	
	/**获取指向该流长度的指针
	*@return	指向该流长度的指针
	*/
	virtual const int *GetCountPtr(void);

	/**获取流的通讯阶段序号
	*@return 流的通讯阶段序号
	*/
	virtual WORD GetCommPhaseNo();

	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length);

	/**设置流的通讯阶段序号
	*@param nCommPhaseNo 要设置的流的通讯阶段序号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);

	/**将流尾部的对象截掉
	*@param nCount 保留的对象的个数
	*@return true 操作成功； false 操作失败
	*/
	virtual bool Truncate(int nCount); 

	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
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
