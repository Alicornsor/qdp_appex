// dbf_file.h: interface for the CDbfFile class.
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBFFILE_H__EBE57BE4_8FC9_427D_B221_FF8D6C806731__INCLUDED_)
#define AFX_DBFFILE_H__EBE57BE4_8FC9_427D_B221_FF8D6C806731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dbf.h"

class CDbfFile
{
public:
	CDbfFile();
	~CDbfFile();
	//��DBF�ļ�
	int OpenDbfFile(char* pDbfFilePath);
	//�����µ�DBF�ļ���������ṹ
	int CreateDbfFile(char* pDbfFilePath, int nFieldNum, TField* pDbfFieldStruct);
	//��DBF�ļ���ĳ�м�¼
	void ReadDbfRecord(void* pDataBuffer);
	//Append��ʽ��DBF�ļ���׷��ĳ�м�¼
	int WriteDbfRecord(void* pDataBuffer);
	//Append��ʽ��DBF�ļ���׷��һ���հ���
	int WriteDbfBlank();
	//�Կո��ʼ����¼��
	int InitRecordBuffer();
    //��λ��DBF�ļ�ĳ�м�¼��
    void LocateRecordLine(int nRecordLineNo);
	//ȡ�ֶ�ֵ������Double
	double GetDouble(char *fieldname);
	//ȡ�ֶ�ֵ������Int
    int GetInt(char *fieldname);
    //ȡ�ֶ�ֵ������Long
	long GetLong(char *fieldname);
    //ȡ�ֶ�ֵ������String
	char* GetString(char *fieldname);
    //ȡ�ֶ�ֵ������Date
    char* GetDate(char *fieldname);
    //ȡ�ֶ�ֵ������Binary
    void* GetBinary(char *fieldname);
	//�޸��ֶ�ֵ���ַ������ͣ�
	int SetString(char *fieldname, char *pValue);
	//�޸��ֶ�ֵ���������ͣ�
	int SetInt(char *fieldname, int data);
	//�޸��ֶ�ֵ�����������ͣ�
	int SetLong(char *fieldname, long data);
	//�޸��ֶ�ֵ�����������ͣ�	
	int SetDouble(char *fieldname, double data);
	//�����ֶ�ֵ���������ͣ�
	int SetDate(char *fieldname, char *pValue);
	//�޸��ֶ�ֵ�����������ͣ�
    int SetBinary(char *fieldname, void *bin, int blen);
	//�����ֶ�ֵ���������������ַ������ͣ�
	int SetStringBuffer(char *fieldname,  const char *pValue);
	//�����ֶ�ֵ���������������������ͣ�
	int SetIntBuffer(char *fieldname, int data);
	//�����ֶ�ֵ�����������������������ͣ�
	int SetLongBuffer(char *fieldname, long data);
	//�޸��ֶ�ֵ�����������������������ͣ�	
	int SetDoubleBuffer(char *fieldname, double data);
	//�����ֶ�ֵ���������������������ͣ�
	int SetDateBuffer(char *fieldname, char *pValue);
	//�޸��ֶ�ֵ�����������������������ͣ�
    int SetBinaryBuffer(char *fieldname, void *bin, int blen);
    //ȡһ����¼���ݷŵ���������
	void GetRecordBuffer(char* record_buf);
	//ȡDBF�ļ��ļ�¼��
    int GetRecordNum();
	//ȡDBF�ļ��ļ�¼�ĳ��ȣ��̶�ֵ��
	int GetRecordLen();
   //ȡDBF�ļ���ÿ���ֶ���
	int GetFieldCount();
    //ȡDBF�ļ���ÿ���ֶ�����Ϣ
	TField * getFieldinfo(int fieldno);
    //�ر�DBF�ļ�
	int CloseDbfFile();
    //��N�ʼ�¼����д��DBF�ļ�
	int WriteBatchRecords(int from, int records, void *buf);
	//д��������
    int WriteEndFlag();
private:
	CDBF m_dbf_handle;
	char *m_binaryBuffer;
};

#endif