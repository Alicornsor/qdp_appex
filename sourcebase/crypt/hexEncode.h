/////////////////////////////////////////////////////////////////////////
///@system �ײ�֧��
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file hexEncode.h
///@brief	������16���Ʊ������Ľӿ�
///@history 
///20080425	xuzh		�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef HEX_ENCODE_H
#define HEX_ENCODE_H

#include "platform.h"

/////////////////////////////////////////////////////////////////////////
///CHexEncoder��һ������16���Ʊ���ı�����
///@author	xuzh
///@version	1.0,20080425
/////////////////////////////////////////////////////////////////////////
class CHexEncoder
{
public:
	///���췽��
	CHexEncoder(void);
	virtual ~CHexEncoder(){};
	
	///���뷽��
	///@param	buffer	�����������Ŀռ�
	///@param	bufferLen	�������ռ�ĳ���
	///@param	input	����Ĵ�������ַ���
	///@param	inputLen	�����ַ����ĳ��ȣ����Ϊ-1��ʾ�ַ�����'\0'��β
	///@return	true��ʾ�ɹ���false��ʾʧ�ܣ�ʧ�ܵ�Ψһԭ�����������Ŀռ䲻��
	virtual bool encode(char *buffer, int bufferLen, const char *input, int inputLen=-1);
	
	///����������ĳ���
	///@param	input	����Ĵ�������ַ���
	///@param	inputLen	�����ַ����ĳ��ȣ����Ϊ-1��ʾ�ַ�����'\0'��β
	///@return	����ĳ���
	virtual int encodeLen(const char *input, int inputLen=-1);
};

#endif
