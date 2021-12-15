#include "dbf_file.h"

CDbfFile::CDbfFile()
{
	m_binaryBuffer = new char[4096];
}

CDbfFile::~CDbfFile()
{
}

int CDbfFile::OpenDbfFile(char* pDbfFilePath)
{
	int nRet = m_dbf_handle.d4use(pDbfFilePath);
	return nRet;
}

int CDbfFile::CreateDbfFile(char* pDbfFilePath, int nFieldNum, TField* pDbfFieldStruct)
{
	int nRet = m_dbf_handle.d4create(pDbfFilePath, nFieldNum, pDbfFieldStruct);
	return nRet;
}
	
void CDbfFile::ReadDbfRecord(void* pDataBuffer)
{
	m_dbf_handle.d4getbuffer(pDataBuffer);
	return;
}
	
int CDbfFile::WriteDbfRecord(void* pDataBuffer)
{
    int nRet = m_dbf_handle.d4append(pDataBuffer);
	return nRet;
}

int CDbfFile::WriteDbfBlank()
{
	int nRet = m_dbf_handle.d4append_blank();
	return nRet;
}

int CDbfFile::InitRecordBuffer()
{
	int nRet = m_dbf_handle.d4b_blank();
	return nRet;
}

int CDbfFile::GetRecordNum()
{
	int nRet = (int)m_dbf_handle.d4reccount();
	return nRet;
}

int CDbfFile::GetRecordLen()
{
    int nRecLen = m_dbf_handle.d4reclen();
	return nRecLen;
}


int CDbfFile::GetFieldCount()
{
    int nRecLen = m_dbf_handle.f4getfieldcount();
	return nRecLen;
}


TField * CDbfFile::getFieldinfo(int fieldno)
{
    TField * tField = m_dbf_handle.f4field(fieldno);
	return tField;
}


void CDbfFile::LocateRecordLine(int nRecordLineNo)
{
	m_dbf_handle.d4go(nRecordLineNo);
}

int CDbfFile::CloseDbfFile()
{
	int nRet = m_dbf_handle.d4close();
	return nRet;
}

double CDbfFile::GetDouble(char *fieldname)
{
    return m_dbf_handle.f4double(fieldname);
}

int CDbfFile::GetInt(char *fieldname)
{
    return m_dbf_handle.f4int(fieldname);
}

long CDbfFile::GetLong(char *fieldname)
{
    return m_dbf_handle.f4long(fieldname);
}

char* CDbfFile::GetString(char *fieldname)
{
    return m_dbf_handle.f4str(fieldname);
}

char* CDbfFile::GetDate(char *fieldname)
{
    return m_dbf_handle.f4str(fieldname);
}

//ȡ������
void* CDbfFile::GetBinary(char *fieldname)
{
    return m_dbf_handle.f4bstr(fieldname);
}

int CDbfFile::SetString(char *fieldname, char *pValue)
{
	return m_dbf_handle.f4r_field(fieldname, (void *)pValue);
}

int CDbfFile::SetInt(char *fieldname, int data)
{
    char fieldBuffer[128];
	memset(fieldBuffer, 0, sizeof(fieldBuffer));
	sprintf(fieldBuffer, "%d", data);
	return m_dbf_handle.f4r_field(fieldname, (void *)fieldBuffer);
}

int CDbfFile::SetLong(char *fieldname, long data)
{
    char fieldBuffer[128];
	memset(fieldBuffer, 0, sizeof(fieldBuffer));
	sprintf(fieldBuffer, "%ld", data);
	return m_dbf_handle.f4r_field(fieldname, (void *)fieldBuffer);
}

int CDbfFile::SetDouble(char *fieldname, double data)
{
    char fmt[10];
	char fieldBuffer[128];
	TField *f_ptr = m_dbf_handle.f4findfield(fieldname);

	memset(fieldBuffer, 0, sizeof(fieldBuffer));
    sprintf(fmt,"%%%d.%dlf", f_ptr->len, f_ptr->bits);
	sprintf(fieldBuffer, fmt, data);

	return m_dbf_handle.f4r_field(fieldname, (void *)fieldBuffer);
}

int CDbfFile::SetDate(char *fieldname, char *pValue)
{
	return m_dbf_handle.f4r_field(fieldname, (void *)pValue);
}

int CDbfFile::SetBinary(char *fieldname, void *bin, int blen)
{
	memcpy(m_binaryBuffer, bin, blen);
	return m_dbf_handle.f4r_field(fieldname, (void *)m_binaryBuffer);
}

//�����ֶ�ֵ���������������ַ������ͣ�
int CDbfFile::SetStringBuffer(char *fieldname,const char *pValue)
{
    return m_dbf_handle.f4b_str(fieldname, pValue);
}

//�����ֶ�ֵ���������������������ͣ�
int CDbfFile::SetIntBuffer(char *fieldname, int data)
{
    return m_dbf_handle.f4b_int(fieldname, data);
}

int CDbfFile::SetLongBuffer(char *fieldname, long data)
{
    return m_dbf_handle.f4b_long(fieldname, data);
}

//�޸��ֶ�ֵ�����������������������ͣ�	
int CDbfFile::SetDoubleBuffer(char *fieldname, double data)
{
    return m_dbf_handle.f4b_double(fieldname, data);
}

//�޸��ֶ�ֵ���������������������ͣ�	
int CDbfFile::SetDateBuffer(char *fieldname, char *pValue)
{
    return m_dbf_handle.f4b_str(fieldname, pValue);
}

//�޸��ֶ�ֵ�����������������������ͣ�
int CDbfFile::SetBinaryBuffer(char *fieldname, void *bin, int blen)
{
    return m_dbf_handle.f4b_binary(fieldname, bin, blen);
}

//ȡһ����¼���ݷŵ���������
void CDbfFile::GetRecordBuffer(char* record_buf)
{
    m_dbf_handle.d4getbuffer(record_buf);
}

int CDbfFile::WriteBatchRecords(int from, int records, void *buf)
{
    return m_dbf_handle.d4writerecords(from, records, buf);
}

//д��������
int CDbfFile::WriteEndFlag()
{
    return m_dbf_handle.writeEndFlag();
}