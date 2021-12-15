//**********************************************************************
//�ļ����� 		DBUserImpAPI.h
//��Ҫ����:		mysql�ڲ�ʹ�ýӿ�
//��  �ߣ�      ����ʤ
//˵    ����    
//�÷�˵����
//�޸���ʷ��
//**********************************************************************
#ifndef __DBUSERIMPAPI_H__
#define __DBUSERIMPAPI_H__

#ifdef WIN32
#include <winsock.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif
#include "mysql.h"

//���ݿ�API
class  DBUserImpAPI
{
public:
    //���캯��,��ʼ��SQLAPI
    DBUserImpAPI();
    
    //��������
	~DBUserImpAPI();

	//��ʼ�����ݿ�
	static bool init_database_library(); 

//��������
public:

	//�������ݿ�
	bool ConnectToDB(char* pIP, char* pUser, char* pPassword, char* pDBName);

	//�ر����ݿ�
    void CloseDB();
	
	/*
	 * ȡ���ݿ�ִ�д������
	 * @return ����ִ�д�����
	 */
	int GetDBErrCode();
	
	/*
	 * ȡ���ݿ�ִ�д�����Ϣ
	 * @return ����ִ�д�����Ϣ
	 */              
	const char * GetDBErrInfo(); 


//���뷽ʽ
public:	
	/*
	 * ִ��SQL���
	 * @param lpSqlBuf  SQL���
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int Execute(char const *lpSqlBuf);

	int GetAffactRow();
	
	/*
	 * �����ύ
	 */
	bool Commit(); 
	
	/*
	 * ����ع�
	 */
	bool RollBack();
		
	/*
	 * ������ĸ���
	 * @return ���������
	 */
	int GetFieldCount();

	/*
	 * ȡ�α���һ����¼
	 * @return true��ʾ���б�ȡ�� false��ʾû���µ�����
	 */
	bool FetchNext(); 
	
	/*
	 * ��ȡ���ַ�������
	 * @param lpFieldName ��������
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetByte(const char *lpFieldName, char& FieldData);  

	/*
	 * ��ȡ�ַ�������
	 * @param lpFieldName ��������
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetString(const char *lpFieldName, char* FieldData);  
	
	/*
	 * ��ȡ˫������
	 * @param lpFieldName ��������
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetDouble(const char *lpFieldName, double& lpFieldData);
	
	/*
	 * ��ȡ��������
	 * @param lpFieldName ��������
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetLong  (const char *lpFieldName, long& lpFieldData);  
	
	/*
	 * ��ȡ������
	 * @param lpFieldName ��������
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetInt (const char *lpFieldName, int& lpFieldData); 

	/*
	 * ��ȡ�ֶ�����
	 * @param index       ������˳��:��0��ʼ
	 * @param fieldname   ��ȡ�ֶ�����
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int GetFieldName(unsigned int index, char* fieldname);
	
	/*
	 * ��ȡ���ַ�������
	 * @param index       ������˳��:��0��ʼ
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetByte(unsigned int index, char& FieldData);

	/*
	 * ��ȡ�ַ�������
	 * @param index       ������˳��:��0��ʼ
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetString(unsigned int index, char* FieldData);  
	
	/*
	 * ��ȡ˫������
	 * @param index       ������˳��:��0��ʼ
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetDouble(unsigned int index, double& lpFieldData);
	
	/*
	 * ��ȡ��������
	 * @param index       ������˳��:��0��ʼ
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetLong  (unsigned int index, long& lpFieldData);  
	
	/*
	 * ��ȡ������
	 * @param index       ������˳��:��0��ʼ
	 * @param FieldData   ��ȡ����������
	 * @return 0��ʾ�����ɹ� -1��ʾ����ʧ��
	 */
	int  GetInt (unsigned int index, int& lpFieldData); 

private:
	MYSQL        m_mydata;
	MYSQL_RES*   m_result;
	MYSQL_ROW    m_row;
};

#endif
