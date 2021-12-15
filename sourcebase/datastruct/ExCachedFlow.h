// CachedFlow.h: interface for the CCachedFlow class.
//
// 20070315 hwp ����CCachedFlow���߳�����
// 20090310 hwp ����DeatchUnderFlow����������ȡ����ҽӵ���(NT-0069)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_)
#define AFX_EXCACHEDFLOW_H__1A86ED0A_F5FE_4A27_A7AC_BCF24B77DCFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CachedFlow.h"

class CExCachedFlow : public CCachedFlow
{
public:
	/**���캯��
	* @param bSyncFlag �ڼ���һ�����ǣ��Ƿ�����ͬ�����ҽӵ�����
	*		 true����ͬ�����ҽӵ�����false��ͬ�����ҽӵ���
	* @param nMaxObjects ��������������,���Ϊ0�����ư��ĸ���
	* @param nDataBlockSize CacheListʹ�õ����������С����ҪС��һ�����ݰ��ĳ���
	*/
	CExCachedFlow(bool bSyncFlag, int nMaxObjects, int nDataBlockSize);
	
	/**��������
	*/
	virtual ~CExCachedFlow();



	/**����������һ������
	*@param	pObject Ҫ���ӵĶ���
	*@param length �������ݵĳ���
	*@return ���������е���ţ�С��0��ʾ����ʧ��
	*/
	virtual int Append(void *pObject, int length);

	/**������ĵ�һ�����ӻ���������ȥ
	*@return true ��ȥ��һ�����ɹ�
	*@return false ��ȥ��һ����ʧ��
	*/
	bool PopFront();

	//20150604 huwp ��Ӹú���
	virtual int Get(int id, void **pObject);

	
protected:

	volatile int m_iHaveGetID;


};

#endif // !defined(AFX_CACHEDFLOW_H__B7AC16F2_8521_4AC1_B445_30DDFE2F8F12__INCLUDED_)
