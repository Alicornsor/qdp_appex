/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ��ڻ���Ϣ�������޹�˾
///@file CXML.h
///@brief��������DBF�����йص���ӿ�
///@history 
///20060104 ���ض�	�������ļ�
///20061113 ��ϰƽ  ������setDoubleField����
///20100831 ���һ�  ����getField,rtrim,ltrim,void printAll����
///20121114 ���һ�	����readRecords,getRecWidth,getFieldCount����
/////////////////////////////////////////////////////////////////////////

/* current ristriction
	1 can not write to dbf file with memo
	2 can not write to number field with decimal easily
	3 can not delete a field actually
	4 �ӿ����ṩ���Ƕ��ļ��Ĳ����������Ҫһ�ν��ļ������ڴ棬Ȼ��ȡ�ֶ���Ҫʹ��readRecords,�Լ�����
*/

#ifndef DBF_H
#define DBF_H

#include "platform.h"
#include "system.h"

#define MAX_MEMO_FIELD 20480

const int fieldNameSize = 11;

class CFieldDefine
{
public:
	char name[fieldNameSize];
	char type;
	unsigned char length1;
	unsigned char length2;
	short length;
	int offset;
};

class CDBF
{
public:
	///���캯��
	CDBF(void);
	
	///�������������ڴ򿪵����ݿ⣬���Զ��ر�
	~CDBF(void);
	
	///��ֻ����ʽ��DBF�ļ���Ŀǰ֧��DBASE��FOXPRO�õ�DBF�ļ�
	///@param	database	DBF�ļ���
	///@return	1��ʾ�ɹ���0��ʾʧ��
	/// ���ļ�֮ǰ�رմ򿪵��ļ������Դ�֮�󣬲���Ҫclose
	int open(char *database);
	
	///�Կ�д��ʽ��DBF�ļ�������memo�ֶε�д��
	///@param	database	DBF�ļ���
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int openForWrite(char *database);

	///�ر�DBF�ļ�
	void close(void);

	///��ȡһ���ֶε�ֵ
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	pLength	���صĳ���
	///@return	�õ����ֶ�ֵ��������pLengthָ����ͬʱ��\0��β������Ҳ����ֶΣ��򷵻�NULL
	char *getField(char *fieldName,int recno,short *pLength);

	///��ȡһ���ֶε�ֵ
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	pLength	���صĳ���
	///@return	�õ����ֶ�ֵ��������pLengthָ����ͬʱ��\0��β������Ҳ����ֶΣ��򷵻�NULL
	char *getField(int fieldno,int recno,short *pLength);

	///��ȡһ���ֶε�ֵ
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@return	�õ����ֶ�ֵ��ͬʱ��\0��β������Ҳ����ֶΣ��򷵻�NULL
	char *getField(int fieldno,int recno);

	///��ȡһ���ֶε�����
	///@param	recno	��¼��
	///@return	�õ����ֶ�������������Ҳ����ֶ������򷵻�NULL
	char *getFieldName(int recno);

	///��ȡһ���ֶε�lenth1
	///@param	recno	��¼��
	///@return	�õ����ֶ�length1������Ҳ����ֶ������򷵻�-1
	unsigned char getFieldLength1(int recno);

	///��ȡһ���ֶε�lenth2
	///@param	recno	��¼��
	///@return	�õ����ֶ�length2������Ҳ����ֶ������򷵻�-1
	unsigned char getFieldLength2(int recno);

	///��ȡһ���ֶε�lenth
	///@param	recno	��¼��
	///@return	�õ����ֶ�length������Ҳ����ֶ������򷵻�-1
	short getFieldLength(int recno);
	///��ȡ�ֶεĶ���
	///@param	fieldName	�ֶ���
	///@return	�õ����ֶζ��壬NULL��ʾû���ҵ����ֶ�
	CFieldDefine *getFieldDefine(char *fieldName);
	
	///��ȡ�ֶζ���
	///@param	pFieldCount	���ڴ洢���ص��ֶθ���
	///@return	�ֶεĶ������飬������pFieldCount�з���
	CFieldDefine *getFieldDefines(short *pFieldCount);
	
	///��ȡ��¼����
	///@return	��¼����
	int getRecCount(void);
	
	///��ȡ����޸����
	///@return	����޸����
	int getYear(void);
	
	///��ȡ����޸��·�
	///@return	����޸��·�
	char getMonth(void);
	
	///��ȡ����޸�����
	///@return	����޸���
	char getDay(void);

	///��ȡ����޸�����
	///@return	����޸�����	
	int getDate();

	///��ȡ��¼���
	///@return	��¼���
	int getRecWidth(void);
	
	///��ȡ��¼����
	///@return	��¼����
	int getReccount(void);
	
	///��ȡ�ֶθ���
	///@return	�ֶθ���
	int getFieldCount(void);


	///����һ���ֶε�ֵ
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ����Ҫ����\0��β
	///@param	length	Ҫ���õ�ֵ�ĳ���,0��ʾʹ���ֶζ����е�ȱʡ����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setField(char *fieldName,int recno,char *value,short length);

	///�����ַ��ֶ�
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ��Ҫ����\0��β
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setCharacterField(char *fieldName,int recno,char *value);
	
	///���������ֶ�
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setIntField(char *fieldName,int recno,int value);
	
	
	///���ø������ֶ�
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setDoubleField(char *fieldName,int recno,double value);
	
	///���������ֶ�
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setDateField(char *fieldName,int recno,char *value);
	
	///���������ֶ�
	///@param	fieldName	�ֶ���
	///@param	recno	��¼��
	///@param	value	Ҫ���õ�ֵ��Ҫ����\0��β
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int setAnyField(char *fieldName,int recno,char *value);

	///ɾ��һ����¼��������ɾ��
	///@param	recno	��¼��
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int deleteRecord(int recno);

	///�ж�һ����¼�Ƿ�ɾ����
	///@param	recno	��¼��
	///@return	1��ʾ�Ѿ�ɾ����0��ʾû��ɾ����-1��ʾʧ��
	int isDeletedRecord(int recno);

	///�ָ��Ѿ�ɾ���ļ�¼
	///@param	recno	��¼��
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int recallRecord(int recno);

	///Ѱ��ĳһ���ֶε���ָ��ֵ�ļ�¼
	///@param	fieldName	�ֶ���
	///@param	startRecno	��ʼѰ�ҵļ�¼��
	///@param	value	Ҫ�����ֵ������Ҫ��\0��β
	///@param	length	ֵ��Ҫ�Ƚϵĳ��ȣ��������ȵĲ��֣����Բ����
	///@return	�ҵ��ļ�¼�ţ�0��ʾû���ҵ�
	int locateField(char *fieldName,int startRecno,char *value,short length);

	///Ѱ�ҵ�һ���ֶδ��ڵ���ָ��ֵ�ļ�¼��Ҫ��ԭDBF�ļ��Ѿ����ո��ֶ����򣬽�ʹ�ö��ֲ��ҷ�
	///@param	fieldName	�ֶ���
	///@param	startRecno	��ʼѰ�ҵļ�¼�ţ�0��ʾ��ͷ��ʼѰ��
	///@param	endRecno	����Ѱ�ҵļ�¼�ţ�0��ʾһֱ�ҵ���
	///@param	value	Ҫ�����ֵ������Ҫ��\0��β
	///@param	length	ֵ��Ҫ�Ƚϵĳ���
	///@return	�ҵ��ļ�¼�ţ�0��ʾû���ҵ�
	int seekField(char *fieldName,int startRecno,int endRecno,char *value,short length);

	///��DBF�ļ��Ľ���λ�ã�����һ���հ׵��¼�¼
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int appendRecord(void);
	
	///��ȡfrom��records�ļ�¼��buf��
	///@param	from	��¼��ʼ��
	///@param	records	��¼������
	///@param	buf	�洢������
	///@return	1��ʾ�ɹ���0��ʾʧ��
	int readRecords(DWORD from,int records,void *buf);

	///ȥ���ַ���β�Ŀո�
	///@param	pstring	�ֶ���
	///@return	�õ���ͷβ�ո� �ֶ�ֵ
	char* rTrim(char * pstring);
	
	///ȥ���ַ���ͷ���Ŀո�
	///@param	pstring	�ֶ���
	///@return	�õ���ͷβ�ո� �ֶ�ֵ
	char* lTrim(char * pstring);

	///������еļ�¼
    ///@return ���ͷ���Ժ����еļ�¼���
	void printAll(void);
	
private:
	int recCount;
	char year;
	char month;
	char day;
	int recWidth;
	short fieldCount;
	CFieldDefine *fieldDefines;

	bool opened;
	char id;
	int handle;
	//ÿ����¼������ڴ�
	char *recBuffer;
	short startPos;

	int memoHandle;
	int memoBlockLength;
	char *memoBuffer;
};

#endif
