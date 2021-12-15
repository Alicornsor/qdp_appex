#ifndef __SUBSCRIBER_H_
#define __SUBSCRIBER_H_

#include "XTPPackage.h"

/** �����߽ӿڣ���Ҫ���ĵ�Ӧ�ü̳и��ࡣһ��������ֻ�ܶ���һ�����⡣
* �����߱���ָ��ͨѶ�׶���š��ѽ�����Ϣ���������ڿɿ�����
* ��ָ���������Ϣ�ִ�ʱ������������������HandleMessage�������û���
* �����ظ÷���������Ϣ���д���
*/
class CSubscriber
{
public:

	virtual ~CSubscriber(){};

	/**��ȡ�����ߵ�ͨѶ�׶α��
	*@return �����ߵ�ͨѶ�׶α��
	*/
	virtual WORD GetCommPhaseNo() = 0;
	
	/**���ö����ߵ�ͨѶ�׶α��
	*@param  nCommPhaseNo Ҫ���õĶ����ߵ�ͨѶ�׶α��
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo) = 0;

	/**��ȡ���ĵ��������
	*@return ���ĵ��������
	*/
	virtual DWORD GetSubjectID() = 0;

	/**��ȡ���յ�����Ϣ����
	*@return ���յ�����Ϣ����
	*/
	virtual DWORD GetReceivedCount() = 0;

	/**�����յ���һ����Ϣ
	*@param pMessage �յ���һ����Ϣ
	*/
	virtual void HandleMessage(CXTPPackage *pMessage) = 0;

	/**�Ƿ���ͨѶ�׶α�ŵ�һ����
	*@return true ��飬false �����
	*@remark �����ͨѶ�׶α�ŵ�һ���ԣ����յ�����Ϣ��ͨѶ�׶α���붩����
	*@remark ��ͨѶ�׶α�Ų�һ��ʱ������Ϣ����������
	*@remark �������ͨѶ�׶α�ŵ�һ���ԣ����յ�����Ϣ��ͨѶ�׶α���붩����
	*@remark ��ͨѶ�׶α�Ų�һ��ʱ����Ϣ�Ա��ύ���Ҷ����ߵ�SetCommPhaseNo����
	*@remark �ᱻ���á�
	*/
	virtual bool CheckCommPhaseNo()
	{
		return false;
	}

	/**�����ٽ���
	*/
	virtual void EnterCritical() {}
	
	/**�뿪�ٽ���
	*/
	virtual void LeaveCritical() {}

};

#endif

