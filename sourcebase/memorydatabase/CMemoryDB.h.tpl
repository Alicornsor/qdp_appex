!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file CMemoryDB.h
///@brief��������CMemoryDB
///@history 
///20121227	hwp	�������ļ�
/////////////////////////////////////////////////////////////////////////

#ifndef CMEMORYDB_H
#define CMEMORYDB_H

#include "CBaseObject.h"
#include "CConfig.h"
#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseIterators.h"

struct TableStruct
{
	char tableName[100];
	int  reuseID;
};

/*** SIR XXXXX BEGIN ***/
typedef struct MemTableItemInfoTag
{
	int InvestorAccountDepositCurrentMaxItem;
}MemTableItemInfoT, *pMemTableItemInfoT;
/*** SIR XXXXX END ***/

/////////////////////////////////////////////////////////////////////////
///CMemoryDB��һ���ڴ����ݿ��࣬���������ж���ı���Ϣ
///@author	xuzh
///@version	1.0,20050824
/////////////////////////////////////////////////////////////////////////
class CMemoryDB : public CBaseObject
{
public:
	///���췽���������ڴ����ݿ�
	CMemoryDB(void);
	
	///�����������������ͷ���ռ�õĿռ�
	virtual ~CMemoryDB(void);
	
	virtual int isA(char *objectType);
	virtual char *getType(void);
	virtual void output(CLogger *pLogger,int indent=0);

	///���г�ʼ������
	///@param	pConfig	��ʼ��ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int init(CConfig *pConfig,IMemoryAllocator *pAllocator=NULL,bool reuse=false);
	
	///�����������빤��
	///@param	pConfig	��������ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int load(CConfig *pConfig);

	///�������ݴ洢����
	///@param	pConfig	��������ʱʹ�õ�������Ϣ
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual int save(CConfig *pConfig);
	
	///������е�����
	///@return	1��ʾ�ɹ���0��ʾʧ��
	virtual void clear(void);
	
	///����������������
	virtual void linkAll(void);
	
	
	
	!!travel tables!!
	!!if !strcmp(@hasTable,"yes")!!
	///!!@usage!!��
	C!!@name!!Factory *m_!!@name!!Factory;
	
	!!endif!!
	!!next!!

/*** SIR XXXXX BEGIN ***/
	MemTableItemInfoT m_memTableItemInfo;
/*** SIR XXXXX END ***/

private:
	CFixMem *pMem;		///������ű����Ϣ
};

#endif
!!leave!!