/////////////////////////////////////////////////////////////////////////
///@system ��Ͷϵͳ������
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CProbeLogger.h
///@brief	����̽��Ľӿ�
///@history 
///20060716	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////
#ifndef CPROBELOGGER_H
#define CPROBELOGGER_H

#include "platform.h"

#define MAX_PARAMETER_NAME 100

class CProbeLogger
{
private:
	const char *m_programName;
	int m_globalSeq;
public:
	///���췽��
	///@param	programName	ָ���ĳ�����
	///@param	globalSeq	����ȫ�����к�
	CProbeLogger(const char *programName, const int globalSeq)
	{
		m_programName=programName;
		m_globalSeq=globalSeq;
	}
	
	///��������
	virtual ~CProbeLogger(void)
	{
	}

	///����̽����Ϣ��ֵΪ�ַ���
	///@param	parameter	������
	///@param	value	Ҫ���͵���Ϣ
	void SendProbeMessage(const char *parameter, const char *value);

	///����̽����Ϣ��ֵΪ����
	///@param	parameter	������
	///@param	value	Ҫ���͵���Ϣ
	void SendProbeMessage(const char *parameter, const int value);

	///����̽����Ϣ��ֵΪ������
	///@param	parameter	������
	///@param	value	Ҫ���͵���Ϣ
	void SendProbeMessage(const char *parameter, const double value);

	///����̽����Ϣ��ֵΪ���������԰ٷֱȷ�ʽ��ʾ
	///@param	parameter	������
	///@param	value	Ҫ���͵���Ϣ
	void SendPercentageProbeMessage(const char *parameter, const double value);
protected:
	/**
	 * ����ʵ����η�����Ϣ
	 * @param programName ������
	 * @param globalSeq ����ȫ�����к�
	 * @param parameter �������ָ��
	 * @param value ����ֵ
	 */
	virtual void SendProbeMessageImpl
	(
		const char *programName,
		const int globalSeq,
		const char *parameter,
		const char *value
	) = 0;
};

#endif
