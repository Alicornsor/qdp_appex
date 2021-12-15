/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file databaseFactories.pp
///@brief实现了若干个内存数据库的对象工厂
///@history 
///20121227	hwp		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "BaseDataStruct.h"
#include "databaseFactories.h"
#include "databaseResources.h"
#include "monitorIndex.h"

//#define COUNT_OPERATION

///强制进行复制，不理会const标记
///@param	target	复制的目标地址
///@param	source	复制的源地址
///@param	size	复制的空间大小
static void forceCopy(const void *target, const void *source, int size)
{
	if ((source==NULL)||(target==NULL))
	{
		REPORT_EVENT(LOG_CRITICAL,"InternalError","copy from or to null");
		return;
	}
	memcpy((void *)target,source,size);
}

extern int compareForTradingdayIndexinDataSyncStatus(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForDataSyncStatus=0;
int updateWithIndexActionForDataSyncStatus=0;
int updateWithoutIndexActionForDataSyncStatus=0;
int removeActionForDataSyncStatus=0;
int addCommitForDataSyncStatus=0;
int updateCommitForDataSyncStatus=0;
int removeCommitForDataSyncStatus=0;
#endif
void CDataSyncStatusFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pTradingdayIndex=new CAVLTree(maxUnit,compareForTradingdayIndexinDataSyncStatus,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("DataSyncStatus_TradingdayIndex",pTradingdayIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("DataSyncStatus_TradingdayIndex");
			if(it != pIndexMap->end()) {
				pTradingdayIndex=new CAVLTree(maxUnit,compareForTradingdayIndexinDataSyncStatus,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pTradingdayIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CDataSyncStatusActionTrigger *>;
	pCommitTriggers=new vector<CDataSyncStatusCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CDataSyncStatusFactory::CDataSyncStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CDataSyncStatus),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CDataSyncStatusFactory::CDataSyncStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CDataSyncStatus),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CDataSyncStatusFactory::~CDataSyncStatusFactory(void)
{
	if (runLevel>=0) {
		if (pTradingdayIndex!=NULL)
			delete pTradingdayIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CDataSyncStatusFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CDataSyncStatusFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pTradingdayIndex->output(pLogger,indent+1);
	}
}

int CDataSyncStatusFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableDataSyncStatus thisDataSyncStatus;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisDataSyncStatus.readCSV(input,pNames))
		add(&thisDataSyncStatus);
	fclose(input);
	delete pNames;
	return 1;
}

int CDataSyncStatusFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "DataSyncStatus.csv");
	return readCSV(szFileName);
}

int CDataSyncStatusFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableDataSyncStatus *pDataSyncStatus;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableDataSyncStatus::writeCSVHead(output);
	pDataSyncStatus=(CWriteableDataSyncStatus *)(pMem->getFirst());
	while (pDataSyncStatus!=NULL) {
		if (!pDataSyncStatus->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pDataSyncStatus=(CWriteableDataSyncStatus *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CDataSyncStatusFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "DataSyncStatus.csv");
	return writeCSV(szFileName);
}

void CDataSyncStatusFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CDataSyncStatusFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableDataSyncStatus *pDataSyncStatus;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CDataSyncStatusFactory={       Total Count=%d\n", pMem->getCount());
	pDataSyncStatus=(CWriteableDataSyncStatus *)(pMem->getFirst());
	while (pDataSyncStatus!=NULL) {
		pDataSyncStatus->dump(fp,index++);
		pDataSyncStatus=(CWriteableDataSyncStatus *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CDataSyncStatusFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pTradingdayIndex->removeAll();
	}
}

CDataSyncStatus *CDataSyncStatusFactory::internalAdd(CWriteableDataSyncStatus *pDataSyncStatus, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForDataSyncStatus++;
#endif
	CDataSyncStatus *pTarget;	
	beforeAdd(pDataSyncStatus);
	pTarget=(CDataSyncStatus *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough DataSyncStatus in memory database");
		return NULL;
	}
	forceCopy(pTarget, pDataSyncStatus, sizeof(CDataSyncStatus));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pTradingdayIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CDataSyncStatus *CDataSyncStatusFactory::add(CWriteableDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction)
{
	pDataSyncStatus->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pDataSyncStatus,true);
	}
	else {
		CDataSyncStatus *pNewDataSyncStatus;
		pNewDataSyncStatus = internalAdd(pDataSyncStatus,false);
		pTransaction->addResource(CDataSyncStatusResource::alloc(CREATE_ACTION,this,pNewDataSyncStatus,NULL));
		return pNewDataSyncStatus;
	}
}

void CDataSyncStatusFactory::internalUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForDataSyncStatus++;
	}
	else {
		updateWithoutIndexActionForDataSyncStatus++;
	}
#endif
	CWriteableDataSyncStatus theOldDataSyncStatus;
	beforeUpdate(pDataSyncStatus,pNewDataSyncStatus);
	if (bNoTransaction) {
		forceCopy(&theOldDataSyncStatus,pDataSyncStatus,sizeof(CDataSyncStatus));
	}
	if (updateIndex) {
	}

	forceCopy(pDataSyncStatus,pNewDataSyncStatus,sizeof(CDataSyncStatus));
	pMem->updateObject(pDataSyncStatus);
	if (updateIndex) {
	}
	afterUpdate(pDataSyncStatus);
	if (bNoTransaction) {
		commitUpdate(pDataSyncStatus,&theOldDataSyncStatus);
	}
}

void CDataSyncStatusFactory::update(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction, bool updateIndex)
{
	pNewDataSyncStatus->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pDataSyncStatus,pNewDataSyncStatus,updateIndex,true);
	}
	else {
		pTransaction->addResource(CDataSyncStatusResource::alloc(UPDATE_ACTION,this,pDataSyncStatus,pNewDataSyncStatus,updateIndex));
		internalUpdate(pDataSyncStatus,pNewDataSyncStatus,updateIndex,false);
	}
}

void CDataSyncStatusFactory::internalRemove(CDataSyncStatus *pDataSyncStatus, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForDataSyncStatus++;
#endif
	CWriteableDataSyncStatus theOldDataSyncStatus;
	beforeRemove(pDataSyncStatus);
	if (bNoTransaction) {
		forceCopy(&theOldDataSyncStatus,pDataSyncStatus,sizeof(CDataSyncStatus));
	}
	if (runLevel>=0) {
		pTradingdayIndex->removeObject(pDataSyncStatus);
	}
	pMem->free(pDataSyncStatus);
	if(bNoTransaction) {
		commitRemove(&theOldDataSyncStatus);
	}
}

void CDataSyncStatusFactory::remove(CDataSyncStatus *pDataSyncStatus, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pDataSyncStatus,true);
	}
	else {
		pTransaction->addResource(CDataSyncStatusResource::alloc(DELETE_ACTION,this,pDataSyncStatus,NULL));
		internalRemove(pDataSyncStatus,false);		
	}
}

CDataSyncStatus* CDataSyncStatusFactory::addOrUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus, CTransaction *pTransaction, bool updateIndex)
{
	if(pDataSyncStatus == NULL) {
		return add(pNewDataSyncStatus,pTransaction);
	}
	else {
		update(pDataSyncStatus,pNewDataSyncStatus,pTransaction,updateIndex);
		return pDataSyncStatus;
	}
}

void CDataSyncStatusFactory::retrieve(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pTargetDataSyncStatus)
{
	forceCopy(pTargetDataSyncStatus, pDataSyncStatus, sizeof(CDataSyncStatus));
}
	
int CDataSyncStatusFactory::addActionTrigger(CDataSyncStatusActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CDataSyncStatusFactory::removeActionTrigger(CDataSyncStatusActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CDataSyncStatusFactory::addCommitTrigger(CDataSyncStatusCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CDataSyncStatusFactory::removeCommitTrigger(CDataSyncStatusCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CDataSyncStatus *CDataSyncStatusFactory::getFirst(void)
{
	CDataSyncStatus *pResult=(CDataSyncStatus *)(pMem->getFirst());
	return pResult;
}
	
CDataSyncStatus *CDataSyncStatusFactory::getNext(void)
{
	CDataSyncStatus *pResult=(CDataSyncStatus *)(pMem->getNext());
	return pResult;
}
	
void CDataSyncStatusFactory::endGet(void)
{
	pMem->endGet();
}

void CDataSyncStatusFactory::beforeAdd(CWriteableDataSyncStatus *pDataSyncStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pDataSyncStatus);
	}
}
	
void CDataSyncStatusFactory::afterAdd(CDataSyncStatus *pDataSyncStatus)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pDataSyncStatus);
	}
}

void CDataSyncStatusFactory::beforeUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pNewDataSyncStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pDataSyncStatus,pNewDataSyncStatus);
	}
}
	
void CDataSyncStatusFactory::afterUpdate(CDataSyncStatus *pDataSyncStatus)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pDataSyncStatus);
	}
}
	
void CDataSyncStatusFactory::beforeRemove(CDataSyncStatus *pDataSyncStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pDataSyncStatus);
	}
}

void CDataSyncStatusFactory::commitAdd(CDataSyncStatus *pDataSyncStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForDataSyncStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pDataSyncStatus);
	}
}

void CDataSyncStatusFactory::commitUpdate(CDataSyncStatus *pDataSyncStatus, CWriteableDataSyncStatus *pOldDataSyncStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForDataSyncStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pDataSyncStatus,pOldDataSyncStatus);
	}
}
	
void CDataSyncStatusFactory::commitRemove(CWriteableDataSyncStatus *pDataSyncStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForDataSyncStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pDataSyncStatus);
	}
}

void CDataSyncStatusFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForTradingDayinSystemStatus(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForSystemStatus=0;
int updateWithIndexActionForSystemStatus=0;
int updateWithoutIndexActionForSystemStatus=0;
int removeActionForSystemStatus=0;
int addCommitForSystemStatus=0;
int updateCommitForSystemStatus=0;
int removeCommitForSystemStatus=0;
#endif
void CSystemStatusFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pTradingDay=new CAVLTree(maxUnit,compareForTradingDayinSystemStatus,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("SystemStatus_TradingDay",pTradingDay->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("SystemStatus_TradingDay");
			if(it != pIndexMap->end()) {
				pTradingDay=new CAVLTree(maxUnit,compareForTradingDayinSystemStatus,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pTradingDay==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CSystemStatusActionTrigger *>;
	pCommitTriggers=new vector<CSystemStatusCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CSystemStatusFactory::CSystemStatusFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSystemStatus),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CSystemStatusFactory::CSystemStatusFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSystemStatus),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CSystemStatusFactory::~CSystemStatusFactory(void)
{
	if (runLevel>=0) {
		if (pTradingDay!=NULL)
			delete pTradingDay;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CSystemStatusFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSystemStatusFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pTradingDay->output(pLogger,indent+1);
	}
}

int CSystemStatusFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableSystemStatus thisSystemStatus;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisSystemStatus.readCSV(input,pNames))
		add(&thisSystemStatus);
	fclose(input);
	delete pNames;
	return 1;
}

int CSystemStatusFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "SystemStatus.csv");
	return readCSV(szFileName);
}

int CSystemStatusFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableSystemStatus *pSystemStatus;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableSystemStatus::writeCSVHead(output);
	pSystemStatus=(CWriteableSystemStatus *)(pMem->getFirst());
	while (pSystemStatus!=NULL) {
		if (!pSystemStatus->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pSystemStatus=(CWriteableSystemStatus *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CSystemStatusFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SystemStatus.csv");
	return writeCSV(szFileName);
}

void CSystemStatusFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CSystemStatusFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableSystemStatus *pSystemStatus;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CSystemStatusFactory={       Total Count=%d\n", pMem->getCount());
	pSystemStatus=(CWriteableSystemStatus *)(pMem->getFirst());
	while (pSystemStatus!=NULL) {
		pSystemStatus->dump(fp,index++);
		pSystemStatus=(CWriteableSystemStatus *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CSystemStatusFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pTradingDay->removeAll();
	}
}

CSystemStatus *CSystemStatusFactory::internalAdd(CWriteableSystemStatus *pSystemStatus, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForSystemStatus++;
#endif
	CSystemStatus *pTarget;	
	beforeAdd(pSystemStatus);
	pTarget=(CSystemStatus *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough SystemStatus in memory database");
		return NULL;
	}
	forceCopy(pTarget, pSystemStatus, sizeof(CSystemStatus));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pTradingDay->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CSystemStatus *CSystemStatusFactory::add(CWriteableSystemStatus *pSystemStatus, CTransaction *pTransaction)
{
	pSystemStatus->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pSystemStatus,true);
	}
	else {
		CSystemStatus *pNewSystemStatus;
		pNewSystemStatus = internalAdd(pSystemStatus,false);
		pTransaction->addResource(CSystemStatusResource::alloc(CREATE_ACTION,this,pNewSystemStatus,NULL));
		return pNewSystemStatus;
	}
}

void CSystemStatusFactory::internalUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForSystemStatus++;
	}
	else {
		updateWithoutIndexActionForSystemStatus++;
	}
#endif
	CWriteableSystemStatus theOldSystemStatus;
	beforeUpdate(pSystemStatus,pNewSystemStatus);
	if (bNoTransaction) {
		forceCopy(&theOldSystemStatus,pSystemStatus,sizeof(CSystemStatus));
	}
	if (updateIndex) {
	}

	forceCopy(pSystemStatus,pNewSystemStatus,sizeof(CSystemStatus));
	pMem->updateObject(pSystemStatus);
	if (updateIndex) {
	}
	afterUpdate(pSystemStatus);
	if (bNoTransaction) {
		commitUpdate(pSystemStatus,&theOldSystemStatus);
	}
}

void CSystemStatusFactory::update(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction, bool updateIndex)
{
	pNewSystemStatus->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pSystemStatus,pNewSystemStatus,updateIndex,true);
	}
	else {
		pTransaction->addResource(CSystemStatusResource::alloc(UPDATE_ACTION,this,pSystemStatus,pNewSystemStatus,updateIndex));
		internalUpdate(pSystemStatus,pNewSystemStatus,updateIndex,false);
	}
}

void CSystemStatusFactory::internalRemove(CSystemStatus *pSystemStatus, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForSystemStatus++;
#endif
	CWriteableSystemStatus theOldSystemStatus;
	beforeRemove(pSystemStatus);
	if (bNoTransaction) {
		forceCopy(&theOldSystemStatus,pSystemStatus,sizeof(CSystemStatus));
	}
	if (runLevel>=0) {
		pTradingDay->removeObject(pSystemStatus);
	}
	pMem->free(pSystemStatus);
	if(bNoTransaction) {
		commitRemove(&theOldSystemStatus);
	}
}

void CSystemStatusFactory::remove(CSystemStatus *pSystemStatus, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pSystemStatus,true);
	}
	else {
		pTransaction->addResource(CSystemStatusResource::alloc(DELETE_ACTION,this,pSystemStatus,NULL));
		internalRemove(pSystemStatus,false);		
	}
}

CSystemStatus* CSystemStatusFactory::addOrUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus, CTransaction *pTransaction, bool updateIndex)
{
	if(pSystemStatus == NULL) {
		return add(pNewSystemStatus,pTransaction);
	}
	else {
		update(pSystemStatus,pNewSystemStatus,pTransaction,updateIndex);
		return pSystemStatus;
	}
}

void CSystemStatusFactory::retrieve(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pTargetSystemStatus)
{
	forceCopy(pTargetSystemStatus, pSystemStatus, sizeof(CSystemStatus));
}
	
int CSystemStatusFactory::addActionTrigger(CSystemStatusActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CSystemStatusFactory::removeActionTrigger(CSystemStatusActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CSystemStatusFactory::addCommitTrigger(CSystemStatusCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CSystemStatusFactory::removeCommitTrigger(CSystemStatusCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CSystemStatus *CSystemStatusFactory::getFirst(void)
{
	CSystemStatus *pResult=(CSystemStatus *)(pMem->getFirst());
	return pResult;
}
	
CSystemStatus *CSystemStatusFactory::getNext(void)
{
	CSystemStatus *pResult=(CSystemStatus *)(pMem->getNext());
	return pResult;
}
	
void CSystemStatusFactory::endGet(void)
{
	pMem->endGet();
}

void CSystemStatusFactory::beforeAdd(CWriteableSystemStatus *pSystemStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pSystemStatus);
	}
}
	
void CSystemStatusFactory::afterAdd(CSystemStatus *pSystemStatus)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pSystemStatus);
	}
}

void CSystemStatusFactory::beforeUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pNewSystemStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pSystemStatus,pNewSystemStatus);
	}
}
	
void CSystemStatusFactory::afterUpdate(CSystemStatus *pSystemStatus)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pSystemStatus);
	}
}
	
void CSystemStatusFactory::beforeRemove(CSystemStatus *pSystemStatus)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pSystemStatus);
	}
}

void CSystemStatusFactory::commitAdd(CSystemStatus *pSystemStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForSystemStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pSystemStatus);
	}
}

void CSystemStatusFactory::commitUpdate(CSystemStatus *pSystemStatus, CWriteableSystemStatus *pOldSystemStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForSystemStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pSystemStatus,pOldSystemStatus);
	}
}
	
void CSystemStatusFactory::commitRemove(CWriteableSystemStatus *pSystemStatus)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForSystemStatus++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pSystemStatus);
	}
}

void CSystemStatusFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForOrderAction=0;
int updateWithIndexActionForOrderAction=0;
int updateWithoutIndexActionForOrderAction=0;
int removeActionForOrderAction=0;
int addCommitForOrderAction=0;
int updateCommitForOrderAction=0;
int removeCommitForOrderAction=0;
#endif
void COrderActionFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	pActionTriggers=new vector<COrderActionActionTrigger *>;
	pCommitTriggers=new vector<COrderActionCommitTrigger *>;
	m_activeCommitTrigger=true;
}

COrderActionFactory::COrderActionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderAction),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

COrderActionFactory::COrderActionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderAction),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

COrderActionFactory::~COrderActionFactory(void)
{
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void COrderActionFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderActionFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int COrderActionFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableOrderAction thisOrderAction;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisOrderAction.readCSV(input,pNames))
		add(&thisOrderAction);
	fclose(input);
	delete pNames;
	return 1;
}

int COrderActionFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "OrderAction.csv");
	return readCSV(szFileName);
}

int COrderActionFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableOrderAction *pOrderAction;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableOrderAction::writeCSVHead(output);
	pOrderAction=(CWriteableOrderAction *)(pMem->getFirst());
	while (pOrderAction!=NULL) {
		if (!pOrderAction->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pOrderAction=(CWriteableOrderAction *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int COrderActionFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderAction.csv");
	return writeCSV(szFileName);
}

void COrderActionFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void COrderActionFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableOrderAction *pOrderAction;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"COrderActionFactory={       Total Count=%d\n", pMem->getCount());
	pOrderAction=(CWriteableOrderAction *)(pMem->getFirst());
	while (pOrderAction!=NULL) {
		pOrderAction->dump(fp,index++);
		pOrderAction=(CWriteableOrderAction *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void COrderActionFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
}

COrderAction *COrderActionFactory::internalAdd(CWriteableOrderAction *pOrderAction, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForOrderAction++;
#endif
	COrderAction *pTarget;	
	beforeAdd(pOrderAction);
	pTarget=(COrderAction *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough OrderAction in memory database");
		return NULL;
	}
	forceCopy(pTarget, pOrderAction, sizeof(COrderAction));
	pMem->updateObject(pTarget);
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

COrderAction *COrderActionFactory::add(CWriteableOrderAction *pOrderAction, CTransaction *pTransaction)
{
	pOrderAction->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pOrderAction,true);
	}
	else {
		COrderAction *pNewOrderAction;
		pNewOrderAction = internalAdd(pOrderAction,false);
		pTransaction->addResource(COrderActionResource::alloc(CREATE_ACTION,this,pNewOrderAction,NULL));
		return pNewOrderAction;
	}
}

void COrderActionFactory::internalUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForOrderAction++;
	}
	else {
		updateWithoutIndexActionForOrderAction++;
	}
#endif
	CWriteableOrderAction theOldOrderAction;
	beforeUpdate(pOrderAction,pNewOrderAction);
	if (bNoTransaction) {
		forceCopy(&theOldOrderAction,pOrderAction,sizeof(COrderAction));
	}
	if (updateIndex) {
	}

	forceCopy(pOrderAction,pNewOrderAction,sizeof(COrderAction));
	pMem->updateObject(pOrderAction);
	if (updateIndex) {
	}
	afterUpdate(pOrderAction);
	if (bNoTransaction) {
		commitUpdate(pOrderAction,&theOldOrderAction);
	}
}

void COrderActionFactory::update(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction, bool updateIndex)
{
	pNewOrderAction->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pOrderAction,pNewOrderAction,updateIndex,true);
	}
	else {
		pTransaction->addResource(COrderActionResource::alloc(UPDATE_ACTION,this,pOrderAction,pNewOrderAction,updateIndex));
		internalUpdate(pOrderAction,pNewOrderAction,updateIndex,false);
	}
}

void COrderActionFactory::internalRemove(COrderAction *pOrderAction, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForOrderAction++;
#endif
	CWriteableOrderAction theOldOrderAction;
	beforeRemove(pOrderAction);
	if (bNoTransaction) {
		forceCopy(&theOldOrderAction,pOrderAction,sizeof(COrderAction));
	}
	pMem->free(pOrderAction);
	if(bNoTransaction) {
		commitRemove(&theOldOrderAction);
	}
}

void COrderActionFactory::remove(COrderAction *pOrderAction, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pOrderAction,true);
	}
	else {
		pTransaction->addResource(COrderActionResource::alloc(DELETE_ACTION,this,pOrderAction,NULL));
		internalRemove(pOrderAction,false);		
	}
}

COrderAction* COrderActionFactory::addOrUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction, CTransaction *pTransaction, bool updateIndex)
{
	if(pOrderAction == NULL) {
		return add(pNewOrderAction,pTransaction);
	}
	else {
		update(pOrderAction,pNewOrderAction,pTransaction,updateIndex);
		return pOrderAction;
	}
}

void COrderActionFactory::retrieve(COrderAction *pOrderAction, CWriteableOrderAction *pTargetOrderAction)
{
	forceCopy(pTargetOrderAction, pOrderAction, sizeof(COrderAction));
}
	
int COrderActionFactory::addActionTrigger(COrderActionActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int COrderActionFactory::removeActionTrigger(COrderActionActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int COrderActionFactory::addCommitTrigger(COrderActionCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int COrderActionFactory::removeCommitTrigger(COrderActionCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

COrderAction *COrderActionFactory::getFirst(void)
{
	COrderAction *pResult=(COrderAction *)(pMem->getFirst());
	return pResult;
}
	
COrderAction *COrderActionFactory::getNext(void)
{
	COrderAction *pResult=(COrderAction *)(pMem->getNext());
	return pResult;
}
	
void COrderActionFactory::endGet(void)
{
	pMem->endGet();
}

void COrderActionFactory::beforeAdd(CWriteableOrderAction *pOrderAction)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pOrderAction);
	}
}
	
void COrderActionFactory::afterAdd(COrderAction *pOrderAction)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pOrderAction);
	}
}

void COrderActionFactory::beforeUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pNewOrderAction)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pOrderAction,pNewOrderAction);
	}
}
	
void COrderActionFactory::afterUpdate(COrderAction *pOrderAction)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pOrderAction);
	}
}
	
void COrderActionFactory::beforeRemove(COrderAction *pOrderAction)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pOrderAction);
	}
}

void COrderActionFactory::commitAdd(COrderAction *pOrderAction)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForOrderAction++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pOrderAction);
	}
}

void COrderActionFactory::commitUpdate(COrderAction *pOrderAction, CWriteableOrderAction *pOldOrderAction)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForOrderAction++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pOrderAction,pOldOrderAction);
	}
}
	
void COrderActionFactory::commitRemove(CWriteableOrderAction *pOrderAction)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForOrderAction++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pOrderAction);
	}
}

void COrderActionFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void COrderActionFactory::linkAllOrder(COrderFactory *pFactory)
{
	COrderAction *pOrderAction;
	pOrderAction=getFirst();
	while (pOrderAction != NULL) {
		pOrderAction->linkOrder(pFactory);
		pOrderAction=getNext();
	}
	endGet();
}

void COrderActionFactory::linkAllPreOrder(CPreOrderFactory *pFactory)
{
	COrderAction *pOrderAction;
	pOrderAction=getFirst();
	while (pOrderAction != NULL) {
		pOrderAction->linkPreOrder(pFactory);
		pOrderAction=getNext();
	}
	endGet();
}

#ifdef COUNT_OPERATION
int addActionForOrder=0;
int updateWithIndexActionForOrder=0;
int updateWithoutIndexActionForOrder=0;
int removeActionForOrder=0;
int addCommitForOrder=0;
int updateCommitForOrder=0;
int removeCommitForOrder=0;
#endif
void COrderFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=1572869;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("Order.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pExchangeIDOrderSysIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Order_ExchangeIDOrderSysIDHashIndex",pExchangeIDOrderSysIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Order_ExchangeIDOrderSysIDHashIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDOrderSysIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDOrderSysIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		int hashKeySize=1572869;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("Order.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pUserIDAndUserOrderLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Order_UserIDAndUserOrderLocalIDHashIndex",pUserIDAndUserOrderLocalIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Order_UserIDAndUserOrderLocalIDHashIndex");
			if(it != pIndexMap->end()) {
				pUserIDAndUserOrderLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pUserIDAndUserOrderLocalIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByUserID=NULL;
	pLastFoundInSearchAllByInvestorID=NULL;
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<COrderActionTrigger *>;
	pCommitTriggers=new vector<COrderCommitTrigger *>;
	m_activeCommitTrigger=true;
}

COrderFactory::COrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrder),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

COrderFactory::COrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrder),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

COrderFactory::~COrderFactory(void)
{
	if (runLevel>=0) {
		if (pExchangeIDOrderSysIDHashIndex!=NULL)
			delete pExchangeIDOrderSysIDHashIndex;
	}
	if (runLevel>=0) {
		if (pUserIDAndUserOrderLocalIDHashIndex!=NULL)
			delete pUserIDAndUserOrderLocalIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void COrderFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int COrderFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableOrder thisOrder;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisOrder.readCSV(input,pNames))
		add(&thisOrder);
	fclose(input);
	delete pNames;
	return 1;
}

int COrderFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Order.csv");
	return readCSV(szFileName);
}

int COrderFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableOrder *pOrder;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableOrder::writeCSVHead(output);
	pOrder=(CWriteableOrder *)(pMem->getFirst());
	while (pOrder!=NULL) {
		if (!pOrder->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pOrder=(CWriteableOrder *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int COrderFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Order.csv");
	return writeCSV(szFileName);
}

void COrderFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void COrderFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableOrder *pOrder;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"COrderFactory={       Total Count=%d\n", pMem->getCount());
	pOrder=(CWriteableOrder *)(pMem->getFirst());
	while (pOrder!=NULL) {
		pOrder->dump(fp,index++);
		pOrder=(CWriteableOrder *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void COrderFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pExchangeIDOrderSysIDHashIndex->removeAll();
	}
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->removeAll();
	}
}

COrder *COrderFactory::internalAdd(CWriteableOrder *pOrder, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForOrder++;
#endif
	COrder *pTarget;	
	beforeAdd(pOrder);
	pTarget=(COrder *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Order in memory database");
		return NULL;
	}
	forceCopy(pTarget, pOrder, sizeof(COrder));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pExchangeIDOrderSysIDHashIndex->addObject(pTarget,pTarget->HashExchangeIDOrderSysID);
	}
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->addObject(pTarget,pTarget->HashUserIDAndUserOrderLocalID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

COrder *COrderFactory::add(CWriteableOrder *pOrder, CTransaction *pTransaction)
{
	pOrder->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pOrder,true);
	}
	else {
		COrder *pNewOrder;
		pNewOrder = internalAdd(pOrder,false);
		pTransaction->addResource(COrderResource::alloc(CREATE_ACTION,this,pNewOrder,NULL));
		return pNewOrder;
	}
}

void COrderFactory::internalUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForOrder++;
	}
	else {
		updateWithoutIndexActionForOrder++;
	}
#endif
	CWriteableOrder theOldOrder;
	beforeUpdate(pOrder,pNewOrder);
	if (bNoTransaction) {
		forceCopy(&theOldOrder,pOrder,sizeof(COrder));
	}
	if (updateIndex) {
	}

	forceCopy(pOrder,pNewOrder,sizeof(COrder));
	pMem->updateObject(pOrder);
	if (updateIndex) {
	}
	afterUpdate(pOrder);
	if (bNoTransaction) {
		commitUpdate(pOrder,&theOldOrder);
	}
}

void COrderFactory::update(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction, bool updateIndex)
{
	pNewOrder->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pOrder,pNewOrder,updateIndex,true);
	}
	else {
		pTransaction->addResource(COrderResource::alloc(UPDATE_ACTION,this,pOrder,pNewOrder,updateIndex));
		internalUpdate(pOrder,pNewOrder,updateIndex,false);
	}
}

void COrderFactory::internalRemove(COrder *pOrder, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForOrder++;
#endif
	CWriteableOrder theOldOrder;
	beforeRemove(pOrder);
	if (bNoTransaction) {
		forceCopy(&theOldOrder,pOrder,sizeof(COrder));
	}
	if (runLevel>=0) {
		pExchangeIDOrderSysIDHashIndex->removeObject(pOrder,pOrder->HashExchangeIDOrderSysID);
	}	
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->removeObject(pOrder,pOrder->HashUserIDAndUserOrderLocalID);
	}	
	pMem->free(pOrder);
	if(bNoTransaction) {
		commitRemove(&theOldOrder);
	}
}

void COrderFactory::remove(COrder *pOrder, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pOrder,true);
	}
	else {
		pTransaction->addResource(COrderResource::alloc(DELETE_ACTION,this,pOrder,NULL));
		internalRemove(pOrder,false);		
	}
}

COrder* COrderFactory::addOrUpdate(COrder *pOrder, CWriteableOrder *pNewOrder, CTransaction *pTransaction, bool updateIndex)
{
	if(pOrder == NULL) {
		return add(pNewOrder,pTransaction);
	}
	else {
		update(pOrder,pNewOrder,pTransaction,updateIndex);
		return pOrder;
	}
}

void COrderFactory::retrieve(COrder *pOrder, CWriteableOrder *pTargetOrder)
{
	forceCopy(pTargetOrder, pOrder, sizeof(COrder));
}
	
int COrderFactory::addActionTrigger(COrderActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int COrderFactory::removeActionTrigger(COrderActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int COrderFactory::addCommitTrigger(COrderCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int COrderFactory::removeCommitTrigger(COrderCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

COrder *COrderFactory::getFirst(void)
{
	COrder *pResult=(COrder *)(pMem->getFirst());
	return pResult;
}
	
COrder *COrderFactory::getNext(void)
{
	COrder *pResult=(COrder *)(pMem->getNext());
	return pResult;
}
	
void COrderFactory::endGet(void)
{
	pMem->endGet();
}

void COrderFactory::beforeAdd(CWriteableOrder *pOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pOrder);
	}
}
	
void COrderFactory::afterAdd(COrder *pOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pOrder);
	}
}

void COrderFactory::beforeUpdate(COrder *pOrder, CWriteableOrder *pNewOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pOrder,pNewOrder);
	}
}
	
void COrderFactory::afterUpdate(COrder *pOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pOrder);
	}
}
	
void COrderFactory::beforeRemove(COrder *pOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pOrder);
	}
}

void COrderFactory::commitAdd(COrder *pOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pOrder);
	}
}

void COrderFactory::commitUpdate(COrder *pOrder, CWriteableOrder *pOldOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pOrder,pOldOrder);
	}
}
	
void COrderFactory::commitRemove(CWriteableOrder *pOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pOrder);
	}
}

void COrderFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void COrderFactory::linkAllInvestor(CInvestorFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestor(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllClientTradingID(CClientTradingIDFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkClientTradingID(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInvestorAccount(CInvestorAccountFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestorAccount(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInvestorPosition(CInvestorPositionFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestorPosition(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInstrument(CInstrumentFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInstrument(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInvestorMargin(CInvestorMarginFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestorMargin(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInvestorFee(CInvestorFeeFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestorFee(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkInvestorOptionFee(pFactory);
		pOrder=getNext();
	}
	endGet();
}

void COrderFactory::linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory)
{
	COrder *pOrder;
	pOrder=getFirst();
	while (pOrder != NULL) {
		pOrder->linkClientGroupPosition(pFactory);
		pOrder=getNext();
	}
	endGet();
}

extern int compareForExchangeIDTradeIDIndexinTrade(const void *pV1, const void *pV2);
extern int compareForExchangeIDTradeIDOrderSysIDIndexinTrade(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForTrade=0;
int updateWithIndexActionForTrade=0;
int updateWithoutIndexActionForTrade=0;
int removeActionForTrade=0;
int addCommitForTrade=0;
int updateCommitForTrade=0;
int removeCommitForTrade=0;
#endif
void CTradeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=1) {
		if(!reuse) {
			pExchangeIDTradeIDIndex=new CAVLTree(maxUnit,compareForExchangeIDTradeIDIndexinTrade,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Trade_ExchangeIDTradeIDIndex",pExchangeIDTradeIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Trade_ExchangeIDTradeIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDTradeIDIndex=new CAVLTree(maxUnit,compareForExchangeIDTradeIDIndexinTrade,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDTradeIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDTradeIDOrderSysIDIndex=new CAVLTree(maxUnit,compareForExchangeIDTradeIDOrderSysIDIndexinTrade,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Trade_ExchangeIDTradeIDOrderSysIDIndex",pExchangeIDTradeIDOrderSysIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Trade_ExchangeIDTradeIDOrderSysIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDTradeIDOrderSysIDIndex=new CAVLTree(maxUnit,compareForExchangeIDTradeIDOrderSysIDIndexinTrade,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDTradeIDOrderSysIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByExchangeIDAndTradeID=NULL;
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
	pLastFoundInSearchAllByInvestorID=NULL;
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CTradeActionTrigger *>;
	pCommitTriggers=new vector<CTradeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CTradeFactory::CTradeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CTrade),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CTradeFactory::CTradeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CTrade),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CTradeFactory::~CTradeFactory(void)
{
	if (runLevel>=1) {
		if (pExchangeIDTradeIDIndex!=NULL)
			delete pExchangeIDTradeIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDTradeIDOrderSysIDIndex!=NULL)
			delete pExchangeIDTradeIDOrderSysIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CTradeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CTradeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=1) {
		pExchangeIDTradeIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDTradeIDOrderSysIDIndex->output(pLogger,indent+1);
	}
}

int CTradeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableTrade thisTrade;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisTrade.readCSV(input,pNames))
		add(&thisTrade);
	fclose(input);
	delete pNames;
	return 1;
}

int CTradeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Trade.csv");
	return readCSV(szFileName);
}

int CTradeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableTrade *pTrade;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableTrade::writeCSVHead(output);
	pTrade=(CWriteableTrade *)(pMem->getFirst());
	while (pTrade!=NULL) {
		if (!pTrade->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pTrade=(CWriteableTrade *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CTradeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Trade.csv");
	return writeCSV(szFileName);
}

void CTradeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CTradeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableTrade *pTrade;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CTradeFactory={       Total Count=%d\n", pMem->getCount());
	pTrade=(CWriteableTrade *)(pMem->getFirst());
	while (pTrade!=NULL) {
		pTrade->dump(fp,index++);
		pTrade=(CWriteableTrade *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CTradeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=1) {
		pExchangeIDTradeIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDTradeIDOrderSysIDIndex->removeAll();
	}
}

CTrade *CTradeFactory::internalAdd(CWriteableTrade *pTrade, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForTrade++;
#endif
	CTrade *pTarget;	
	beforeAdd(pTrade);
	pTarget=(CTrade *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Trade in memory database");
		return NULL;
	}
	forceCopy(pTarget, pTrade, sizeof(CTrade));
	pMem->updateObject(pTarget);
	if (runLevel>=1) {
		pExchangeIDTradeIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDTradeIDOrderSysIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CTrade *CTradeFactory::add(CWriteableTrade *pTrade, CTransaction *pTransaction)
{
	pTrade->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pTrade,true);
	}
	else {
		CTrade *pNewTrade;
		pNewTrade = internalAdd(pTrade,false);
		pTransaction->addResource(CTradeResource::alloc(CREATE_ACTION,this,pNewTrade,NULL));
		return pNewTrade;
	}
}

void CTradeFactory::internalUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForTrade++;
	}
	else {
		updateWithoutIndexActionForTrade++;
	}
#endif
	CWriteableTrade theOldTrade;
	beforeUpdate(pTrade,pNewTrade);
	if (bNoTransaction) {
		forceCopy(&theOldTrade,pTrade,sizeof(CTrade));
	}
	if (updateIndex) {
	}

	forceCopy(pTrade,pNewTrade,sizeof(CTrade));
	pMem->updateObject(pTrade);
	if (updateIndex) {
	}
	afterUpdate(pTrade);
	if (bNoTransaction) {
		commitUpdate(pTrade,&theOldTrade);
	}
}

void CTradeFactory::update(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction, bool updateIndex)
{
	pNewTrade->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pTrade,pNewTrade,updateIndex,true);
	}
	else {
		pTransaction->addResource(CTradeResource::alloc(UPDATE_ACTION,this,pTrade,pNewTrade,updateIndex));
		internalUpdate(pTrade,pNewTrade,updateIndex,false);
	}
}

void CTradeFactory::internalRemove(CTrade *pTrade, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForTrade++;
#endif
	CWriteableTrade theOldTrade;
	beforeRemove(pTrade);
	if (bNoTransaction) {
		forceCopy(&theOldTrade,pTrade,sizeof(CTrade));
	}
	if (runLevel>=1) {
		pExchangeIDTradeIDIndex->removeObject(pTrade);
	}
	if (runLevel>=0) {
		pExchangeIDTradeIDOrderSysIDIndex->removeObject(pTrade);
	}
	pMem->free(pTrade);
	if(bNoTransaction) {
		commitRemove(&theOldTrade);
	}
}

void CTradeFactory::remove(CTrade *pTrade, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pTrade,true);
	}
	else {
		pTransaction->addResource(CTradeResource::alloc(DELETE_ACTION,this,pTrade,NULL));
		internalRemove(pTrade,false);		
	}
}

CTrade* CTradeFactory::addOrUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade, CTransaction *pTransaction, bool updateIndex)
{
	if(pTrade == NULL) {
		return add(pNewTrade,pTransaction);
	}
	else {
		update(pTrade,pNewTrade,pTransaction,updateIndex);
		return pTrade;
	}
}

void CTradeFactory::retrieve(CTrade *pTrade, CWriteableTrade *pTargetTrade)
{
	forceCopy(pTargetTrade, pTrade, sizeof(CTrade));
}
	
int CTradeFactory::addActionTrigger(CTradeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CTradeFactory::removeActionTrigger(CTradeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CTradeFactory::addCommitTrigger(CTradeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CTradeFactory::removeCommitTrigger(CTradeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CTrade *CTradeFactory::getFirst(void)
{
	CTrade *pResult=(CTrade *)(pMem->getFirst());
	return pResult;
}
	
CTrade *CTradeFactory::getNext(void)
{
	CTrade *pResult=(CTrade *)(pMem->getNext());
	return pResult;
}
	
void CTradeFactory::endGet(void)
{
	pMem->endGet();
}

void CTradeFactory::beforeAdd(CWriteableTrade *pTrade)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pTrade);
	}
}
	
void CTradeFactory::afterAdd(CTrade *pTrade)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pTrade);
	}
}

void CTradeFactory::beforeUpdate(CTrade *pTrade, CWriteableTrade *pNewTrade)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pTrade,pNewTrade);
	}
}
	
void CTradeFactory::afterUpdate(CTrade *pTrade)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pTrade);
	}
}
	
void CTradeFactory::beforeRemove(CTrade *pTrade)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pTrade);
	}
}

void CTradeFactory::commitAdd(CTrade *pTrade)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForTrade++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pTrade);
	}
}

void CTradeFactory::commitUpdate(CTrade *pTrade, CWriteableTrade *pOldTrade)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForTrade++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pTrade,pOldTrade);
	}
}
	
void CTradeFactory::commitRemove(CWriteableTrade *pTrade)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForTrade++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pTrade);
	}
}

void CTradeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForAPIIDAndOrderLocalIDIndexinPreOrder(const void *pV1, const void *pV2);
extern int compareForAPIIDIndexinPreOrder(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForPreOrder=0;
int updateWithIndexActionForPreOrder=0;
int updateWithoutIndexActionForPreOrder=0;
int removeActionForPreOrder=0;
int addCommitForPreOrder=0;
int updateCommitForPreOrder=0;
int removeCommitForPreOrder=0;
#endif
void CPreOrderFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pAPIIDAndOrderLocalIDIndex=new CAVLTree(maxUnit,compareForAPIIDAndOrderLocalIDIndexinPreOrder,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("PreOrder_APIIDAndOrderLocalIDIndex",pAPIIDAndOrderLocalIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("PreOrder_APIIDAndOrderLocalIDIndex");
			if(it != pIndexMap->end()) {
				pAPIIDAndOrderLocalIDIndex=new CAVLTree(maxUnit,compareForAPIIDAndOrderLocalIDIndexinPreOrder,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pAPIIDAndOrderLocalIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=1) {
		if(!reuse) {
			pAPIIDIndex=new CAVLTree(maxUnit,compareForAPIIDIndexinPreOrder,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("PreOrder_APIIDIndex",pAPIIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("PreOrder_APIIDIndex");
			if(it != pIndexMap->end()) {
				pAPIIDIndex=new CAVLTree(maxUnit,compareForAPIIDIndexinPreOrder,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pAPIIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		int hashKeySize=1572869;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("PreOrder.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pUserIDAndUserOrderLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("PreOrder_UserIDAndUserOrderLocalIDHashIndex",pUserIDAndUserOrderLocalIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("PreOrder_UserIDAndUserOrderLocalIDHashIndex");
			if(it != pIndexMap->end()) {
				pUserIDAndUserOrderLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pUserIDAndUserOrderLocalIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByAPIID=NULL;
	pActionTriggers=new vector<CPreOrderActionTrigger *>;
	pCommitTriggers=new vector<CPreOrderCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CPreOrderFactory::CPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CPreOrder),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CPreOrderFactory::CPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CPreOrder),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CPreOrderFactory::~CPreOrderFactory(void)
{
	if (runLevel>=0) {
		if (pAPIIDAndOrderLocalIDIndex!=NULL)
			delete pAPIIDAndOrderLocalIDIndex;
	}
	if (runLevel>=1) {
		if (pAPIIDIndex!=NULL)
			delete pAPIIDIndex;
	}
	if (runLevel>=0) {
		if (pUserIDAndUserOrderLocalIDHashIndex!=NULL)
			delete pUserIDAndUserOrderLocalIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CPreOrderFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CPreOrderFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pAPIIDAndOrderLocalIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=1) {
		pAPIIDIndex->output(pLogger,indent+1);
	}
}

int CPreOrderFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteablePreOrder thisPreOrder;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisPreOrder.readCSV(input,pNames))
		add(&thisPreOrder);
	fclose(input);
	delete pNames;
	return 1;
}

int CPreOrderFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "PreOrder.csv");
	return readCSV(szFileName);
}

int CPreOrderFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteablePreOrder *pPreOrder;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteablePreOrder::writeCSVHead(output);
	pPreOrder=(CWriteablePreOrder *)(pMem->getFirst());
	while (pPreOrder!=NULL) {
		if (!pPreOrder->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pPreOrder=(CWriteablePreOrder *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CPreOrderFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "PreOrder.csv");
	return writeCSV(szFileName);
}

void CPreOrderFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CPreOrderFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteablePreOrder *pPreOrder;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CPreOrderFactory={       Total Count=%d\n", pMem->getCount());
	pPreOrder=(CWriteablePreOrder *)(pMem->getFirst());
	while (pPreOrder!=NULL) {
		pPreOrder->dump(fp,index++);
		pPreOrder=(CWriteablePreOrder *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CPreOrderFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pAPIIDAndOrderLocalIDIndex->removeAll();
	}
	if (runLevel>=1) {
		pAPIIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->removeAll();
	}
}

CPreOrder *CPreOrderFactory::internalAdd(CWriteablePreOrder *pPreOrder, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForPreOrder++;
#endif
	CPreOrder *pTarget;	
	beforeAdd(pPreOrder);
	pTarget=(CPreOrder *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough PreOrder in memory database");
		return NULL;
	}
	forceCopy(pTarget, pPreOrder, sizeof(CPreOrder));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pAPIIDAndOrderLocalIDIndex->addObject(pTarget);
	}
	if (runLevel>=1) {
		pAPIIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->addObject(pTarget,pTarget->HashUserIDAndUserOrderLocalID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CPreOrder *CPreOrderFactory::add(CWriteablePreOrder *pPreOrder, CTransaction *pTransaction)
{
	pPreOrder->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pPreOrder,true);
	}
	else {
		CPreOrder *pNewPreOrder;
		pNewPreOrder = internalAdd(pPreOrder,false);
		pTransaction->addResource(CPreOrderResource::alloc(CREATE_ACTION,this,pNewPreOrder,NULL));
		return pNewPreOrder;
	}
}

void CPreOrderFactory::internalUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForPreOrder++;
	}
	else {
		updateWithoutIndexActionForPreOrder++;
	}
#endif
	CWriteablePreOrder theOldPreOrder;
	beforeUpdate(pPreOrder,pNewPreOrder);
	if (bNoTransaction) {
		forceCopy(&theOldPreOrder,pPreOrder,sizeof(CPreOrder));
	}
	if (updateIndex) {
	}

	forceCopy(pPreOrder,pNewPreOrder,sizeof(CPreOrder));
	pMem->updateObject(pPreOrder);
	if (updateIndex) {
	}
	afterUpdate(pPreOrder);
	if (bNoTransaction) {
		commitUpdate(pPreOrder,&theOldPreOrder);
	}
}

void CPreOrderFactory::update(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	pNewPreOrder->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pPreOrder,pNewPreOrder,updateIndex,true);
	}
	else {
		pTransaction->addResource(CPreOrderResource::alloc(UPDATE_ACTION,this,pPreOrder,pNewPreOrder,updateIndex));
		internalUpdate(pPreOrder,pNewPreOrder,updateIndex,false);
	}
}

void CPreOrderFactory::internalRemove(CPreOrder *pPreOrder, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForPreOrder++;
#endif
	CWriteablePreOrder theOldPreOrder;
	beforeRemove(pPreOrder);
	if (bNoTransaction) {
		forceCopy(&theOldPreOrder,pPreOrder,sizeof(CPreOrder));
	}
	if (runLevel>=0) {
		pAPIIDAndOrderLocalIDIndex->removeObject(pPreOrder);
	}
	if (runLevel>=1) {
		pAPIIDIndex->removeObject(pPreOrder);
	}
	if (runLevel>=0) {
		pUserIDAndUserOrderLocalIDHashIndex->removeObject(pPreOrder,pPreOrder->HashUserIDAndUserOrderLocalID);
	}	
	pMem->free(pPreOrder);
	if(bNoTransaction) {
		commitRemove(&theOldPreOrder);
	}
}

void CPreOrderFactory::remove(CPreOrder *pPreOrder, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pPreOrder,true);
	}
	else {
		pTransaction->addResource(CPreOrderResource::alloc(DELETE_ACTION,this,pPreOrder,NULL));
		internalRemove(pPreOrder,false);		
	}
}

CPreOrder* CPreOrderFactory::addOrUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	if(pPreOrder == NULL) {
		return add(pNewPreOrder,pTransaction);
	}
	else {
		update(pPreOrder,pNewPreOrder,pTransaction,updateIndex);
		return pPreOrder;
	}
}

void CPreOrderFactory::retrieve(CPreOrder *pPreOrder, CWriteablePreOrder *pTargetPreOrder)
{
	forceCopy(pTargetPreOrder, pPreOrder, sizeof(CPreOrder));
}
	
int CPreOrderFactory::addActionTrigger(CPreOrderActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CPreOrderFactory::removeActionTrigger(CPreOrderActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CPreOrderFactory::addCommitTrigger(CPreOrderCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CPreOrderFactory::removeCommitTrigger(CPreOrderCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CPreOrder *CPreOrderFactory::getFirst(void)
{
	CPreOrder *pResult=(CPreOrder *)(pMem->getFirst());
	return pResult;
}
	
CPreOrder *CPreOrderFactory::getNext(void)
{
	CPreOrder *pResult=(CPreOrder *)(pMem->getNext());
	return pResult;
}
	
void CPreOrderFactory::endGet(void)
{
	pMem->endGet();
}

void CPreOrderFactory::beforeAdd(CWriteablePreOrder *pPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pPreOrder);
	}
}
	
void CPreOrderFactory::afterAdd(CPreOrder *pPreOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pPreOrder);
	}
}

void CPreOrderFactory::beforeUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pNewPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pPreOrder,pNewPreOrder);
	}
}
	
void CPreOrderFactory::afterUpdate(CPreOrder *pPreOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pPreOrder);
	}
}
	
void CPreOrderFactory::beforeRemove(CPreOrder *pPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pPreOrder);
	}
}

void CPreOrderFactory::commitAdd(CPreOrder *pPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pPreOrder);
	}
}

void CPreOrderFactory::commitUpdate(CPreOrder *pPreOrder, CWriteablePreOrder *pOldPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pPreOrder,pOldPreOrder);
	}
}
	
void CPreOrderFactory::commitRemove(CWriteablePreOrder *pPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pPreOrder);
	}
}

void CPreOrderFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void CPreOrderFactory::linkAllInvestor(CInvestorFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestor(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllClientTradingID(CClientTradingIDFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkClientTradingID(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInvestorAccount(CInvestorAccountFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestorAccount(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInvestorPosition(CInvestorPositionFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestorPosition(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInstrument(CInstrumentFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInstrument(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInvestorMargin(CInvestorMarginFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestorMargin(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInvestorFee(CInvestorFeeFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestorFee(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllInvestorOptionFee(CInvestorOptionFeeFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkInvestorOptionFee(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

void CPreOrderFactory::linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory)
{
	CPreOrder *pPreOrder;
	pPreOrder=getFirst();
	while (pPreOrder != NULL) {
		pPreOrder->linkClientGroupPosition(pFactory);
		pPreOrder=getNext();
	}
	endGet();
}

#ifdef COUNT_OPERATION
int addActionForIndexPreOrder=0;
int updateWithIndexActionForIndexPreOrder=0;
int updateWithoutIndexActionForIndexPreOrder=0;
int removeActionForIndexPreOrder=0;
int addCommitForIndexPreOrder=0;
int updateCommitForIndexPreOrder=0;
int removeCommitForIndexPreOrder=0;
#endif
void CIndexPreOrderFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=1572869;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("IndexPreOrder.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pALLFldsHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("IndexPreOrder_ALLFldsHashIndex",pALLFldsHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("IndexPreOrder_ALLFldsHashIndex");
			if(it != pIndexMap->end()) {
				pALLFldsHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pALLFldsHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CIndexPreOrderActionTrigger *>;
	pCommitTriggers=new vector<CIndexPreOrderCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CIndexPreOrderFactory::CIndexPreOrderFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CIndexPreOrder),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CIndexPreOrderFactory::CIndexPreOrderFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CIndexPreOrder),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CIndexPreOrderFactory::~CIndexPreOrderFactory(void)
{
	if (runLevel>=0) {
		if (pALLFldsHashIndex!=NULL)
			delete pALLFldsHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CIndexPreOrderFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CIndexPreOrderFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CIndexPreOrderFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableIndexPreOrder thisIndexPreOrder;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisIndexPreOrder.readCSV(input,pNames))
		add(&thisIndexPreOrder);
	fclose(input);
	delete pNames;
	return 1;
}

int CIndexPreOrderFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "IndexPreOrder.csv");
	return readCSV(szFileName);
}

int CIndexPreOrderFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableIndexPreOrder *pIndexPreOrder;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableIndexPreOrder::writeCSVHead(output);
	pIndexPreOrder=(CWriteableIndexPreOrder *)(pMem->getFirst());
	while (pIndexPreOrder!=NULL) {
		if (!pIndexPreOrder->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pIndexPreOrder=(CWriteableIndexPreOrder *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CIndexPreOrderFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "IndexPreOrder.csv");
	return writeCSV(szFileName);
}

void CIndexPreOrderFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CIndexPreOrderFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableIndexPreOrder *pIndexPreOrder;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CIndexPreOrderFactory={       Total Count=%d\n", pMem->getCount());
	pIndexPreOrder=(CWriteableIndexPreOrder *)(pMem->getFirst());
	while (pIndexPreOrder!=NULL) {
		pIndexPreOrder->dump(fp,index++);
		pIndexPreOrder=(CWriteableIndexPreOrder *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CIndexPreOrderFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pALLFldsHashIndex->removeAll();
	}
}

CIndexPreOrder *CIndexPreOrderFactory::internalAdd(CWriteableIndexPreOrder *pIndexPreOrder, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForIndexPreOrder++;
#endif
	CIndexPreOrder *pTarget;	
	beforeAdd(pIndexPreOrder);
	pTarget=(CIndexPreOrder *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough IndexPreOrder in memory database");
		return NULL;
	}
	forceCopy(pTarget, pIndexPreOrder, sizeof(CIndexPreOrder));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pALLFldsHashIndex->addObject(pTarget,pTarget->HashALLFlds);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CIndexPreOrder *CIndexPreOrderFactory::add(CWriteableIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction)
{
	pIndexPreOrder->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pIndexPreOrder,true);
	}
	else {
		CIndexPreOrder *pNewIndexPreOrder;
		pNewIndexPreOrder = internalAdd(pIndexPreOrder,false);
		pTransaction->addResource(CIndexPreOrderResource::alloc(CREATE_ACTION,this,pNewIndexPreOrder,NULL));
		return pNewIndexPreOrder;
	}
}

void CIndexPreOrderFactory::internalUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForIndexPreOrder++;
	}
	else {
		updateWithoutIndexActionForIndexPreOrder++;
	}
#endif
	CWriteableIndexPreOrder theOldIndexPreOrder;
	beforeUpdate(pIndexPreOrder,pNewIndexPreOrder);
	if (bNoTransaction) {
		forceCopy(&theOldIndexPreOrder,pIndexPreOrder,sizeof(CIndexPreOrder));
	}
	if (updateIndex) {
	}

	forceCopy(pIndexPreOrder,pNewIndexPreOrder,sizeof(CIndexPreOrder));
	pMem->updateObject(pIndexPreOrder);
	if (updateIndex) {
	}
	afterUpdate(pIndexPreOrder);
	if (bNoTransaction) {
		commitUpdate(pIndexPreOrder,&theOldIndexPreOrder);
	}
}

void CIndexPreOrderFactory::update(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	pNewIndexPreOrder->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pIndexPreOrder,pNewIndexPreOrder,updateIndex,true);
	}
	else {
		pTransaction->addResource(CIndexPreOrderResource::alloc(UPDATE_ACTION,this,pIndexPreOrder,pNewIndexPreOrder,updateIndex));
		internalUpdate(pIndexPreOrder,pNewIndexPreOrder,updateIndex,false);
	}
}

void CIndexPreOrderFactory::internalRemove(CIndexPreOrder *pIndexPreOrder, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForIndexPreOrder++;
#endif
	CWriteableIndexPreOrder theOldIndexPreOrder;
	beforeRemove(pIndexPreOrder);
	if (bNoTransaction) {
		forceCopy(&theOldIndexPreOrder,pIndexPreOrder,sizeof(CIndexPreOrder));
	}
	if (runLevel>=0) {
		pALLFldsHashIndex->removeObject(pIndexPreOrder,pIndexPreOrder->HashALLFlds);
	}	
	pMem->free(pIndexPreOrder);
	if(bNoTransaction) {
		commitRemove(&theOldIndexPreOrder);
	}
}

void CIndexPreOrderFactory::remove(CIndexPreOrder *pIndexPreOrder, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pIndexPreOrder,true);
	}
	else {
		pTransaction->addResource(CIndexPreOrderResource::alloc(DELETE_ACTION,this,pIndexPreOrder,NULL));
		internalRemove(pIndexPreOrder,false);		
	}
}

CIndexPreOrder* CIndexPreOrderFactory::addOrUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder, CTransaction *pTransaction, bool updateIndex)
{
	if(pIndexPreOrder == NULL) {
		return add(pNewIndexPreOrder,pTransaction);
	}
	else {
		update(pIndexPreOrder,pNewIndexPreOrder,pTransaction,updateIndex);
		return pIndexPreOrder;
	}
}

void CIndexPreOrderFactory::retrieve(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pTargetIndexPreOrder)
{
	forceCopy(pTargetIndexPreOrder, pIndexPreOrder, sizeof(CIndexPreOrder));
}
	
int CIndexPreOrderFactory::addActionTrigger(CIndexPreOrderActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CIndexPreOrderFactory::removeActionTrigger(CIndexPreOrderActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CIndexPreOrderFactory::addCommitTrigger(CIndexPreOrderCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CIndexPreOrderFactory::removeCommitTrigger(CIndexPreOrderCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CIndexPreOrder *CIndexPreOrderFactory::getFirst(void)
{
	CIndexPreOrder *pResult=(CIndexPreOrder *)(pMem->getFirst());
	return pResult;
}
	
CIndexPreOrder *CIndexPreOrderFactory::getNext(void)
{
	CIndexPreOrder *pResult=(CIndexPreOrder *)(pMem->getNext());
	return pResult;
}
	
void CIndexPreOrderFactory::endGet(void)
{
	pMem->endGet();
}

void CIndexPreOrderFactory::beforeAdd(CWriteableIndexPreOrder *pIndexPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pIndexPreOrder);
	}
}
	
void CIndexPreOrderFactory::afterAdd(CIndexPreOrder *pIndexPreOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pIndexPreOrder);
	}
}

void CIndexPreOrderFactory::beforeUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pNewIndexPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pIndexPreOrder,pNewIndexPreOrder);
	}
}
	
void CIndexPreOrderFactory::afterUpdate(CIndexPreOrder *pIndexPreOrder)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pIndexPreOrder);
	}
}
	
void CIndexPreOrderFactory::beforeRemove(CIndexPreOrder *pIndexPreOrder)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pIndexPreOrder);
	}
}

void CIndexPreOrderFactory::commitAdd(CIndexPreOrder *pIndexPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForIndexPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pIndexPreOrder);
	}
}

void CIndexPreOrderFactory::commitUpdate(CIndexPreOrder *pIndexPreOrder, CWriteableIndexPreOrder *pOldIndexPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForIndexPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pIndexPreOrder,pOldIndexPreOrder);
	}
}
	
void CIndexPreOrderFactory::commitRemove(CWriteableIndexPreOrder *pIndexPreOrder)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForIndexPreOrder++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pIndexPreOrder);
	}
}

void CIndexPreOrderFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void CIndexPreOrderFactory::linkAllInvestor(CInvestorFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkInvestor(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllClientTradingID(CClientTradingIDFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkClientTradingID(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllInvestorAccount(CInvestorAccountFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkInvestorAccount(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllInstrument(CInstrumentFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkInstrument(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllInvestorMargin(CInvestorMarginFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkInvestorMargin(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllInvestorFee(CInvestorFeeFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkInvestorFee(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

void CIndexPreOrderFactory::linkAllClientGroupPosition(CPartClientInsGroupPositionFactory *pFactory)
{
	CIndexPreOrder *pIndexPreOrder;
	pIndexPreOrder=getFirst();
	while (pIndexPreOrder != NULL) {
		pIndexPreOrder->linkClientGroupPosition(pFactory);
		pIndexPreOrder=getNext();
	}
	endGet();
}

extern int compareForBrkIDExIDInvIDInsIDDirHedIndexinInvestorPosition(const void *pV1, const void *pV2);
extern int compareForExIDAndInstrumentIDIndexinInvestorPosition(const void *pV1, const void *pV2);
extern int compareForInvestorIDIndexinInvestorPosition(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorPosition=0;
int updateWithIndexActionForInvestorPosition=0;
int updateWithoutIndexActionForInvestorPosition=0;
int removeActionForInvestorPosition=0;
int addCommitForInvestorPosition=0;
int updateCommitForInvestorPosition=0;
int removeCommitForInvestorPosition=0;
#endif
void CInvestorPositionFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrkIDExIDInvIDInsIDDirHedIndex=new CAVLTree(maxUnit,compareForBrkIDExIDInvIDInsIDDirHedIndexinInvestorPosition,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorPosition_BrkIDExIDInvIDInsIDDirHedIndex",pBrkIDExIDInvIDInsIDDirHedIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorPosition_BrkIDExIDInvIDInsIDDirHedIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDInvIDInsIDDirHedIndex=new CAVLTree(maxUnit,compareForBrkIDExIDInvIDInsIDDirHedIndexinInvestorPosition,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDInvIDInsIDDirHedIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExIDAndInstrumentIDIndex=new CAVLTree(maxUnit,compareForExIDAndInstrumentIDIndexinInvestorPosition,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorPosition_ExIDAndInstrumentIDIndex",pExIDAndInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorPosition_ExIDAndInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExIDAndInstrumentIDIndex=new CAVLTree(maxUnit,compareForExIDAndInstrumentIDIndexinInvestorPosition,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExIDAndInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=1) {
		if(!reuse) {
			pInvestorIDIndex=new CAVLTree(maxUnit,compareForInvestorIDIndexinInvestorPosition,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorPosition_InvestorIDIndex",pInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorPosition_InvestorIDIndex");
			if(it != pIndexMap->end()) {
				pInvestorIDIndex=new CAVLTree(maxUnit,compareForInvestorIDIndexinInvestorPosition,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByExIDAndInstrumentID=NULL;
	pLastFoundInSearchByInvestorID=NULL;
	pLastFoundInSearchAllByBrokerID=NULL;
	pLastFoundInSearchAllByInstrumentID=NULL;
	pLastFoundInSearchAllByExchangeID=NULL;
	pLastFoundInSearchAllByInvestorIDAndInstrumentID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CInvestorPositionActionTrigger *>;
	pCommitTriggers=new vector<CInvestorPositionCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorPositionFactory::CInvestorPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorPosition),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorPositionFactory::CInvestorPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorPosition),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorPositionFactory::~CInvestorPositionFactory(void)
{
	if (runLevel>=0) {
		if (pBrkIDExIDInvIDInsIDDirHedIndex!=NULL)
			delete pBrkIDExIDInvIDInsIDDirHedIndex;
	}
	if (runLevel>=0) {
		if (pExIDAndInstrumentIDIndex!=NULL)
			delete pExIDAndInstrumentIDIndex;
	}
	if (runLevel>=1) {
		if (pInvestorIDIndex!=NULL)
			delete pInvestorIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorPositionFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorPositionFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrkIDExIDInvIDInsIDDirHedIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExIDAndInstrumentIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=1) {
		pInvestorIDIndex->output(pLogger,indent+1);
	}
}

int CInvestorPositionFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorPosition thisInvestorPosition;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorPosition.readCSV(input,pNames))
		add(&thisInvestorPosition);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorPositionFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorPosition.csv");
	return readCSV(szFileName);
}

int CInvestorPositionFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorPosition *pInvestorPosition;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorPosition::writeCSVHead(output);
	pInvestorPosition=(CWriteableInvestorPosition *)(pMem->getFirst());
	while (pInvestorPosition!=NULL) {
		if (!pInvestorPosition->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorPosition=(CWriteableInvestorPosition *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorPositionFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorPosition.csv");
	return writeCSV(szFileName);
}

void CInvestorPositionFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorPositionFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorPosition *pInvestorPosition;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorPositionFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorPosition=(CWriteableInvestorPosition *)(pMem->getFirst());
	while (pInvestorPosition!=NULL) {
		pInvestorPosition->dump(fp,index++);
		pInvestorPosition=(CWriteableInvestorPosition *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorPositionFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrkIDExIDInvIDInsIDDirHedIndex->removeAll();
	}
	if (runLevel>=0) {
		pExIDAndInstrumentIDIndex->removeAll();
	}
	if (runLevel>=1) {
		pInvestorIDIndex->removeAll();
	}
}

CInvestorPosition *CInvestorPositionFactory::internalAdd(CWriteableInvestorPosition *pInvestorPosition, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorPosition++;
#endif
	CInvestorPosition *pTarget;	
	beforeAdd(pInvestorPosition);
	pTarget=(CInvestorPosition *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorPosition in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorPosition, sizeof(CInvestorPosition));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrkIDExIDInvIDInsIDDirHedIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExIDAndInstrumentIDIndex->addObject(pTarget);
	}
	if (runLevel>=1) {
		pInvestorIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorPosition *CInvestorPositionFactory::add(CWriteableInvestorPosition *pInvestorPosition, CTransaction *pTransaction)
{
	pInvestorPosition->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorPosition,true);
	}
	else {
		CInvestorPosition *pNewInvestorPosition;
		pNewInvestorPosition = internalAdd(pInvestorPosition,false);
		pTransaction->addResource(CInvestorPositionResource::alloc(CREATE_ACTION,this,pNewInvestorPosition,NULL));
		return pNewInvestorPosition;
	}
}

void CInvestorPositionFactory::internalUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorPosition++;
	}
	else {
		updateWithoutIndexActionForInvestorPosition++;
	}
#endif
	CWriteableInvestorPosition theOldInvestorPosition;
	beforeUpdate(pInvestorPosition,pNewInvestorPosition);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorPosition,pInvestorPosition,sizeof(CInvestorPosition));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorPosition,pNewInvestorPosition,sizeof(CInvestorPosition));
	pMem->updateObject(pInvestorPosition);
	if (updateIndex) {
	}
	afterUpdate(pInvestorPosition);
	if (bNoTransaction) {
		commitUpdate(pInvestorPosition,&theOldInvestorPosition);
	}
}

void CInvestorPositionFactory::update(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorPosition->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorPosition,pNewInvestorPosition,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorPositionResource::alloc(UPDATE_ACTION,this,pInvestorPosition,pNewInvestorPosition,updateIndex));
		internalUpdate(pInvestorPosition,pNewInvestorPosition,updateIndex,false);
	}
}

void CInvestorPositionFactory::internalRemove(CInvestorPosition *pInvestorPosition, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorPosition++;
#endif
	CWriteableInvestorPosition theOldInvestorPosition;
	beforeRemove(pInvestorPosition);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorPosition,pInvestorPosition,sizeof(CInvestorPosition));
	}
	if (runLevel>=0) {
		pBrkIDExIDInvIDInsIDDirHedIndex->removeObject(pInvestorPosition);
	}
	if (runLevel>=0) {
		pExIDAndInstrumentIDIndex->removeObject(pInvestorPosition);
	}
	if (runLevel>=1) {
		pInvestorIDIndex->removeObject(pInvestorPosition);
	}
	pMem->free(pInvestorPosition);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorPosition);
	}
}

void CInvestorPositionFactory::remove(CInvestorPosition *pInvestorPosition, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorPosition,true);
	}
	else {
		pTransaction->addResource(CInvestorPositionResource::alloc(DELETE_ACTION,this,pInvestorPosition,NULL));
		internalRemove(pInvestorPosition,false);		
	}
}

CInvestorPosition* CInvestorPositionFactory::addOrUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorPosition == NULL) {
		return add(pNewInvestorPosition,pTransaction);
	}
	else {
		update(pInvestorPosition,pNewInvestorPosition,pTransaction,updateIndex);
		return pInvestorPosition;
	}
}

void CInvestorPositionFactory::retrieve(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pTargetInvestorPosition)
{
	forceCopy(pTargetInvestorPosition, pInvestorPosition, sizeof(CInvestorPosition));
}
	
int CInvestorPositionFactory::addActionTrigger(CInvestorPositionActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorPositionFactory::removeActionTrigger(CInvestorPositionActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorPositionFactory::addCommitTrigger(CInvestorPositionCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorPositionFactory::removeCommitTrigger(CInvestorPositionCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorPosition *CInvestorPositionFactory::getFirst(void)
{
	CInvestorPosition *pResult=(CInvestorPosition *)(pMem->getFirst());
	return pResult;
}
	
CInvestorPosition *CInvestorPositionFactory::getNext(void)
{
	CInvestorPosition *pResult=(CInvestorPosition *)(pMem->getNext());
	return pResult;
}
	
void CInvestorPositionFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorPositionFactory::beforeAdd(CWriteableInvestorPosition *pInvestorPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorPosition);
	}
}
	
void CInvestorPositionFactory::afterAdd(CInvestorPosition *pInvestorPosition)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorPosition);
	}
}

void CInvestorPositionFactory::beforeUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pNewInvestorPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorPosition,pNewInvestorPosition);
	}
}
	
void CInvestorPositionFactory::afterUpdate(CInvestorPosition *pInvestorPosition)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorPosition);
	}
}
	
void CInvestorPositionFactory::beforeRemove(CInvestorPosition *pInvestorPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorPosition);
	}
}

void CInvestorPositionFactory::commitAdd(CInvestorPosition *pInvestorPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorPosition);
	}
}

void CInvestorPositionFactory::commitUpdate(CInvestorPosition *pInvestorPosition, CWriteableInvestorPosition *pOldInvestorPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorPosition,pOldInvestorPosition);
	}
}
	
void CInvestorPositionFactory::commitRemove(CWriteableInvestorPosition *pInvestorPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorPosition);
	}
}

void CInvestorPositionFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDAccountIDIndexinInvestorAccount(const void *pV1, const void *pV2);
extern int compareForBrokerIDInvestorIDIndexinInvestorAccount(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorAccount=0;
int updateWithIndexActionForInvestorAccount=0;
int updateWithoutIndexActionForInvestorAccount=0;
int removeActionForInvestorAccount=0;
int addCommitForInvestorAccount=0;
int updateCommitForInvestorAccount=0;
int removeCommitForInvestorAccount=0;
#endif
void CInvestorAccountFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDAccountIDIndex=new CAVLTree(maxUnit,compareForBrokerIDAccountIDIndexinInvestorAccount,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorAccount_BrokerIDAccountIDIndex",pBrokerIDAccountIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorAccount_BrokerIDAccountIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDAccountIDIndex=new CAVLTree(maxUnit,compareForBrokerIDAccountIDIndexinInvestorAccount,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDAccountIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinInvestorAccount,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorAccount_BrokerIDInvestorIDIndex",pBrokerIDInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorAccount_BrokerIDInvestorIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinInvestorAccount,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByInvestorID=NULL;
	pLastFoundInSearchAllByBrokerID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CInvestorAccountActionTrigger *>;
	pCommitTriggers=new vector<CInvestorAccountCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorAccountFactory::CInvestorAccountFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorAccount),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorAccountFactory::CInvestorAccountFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorAccount),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorAccountFactory::~CInvestorAccountFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDAccountIDIndex!=NULL)
			delete pBrokerIDAccountIDIndex;
	}
	if (runLevel>=0) {
		if (pBrokerIDInvestorIDIndex!=NULL)
			delete pBrokerIDInvestorIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorAccountFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorAccountFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDAccountIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->output(pLogger,indent+1);
	}
}

int CInvestorAccountFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorAccount thisInvestorAccount;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorAccount.readCSV(input,pNames))
		add(&thisInvestorAccount);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorAccountFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorAccount.csv");
	return readCSV(szFileName);
}

int CInvestorAccountFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorAccount *pInvestorAccount;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorAccount::writeCSVHead(output);
	pInvestorAccount=(CWriteableInvestorAccount *)(pMem->getFirst());
	while (pInvestorAccount!=NULL) {
		if (!pInvestorAccount->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorAccount=(CWriteableInvestorAccount *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorAccountFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorAccount.csv");
	return writeCSV(szFileName);
}

void CInvestorAccountFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorAccountFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorAccount *pInvestorAccount;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorAccountFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorAccount=(CWriteableInvestorAccount *)(pMem->getFirst());
	while (pInvestorAccount!=NULL) {
		pInvestorAccount->dump(fp,index++);
		pInvestorAccount=(CWriteableInvestorAccount *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorAccountFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDAccountIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeAll();
	}
}

CInvestorAccount *CInvestorAccountFactory::internalAdd(CWriteableInvestorAccount *pInvestorAccount, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorAccount++;
#endif
	CInvestorAccount *pTarget;	
	beforeAdd(pInvestorAccount);
	pTarget=(CInvestorAccount *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorAccount in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorAccount, sizeof(CInvestorAccount));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDAccountIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorAccount *CInvestorAccountFactory::add(CWriteableInvestorAccount *pInvestorAccount, CTransaction *pTransaction)
{
	if(pInvestorAccount->AccountID=="000001")
	{
		REPORT_EVENT(LOG_CRITICAL,"InvestorAccount","add InvestorMargin:%.2f",pInvestorAccount->FrozenMargin);
	}
	pInvestorAccount->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorAccount,true);
	}
	else {
		CInvestorAccount *pNewInvestorAccount;
		pNewInvestorAccount = internalAdd(pInvestorAccount,false);
		pTransaction->addResource(CInvestorAccountResource::alloc(CREATE_ACTION,this,pNewInvestorAccount,NULL));
		return pNewInvestorAccount;
	}
}

void CInvestorAccountFactory::internalUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorAccount++;
	}
	else {
		updateWithoutIndexActionForInvestorAccount++;
	}
#endif
	CWriteableInvestorAccount theOldInvestorAccount;
	beforeUpdate(pInvestorAccount,pNewInvestorAccount);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorAccount,pInvestorAccount,sizeof(CInvestorAccount));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorAccount,pNewInvestorAccount,sizeof(CInvestorAccount));
	pMem->updateObject(pInvestorAccount);
	if (updateIndex) {
	}
	afterUpdate(pInvestorAccount);
	if (bNoTransaction) {
		commitUpdate(pInvestorAccount,&theOldInvestorAccount);
	}
}

void CInvestorAccountFactory::update(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction, bool updateIndex)
{
	if(pNewInvestorAccount->AccountID=="000001")
	{
		REPORT_EVENT(LOG_CRITICAL,"InvestorAccount"," update InvestorMargin:%.2f",pNewInvestorAccount->FrozenMargin);
	}
	pNewInvestorAccount->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorAccount,pNewInvestorAccount,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorAccountResource::alloc(UPDATE_ACTION,this,pInvestorAccount,pNewInvestorAccount,updateIndex));
		internalUpdate(pInvestorAccount,pNewInvestorAccount,updateIndex,false);
	}
}

void CInvestorAccountFactory::internalRemove(CInvestorAccount *pInvestorAccount, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorAccount++;
#endif
	CWriteableInvestorAccount theOldInvestorAccount;
	beforeRemove(pInvestorAccount);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorAccount,pInvestorAccount,sizeof(CInvestorAccount));
	}
	if (runLevel>=0) {
		pBrokerIDAccountIDIndex->removeObject(pInvestorAccount);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeObject(pInvestorAccount);
	}
	pMem->free(pInvestorAccount);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorAccount);
	}
}

void CInvestorAccountFactory::remove(CInvestorAccount *pInvestorAccount, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorAccount,true);
	}
	else {
		pTransaction->addResource(CInvestorAccountResource::alloc(DELETE_ACTION,this,pInvestorAccount,NULL));
		internalRemove(pInvestorAccount,false);		
	}
}

CInvestorAccount* CInvestorAccountFactory::addOrUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount, CTransaction *pTransaction, bool updateIndex)
{
	if(pNewInvestorAccount->AccountID=="08000800")
	{
		REPORT_EVENT(LOG_CRITICAL,"InvestorAccount","InvestorMargin:%.2f",pNewInvestorAccount->Margin);
	}
	if(pInvestorAccount == NULL) {
		return add(pNewInvestorAccount,pTransaction);
	}
	else {
		update(pInvestorAccount,pNewInvestorAccount,pTransaction,updateIndex);
		return pInvestorAccount;
	}
}

void CInvestorAccountFactory::retrieve(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pTargetInvestorAccount)
{
	forceCopy(pTargetInvestorAccount, pInvestorAccount, sizeof(CInvestorAccount));
}
	
int CInvestorAccountFactory::addActionTrigger(CInvestorAccountActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorAccountFactory::removeActionTrigger(CInvestorAccountActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorAccountFactory::addCommitTrigger(CInvestorAccountCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorAccountFactory::removeCommitTrigger(CInvestorAccountCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorAccount *CInvestorAccountFactory::getFirst(void)
{
	CInvestorAccount *pResult=(CInvestorAccount *)(pMem->getFirst());
	return pResult;
}
	
CInvestorAccount *CInvestorAccountFactory::getNext(void)
{
	CInvestorAccount *pResult=(CInvestorAccount *)(pMem->getNext());
	return pResult;
}
	
void CInvestorAccountFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorAccountFactory::beforeAdd(CWriteableInvestorAccount *pInvestorAccount)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorAccount);
	}
}
	
void CInvestorAccountFactory::afterAdd(CInvestorAccount *pInvestorAccount)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorAccount);
	}
}

void CInvestorAccountFactory::beforeUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pNewInvestorAccount)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorAccount,pNewInvestorAccount);
	}
}
	
void CInvestorAccountFactory::afterUpdate(CInvestorAccount *pInvestorAccount)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorAccount);
	}
}
	
void CInvestorAccountFactory::beforeRemove(CInvestorAccount *pInvestorAccount)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorAccount);
	}
}

void CInvestorAccountFactory::commitAdd(CInvestorAccount *pInvestorAccount)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorAccount++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorAccount);
	}
}

void CInvestorAccountFactory::commitUpdate(CInvestorAccount *pInvestorAccount, CWriteableInvestorAccount *pOldInvestorAccount)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorAccount++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorAccount,pOldInvestorAccount);
	}
}
	
void CInvestorAccountFactory::commitRemove(CWriteableInvestorAccount *pInvestorAccount)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorAccount++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorAccount);
	}
}

void CInvestorAccountFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDAccountSeqNoIndexinInvestorAccountDeposit(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorAccountDeposit=0;
int updateWithIndexActionForInvestorAccountDeposit=0;
int updateWithoutIndexActionForInvestorAccountDeposit=0;
int removeActionForInvestorAccountDeposit=0;
int addCommitForInvestorAccountDeposit=0;
int updateCommitForInvestorAccountDeposit=0;
int removeCommitForInvestorAccountDeposit=0;
#endif
void CInvestorAccountDepositFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDAccountSeqNoIndex=new CAVLTree(maxUnit,compareForBrokerIDAccountSeqNoIndexinInvestorAccountDeposit,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorAccountDeposit_BrokerIDAccountSeqNoIndex",pBrokerIDAccountSeqNoIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorAccountDeposit_BrokerIDAccountSeqNoIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDAccountSeqNoIndex=new CAVLTree(maxUnit,compareForBrokerIDAccountSeqNoIndexinInvestorAccountDeposit,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDAccountSeqNoIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CInvestorAccountDepositActionTrigger *>;
	pCommitTriggers=new vector<CInvestorAccountDepositCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorAccountDepositFactory::CInvestorAccountDepositFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorAccountDeposit),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorAccountDepositFactory::CInvestorAccountDepositFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorAccountDeposit),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorAccountDepositFactory::~CInvestorAccountDepositFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDAccountSeqNoIndex!=NULL)
			delete pBrokerIDAccountSeqNoIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorAccountDepositFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorAccountDepositFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDAccountSeqNoIndex->output(pLogger,indent+1);
	}
}

int CInvestorAccountDepositFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorAccountDeposit thisInvestorAccountDeposit;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorAccountDeposit.readCSV(input,pNames))
		add(&thisInvestorAccountDeposit);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorAccountDepositFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorAccountDeposit.csv");
	return readCSV(szFileName);
}

int CInvestorAccountDepositFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorAccountDeposit *pInvestorAccountDeposit;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorAccountDeposit::writeCSVHead(output);
	pInvestorAccountDeposit=(CWriteableInvestorAccountDeposit *)(pMem->getFirst());
	while (pInvestorAccountDeposit!=NULL) {
		if (!pInvestorAccountDeposit->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorAccountDeposit=(CWriteableInvestorAccountDeposit *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorAccountDepositFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorAccountDeposit.csv");
	return writeCSV(szFileName);
}

void CInvestorAccountDepositFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorAccountDepositFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorAccountDeposit *pInvestorAccountDeposit;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorAccountDepositFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorAccountDeposit=(CWriteableInvestorAccountDeposit *)(pMem->getFirst());
	while (pInvestorAccountDeposit!=NULL) {
		pInvestorAccountDeposit->dump(fp,index++);
		pInvestorAccountDeposit=(CWriteableInvestorAccountDeposit *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorAccountDepositFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDAccountSeqNoIndex->removeAll();
	}
}

CInvestorAccountDeposit *CInvestorAccountDepositFactory::internalAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorAccountDeposit++;
#endif
	CInvestorAccountDeposit *pTarget;	
	beforeAdd(pInvestorAccountDeposit);
	pTarget=(CInvestorAccountDeposit *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorAccountDeposit in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorAccountDeposit, sizeof(CInvestorAccountDeposit));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDAccountSeqNoIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorAccountDeposit *CInvestorAccountDepositFactory::add(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction)
{
	pInvestorAccountDeposit->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorAccountDeposit,true);
	}
	else {
		CInvestorAccountDeposit *pNewInvestorAccountDeposit;
		pNewInvestorAccountDeposit = internalAdd(pInvestorAccountDeposit,false);
		pTransaction->addResource(CInvestorAccountDepositResource::alloc(CREATE_ACTION,this,pNewInvestorAccountDeposit,NULL));
		return pNewInvestorAccountDeposit;
	}
}

void CInvestorAccountDepositFactory::internalUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorAccountDeposit++;
	}
	else {
		updateWithoutIndexActionForInvestorAccountDeposit++;
	}
#endif
	CWriteableInvestorAccountDeposit theOldInvestorAccountDeposit;
	beforeUpdate(pInvestorAccountDeposit,pNewInvestorAccountDeposit);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorAccountDeposit,pInvestorAccountDeposit,sizeof(CInvestorAccountDeposit));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorAccountDeposit,pNewInvestorAccountDeposit,sizeof(CInvestorAccountDeposit));
	pMem->updateObject(pInvestorAccountDeposit);
	if (updateIndex) {
	}
	afterUpdate(pInvestorAccountDeposit);
	if (bNoTransaction) {
		commitUpdate(pInvestorAccountDeposit,&theOldInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::update(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorAccountDeposit->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorAccountDeposit,pNewInvestorAccountDeposit,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorAccountDepositResource::alloc(UPDATE_ACTION,this,pInvestorAccountDeposit,pNewInvestorAccountDeposit,updateIndex));
		internalUpdate(pInvestorAccountDeposit,pNewInvestorAccountDeposit,updateIndex,false);
	}
}

void CInvestorAccountDepositFactory::internalRemove(CInvestorAccountDeposit *pInvestorAccountDeposit, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorAccountDeposit++;
#endif
	CWriteableInvestorAccountDeposit theOldInvestorAccountDeposit;
	beforeRemove(pInvestorAccountDeposit);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorAccountDeposit,pInvestorAccountDeposit,sizeof(CInvestorAccountDeposit));
	}
	if (runLevel>=0) {
		pBrokerIDAccountSeqNoIndex->removeObject(pInvestorAccountDeposit);
	}
	pMem->free(pInvestorAccountDeposit);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::remove(CInvestorAccountDeposit *pInvestorAccountDeposit, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorAccountDeposit,true);
	}
	else {
		pTransaction->addResource(CInvestorAccountDepositResource::alloc(DELETE_ACTION,this,pInvestorAccountDeposit,NULL));
		internalRemove(pInvestorAccountDeposit,false);		
	}
}

CInvestorAccountDeposit* CInvestorAccountDepositFactory::addOrUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorAccountDeposit == NULL) {
		return add(pNewInvestorAccountDeposit,pTransaction);
	}
	else {
		update(pInvestorAccountDeposit,pNewInvestorAccountDeposit,pTransaction,updateIndex);
		return pInvestorAccountDeposit;
	}
}

void CInvestorAccountDepositFactory::retrieve(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pTargetInvestorAccountDeposit)
{
	forceCopy(pTargetInvestorAccountDeposit, pInvestorAccountDeposit, sizeof(CInvestorAccountDeposit));
}
	
int CInvestorAccountDepositFactory::addActionTrigger(CInvestorAccountDepositActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorAccountDepositFactory::removeActionTrigger(CInvestorAccountDepositActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorAccountDepositFactory::addCommitTrigger(CInvestorAccountDepositCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorAccountDepositFactory::removeCommitTrigger(CInvestorAccountDepositCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorAccountDeposit *CInvestorAccountDepositFactory::getFirst(void)
{
	CInvestorAccountDeposit *pResult=(CInvestorAccountDeposit *)(pMem->getFirst());
	return pResult;
}
	
CInvestorAccountDeposit *CInvestorAccountDepositFactory::getNext(void)
{
	CInvestorAccountDeposit *pResult=(CInvestorAccountDeposit *)(pMem->getNext());
	return pResult;
}
	
void CInvestorAccountDepositFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorAccountDepositFactory::beforeAdd(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorAccountDeposit);
	}
}
	
void CInvestorAccountDepositFactory::afterAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::beforeUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pNewInvestorAccountDeposit)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorAccountDeposit,pNewInvestorAccountDeposit);
	}
}
	
void CInvestorAccountDepositFactory::afterUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorAccountDeposit);
	}
}
	
void CInvestorAccountDepositFactory::beforeRemove(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::commitAdd(CInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorAccountDeposit++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::commitUpdate(CInvestorAccountDeposit *pInvestorAccountDeposit, CWriteableInvestorAccountDeposit *pOldInvestorAccountDeposit)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorAccountDeposit++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorAccountDeposit,pOldInvestorAccountDeposit);
	}
}
	
void CInvestorAccountDepositFactory::commitRemove(CWriteableInvestorAccountDeposit *pInvestorAccountDeposit)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorAccountDeposit++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorAccountDeposit);
	}
}

void CInvestorAccountDepositFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForExchangeIDIndexinExchange(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForExchange=0;
int updateWithIndexActionForExchange=0;
int updateWithoutIndexActionForExchange=0;
int removeActionForExchange=0;
int addCommitForExchange=0;
int updateCommitForExchange=0;
int removeCommitForExchange=0;
#endif
void CExchangeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDIndex=new CAVLTree(maxUnit,compareForExchangeIDIndexinExchange,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Exchange_ExchangeIDIndex",pExchangeIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Exchange_ExchangeIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDIndex=new CAVLTree(maxUnit,compareForExchangeIDIndexinExchange,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchStartByExchangeID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CExchangeActionTrigger *>;
	pCommitTriggers=new vector<CExchangeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CExchangeFactory::CExchangeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CExchange),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CExchangeFactory::CExchangeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CExchange),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CExchangeFactory::~CExchangeFactory(void)
{
	if (runLevel>=0) {
		if (pExchangeIDIndex!=NULL)
			delete pExchangeIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CExchangeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CExchangeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pExchangeIDIndex->output(pLogger,indent+1);
	}
}

int CExchangeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableExchange thisExchange;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisExchange.readCSV(input,pNames))
		add(&thisExchange);
	fclose(input);
	delete pNames;
	return 1;
}

int CExchangeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Exchange.csv");
	return readCSV(szFileName);
}

int CExchangeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableExchange *pExchange;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableExchange::writeCSVHead(output);
	pExchange=(CWriteableExchange *)(pMem->getFirst());
	while (pExchange!=NULL) {
		if (!pExchange->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pExchange=(CWriteableExchange *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CExchangeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Exchange.csv");
	return writeCSV(szFileName);
}

void CExchangeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CExchangeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableExchange *pExchange;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CExchangeFactory={       Total Count=%d\n", pMem->getCount());
	pExchange=(CWriteableExchange *)(pMem->getFirst());
	while (pExchange!=NULL) {
		pExchange->dump(fp,index++);
		pExchange=(CWriteableExchange *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CExchangeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pExchangeIDIndex->removeAll();
	}
}

CExchange *CExchangeFactory::internalAdd(CWriteableExchange *pExchange, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForExchange++;
#endif
	CExchange *pTarget;	
	beforeAdd(pExchange);
	pTarget=(CExchange *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Exchange in memory database");
		return NULL;
	}
	forceCopy(pTarget, pExchange, sizeof(CExchange));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pExchangeIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CExchange *CExchangeFactory::add(CWriteableExchange *pExchange, CTransaction *pTransaction)
{
	pExchange->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pExchange,true);
	}
	else {
		CExchange *pNewExchange;
		pNewExchange = internalAdd(pExchange,false);
		pTransaction->addResource(CExchangeResource::alloc(CREATE_ACTION,this,pNewExchange,NULL));
		return pNewExchange;
	}
}

void CExchangeFactory::internalUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForExchange++;
	}
	else {
		updateWithoutIndexActionForExchange++;
	}
#endif
	CWriteableExchange theOldExchange;
	beforeUpdate(pExchange,pNewExchange);
	if (bNoTransaction) {
		forceCopy(&theOldExchange,pExchange,sizeof(CExchange));
	}
	if (updateIndex) {
	}

	forceCopy(pExchange,pNewExchange,sizeof(CExchange));
	pMem->updateObject(pExchange);
	if (updateIndex) {
	}
	afterUpdate(pExchange);
	if (bNoTransaction) {
		commitUpdate(pExchange,&theOldExchange);
	}
}

void CExchangeFactory::update(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction, bool updateIndex)
{
	pNewExchange->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pExchange,pNewExchange,updateIndex,true);
	}
	else {
		pTransaction->addResource(CExchangeResource::alloc(UPDATE_ACTION,this,pExchange,pNewExchange,updateIndex));
		internalUpdate(pExchange,pNewExchange,updateIndex,false);
	}
}

void CExchangeFactory::internalRemove(CExchange *pExchange, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForExchange++;
#endif
	CWriteableExchange theOldExchange;
	beforeRemove(pExchange);
	if (bNoTransaction) {
		forceCopy(&theOldExchange,pExchange,sizeof(CExchange));
	}
	if (runLevel>=0) {
		pExchangeIDIndex->removeObject(pExchange);
	}
	pMem->free(pExchange);
	if(bNoTransaction) {
		commitRemove(&theOldExchange);
	}
}

void CExchangeFactory::remove(CExchange *pExchange, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pExchange,true);
	}
	else {
		pTransaction->addResource(CExchangeResource::alloc(DELETE_ACTION,this,pExchange,NULL));
		internalRemove(pExchange,false);		
	}
}

CExchange* CExchangeFactory::addOrUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange, CTransaction *pTransaction, bool updateIndex)
{
	if(pExchange == NULL) {
		return add(pNewExchange,pTransaction);
	}
	else {
		update(pExchange,pNewExchange,pTransaction,updateIndex);
		return pExchange;
	}
}

void CExchangeFactory::retrieve(CExchange *pExchange, CWriteableExchange *pTargetExchange)
{
	forceCopy(pTargetExchange, pExchange, sizeof(CExchange));
}
	
int CExchangeFactory::addActionTrigger(CExchangeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CExchangeFactory::removeActionTrigger(CExchangeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CExchangeFactory::addCommitTrigger(CExchangeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CExchangeFactory::removeCommitTrigger(CExchangeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CExchange *CExchangeFactory::getFirst(void)
{
	CExchange *pResult=(CExchange *)(pMem->getFirst());
	return pResult;
}
	
CExchange *CExchangeFactory::getNext(void)
{
	CExchange *pResult=(CExchange *)(pMem->getNext());
	return pResult;
}
	
void CExchangeFactory::endGet(void)
{
	pMem->endGet();
}

void CExchangeFactory::beforeAdd(CWriteableExchange *pExchange)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pExchange);
	}
}
	
void CExchangeFactory::afterAdd(CExchange *pExchange)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pExchange);
	}
}

void CExchangeFactory::beforeUpdate(CExchange *pExchange, CWriteableExchange *pNewExchange)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pExchange,pNewExchange);
	}
}
	
void CExchangeFactory::afterUpdate(CExchange *pExchange)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pExchange);
	}
}
	
void CExchangeFactory::beforeRemove(CExchange *pExchange)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pExchange);
	}
}

void CExchangeFactory::commitAdd(CExchange *pExchange)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForExchange++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pExchange);
	}
}

void CExchangeFactory::commitUpdate(CExchange *pExchange, CWriteableExchange *pOldExchange)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForExchange++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pExchange,pOldExchange);
	}
}
	
void CExchangeFactory::commitRemove(CWriteableExchange *pExchange)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForExchange++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pExchange);
	}
}

void CExchangeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDExchangeIDSeatIDIndexinSeat(const void *pV1, const void *pV2);
extern int compareForExchangeIDParticipantIDSeatIDIndexinSeat(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForSeat=0;
int updateWithIndexActionForSeat=0;
int updateWithoutIndexActionForSeat=0;
int removeActionForSeat=0;
int addCommitForSeat=0;
int updateCommitForSeat=0;
int removeCommitForSeat=0;
#endif
void CSeatFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDExchangeIDSeatIDIndex=new CAVLTree(maxUnit,compareForBrokerIDExchangeIDSeatIDIndexinSeat,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Seat_BrokerIDExchangeIDSeatIDIndex",pBrokerIDExchangeIDSeatIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Seat_BrokerIDExchangeIDSeatIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDExchangeIDSeatIDIndex=new CAVLTree(maxUnit,compareForBrokerIDExchangeIDSeatIDIndexinSeat,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDExchangeIDSeatIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDParticipantIDSeatIDIndex=new CAVLTree(maxUnit,compareForExchangeIDParticipantIDSeatIDIndexinSeat,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Seat_ExchangeIDParticipantIDSeatIDIndex",pExchangeIDParticipantIDSeatIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Seat_ExchangeIDParticipantIDSeatIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDParticipantIDSeatIDIndex=new CAVLTree(maxUnit,compareForExchangeIDParticipantIDSeatIDIndexinSeat,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDParticipantIDSeatIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CSeatActionTrigger *>;
	pCommitTriggers=new vector<CSeatCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CSeatFactory::CSeatFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSeat),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CSeatFactory::CSeatFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSeat),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CSeatFactory::~CSeatFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDExchangeIDSeatIDIndex!=NULL)
			delete pBrokerIDExchangeIDSeatIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDParticipantIDSeatIDIndex!=NULL)
			delete pExchangeIDParticipantIDSeatIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CSeatFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSeatFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDExchangeIDSeatIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDParticipantIDSeatIDIndex->output(pLogger,indent+1);
	}
}

int CSeatFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableSeat thisSeat;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisSeat.readCSV(input,pNames))
		add(&thisSeat);
	fclose(input);
	delete pNames;
	return 1;
}

int CSeatFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Seat.csv");
	return readCSV(szFileName);
}

int CSeatFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableSeat *pSeat;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableSeat::writeCSVHead(output);
	pSeat=(CWriteableSeat *)(pMem->getFirst());
	while (pSeat!=NULL) {
		if (!pSeat->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pSeat=(CWriteableSeat *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CSeatFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Seat.csv");
	return writeCSV(szFileName);
}

void CSeatFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CSeatFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableSeat *pSeat;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CSeatFactory={       Total Count=%d\n", pMem->getCount());
	pSeat=(CWriteableSeat *)(pMem->getFirst());
	while (pSeat!=NULL) {
		pSeat->dump(fp,index++);
		pSeat=(CWriteableSeat *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CSeatFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDExchangeIDSeatIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDParticipantIDSeatIDIndex->removeAll();
	}
}

CSeat *CSeatFactory::internalAdd(CWriteableSeat *pSeat, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForSeat++;
#endif
	CSeat *pTarget;	
	beforeAdd(pSeat);
	pTarget=(CSeat *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Seat in memory database");
		return NULL;
	}
	forceCopy(pTarget, pSeat, sizeof(CSeat));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDExchangeIDSeatIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDParticipantIDSeatIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CSeat *CSeatFactory::add(CWriteableSeat *pSeat, CTransaction *pTransaction)
{
	pSeat->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pSeat,true);
	}
	else {
		CSeat *pNewSeat;
		pNewSeat = internalAdd(pSeat,false);
		pTransaction->addResource(CSeatResource::alloc(CREATE_ACTION,this,pNewSeat,NULL));
		return pNewSeat;
	}
}

void CSeatFactory::internalUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForSeat++;
	}
	else {
		updateWithoutIndexActionForSeat++;
	}
#endif
	CWriteableSeat theOldSeat;
	beforeUpdate(pSeat,pNewSeat);
	if (bNoTransaction) {
		forceCopy(&theOldSeat,pSeat,sizeof(CSeat));
	}
	if (updateIndex) {
	}

	forceCopy(pSeat,pNewSeat,sizeof(CSeat));
	pMem->updateObject(pSeat);
	if (updateIndex) {
	}
	afterUpdate(pSeat);
	if (bNoTransaction) {
		commitUpdate(pSeat,&theOldSeat);
	}
}

void CSeatFactory::update(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction, bool updateIndex)
{
	pNewSeat->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pSeat,pNewSeat,updateIndex,true);
	}
	else {
		pTransaction->addResource(CSeatResource::alloc(UPDATE_ACTION,this,pSeat,pNewSeat,updateIndex));
		internalUpdate(pSeat,pNewSeat,updateIndex,false);
	}
}

void CSeatFactory::internalRemove(CSeat *pSeat, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForSeat++;
#endif
	CWriteableSeat theOldSeat;
	beforeRemove(pSeat);
	if (bNoTransaction) {
		forceCopy(&theOldSeat,pSeat,sizeof(CSeat));
	}
	if (runLevel>=0) {
		pBrokerIDExchangeIDSeatIDIndex->removeObject(pSeat);
	}
	if (runLevel>=0) {
		pExchangeIDParticipantIDSeatIDIndex->removeObject(pSeat);
	}
	pMem->free(pSeat);
	if(bNoTransaction) {
		commitRemove(&theOldSeat);
	}
}

void CSeatFactory::remove(CSeat *pSeat, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pSeat,true);
	}
	else {
		pTransaction->addResource(CSeatResource::alloc(DELETE_ACTION,this,pSeat,NULL));
		internalRemove(pSeat,false);		
	}
}

CSeat* CSeatFactory::addOrUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat, CTransaction *pTransaction, bool updateIndex)
{
	if(pSeat == NULL) {
		return add(pNewSeat,pTransaction);
	}
	else {
		update(pSeat,pNewSeat,pTransaction,updateIndex);
		return pSeat;
	}
}

void CSeatFactory::retrieve(CSeat *pSeat, CWriteableSeat *pTargetSeat)
{
	forceCopy(pTargetSeat, pSeat, sizeof(CSeat));
}
	
int CSeatFactory::addActionTrigger(CSeatActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CSeatFactory::removeActionTrigger(CSeatActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CSeatFactory::addCommitTrigger(CSeatCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CSeatFactory::removeCommitTrigger(CSeatCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CSeat *CSeatFactory::getFirst(void)
{
	CSeat *pResult=(CSeat *)(pMem->getFirst());
	return pResult;
}
	
CSeat *CSeatFactory::getNext(void)
{
	CSeat *pResult=(CSeat *)(pMem->getNext());
	return pResult;
}
	
void CSeatFactory::endGet(void)
{
	pMem->endGet();
}

void CSeatFactory::beforeAdd(CWriteableSeat *pSeat)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pSeat);
	}
}
	
void CSeatFactory::afterAdd(CSeat *pSeat)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pSeat);
	}
}

void CSeatFactory::beforeUpdate(CSeat *pSeat, CWriteableSeat *pNewSeat)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pSeat,pNewSeat);
	}
}
	
void CSeatFactory::afterUpdate(CSeat *pSeat)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pSeat);
	}
}
	
void CSeatFactory::beforeRemove(CSeat *pSeat)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pSeat);
	}
}

void CSeatFactory::commitAdd(CSeat *pSeat)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForSeat++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pSeat);
	}
}

void CSeatFactory::commitUpdate(CSeat *pSeat, CWriteableSeat *pOldSeat)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForSeat++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pSeat,pOldSeat);
	}
}
	
void CSeatFactory::commitRemove(CWriteableSeat *pSeat)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForSeat++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pSeat);
	}
}

void CSeatFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForExchangeIDInstrumentIDIndexinInstrument(const void *pV1, const void *pV2);
extern int compareForInstrumentIDIndexinInstrument(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInstrument=0;
int updateWithIndexActionForInstrument=0;
int updateWithoutIndexActionForInstrument=0;
int removeActionForInstrument=0;
int addCommitForInstrument=0;
int updateCommitForInstrument=0;
int removeCommitForInstrument=0;
#endif
void CInstrumentFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDInstrumentIDIndexinInstrument,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Instrument_ExchangeIDInstrumentIDIndex",pExchangeIDInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Instrument_ExchangeIDInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDInstrumentIDIndexinInstrument,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pInstrumentIDIndex=new CAVLTree(maxUnit,compareForInstrumentIDIndexinInstrument,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Instrument_InstrumentIDIndex",pInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Instrument_InstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pInstrumentIDIndex=new CAVLTree(maxUnit,compareForInstrumentIDIndexinInstrument,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByInstrumentID=NULL;
	pLastFoundInSearchAllByExchangeID=NULL;
	pLastFoundInSearchAllByProductID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CInstrumentActionTrigger *>;
	pCommitTriggers=new vector<CInstrumentCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInstrumentFactory::CInstrumentFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInstrument),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInstrumentFactory::CInstrumentFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInstrument),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInstrumentFactory::~CInstrumentFactory(void)
{
	if (runLevel>=0) {
		if (pExchangeIDInstrumentIDIndex!=NULL)
			delete pExchangeIDInstrumentIDIndex;
	}
	if (runLevel>=0) {
		if (pInstrumentIDIndex!=NULL)
			delete pInstrumentIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInstrumentFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pExchangeIDInstrumentIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pInstrumentIDIndex->output(pLogger,indent+1);
	}
}

int CInstrumentFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInstrument thisInstrument;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInstrument.readCSV(input,pNames))
		add(&thisInstrument);
	fclose(input);
	delete pNames;
	return 1;
}

int CInstrumentFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Instrument.csv");
	return readCSV(szFileName);
}

int CInstrumentFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInstrument *pInstrument;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInstrument::writeCSVHead(output);
	pInstrument=(CWriteableInstrument *)(pMem->getFirst());
	while (pInstrument!=NULL) {
		if (!pInstrument->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInstrument=(CWriteableInstrument *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInstrumentFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Instrument.csv");
	return writeCSV(szFileName);
}

void CInstrumentFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInstrumentFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInstrument *pInstrument;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInstrumentFactory={       Total Count=%d\n", pMem->getCount());
	pInstrument=(CWriteableInstrument *)(pMem->getFirst());
	while (pInstrument!=NULL) {
		pInstrument->dump(fp,index++);
		pInstrument=(CWriteableInstrument *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInstrumentFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pExchangeIDInstrumentIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pInstrumentIDIndex->removeAll();
	}
}

CInstrument *CInstrumentFactory::internalAdd(CWriteableInstrument *pInstrument, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInstrument++;
#endif
	CInstrument *pTarget;	
	beforeAdd(pInstrument);
	pTarget=(CInstrument *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Instrument in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInstrument, sizeof(CInstrument));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pExchangeIDInstrumentIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pInstrumentIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInstrument *CInstrumentFactory::add(CWriteableInstrument *pInstrument, CTransaction *pTransaction)
{
	pInstrument->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInstrument,true);
	}
	else {
		CInstrument *pNewInstrument;
		pNewInstrument = internalAdd(pInstrument,false);
		pTransaction->addResource(CInstrumentResource::alloc(CREATE_ACTION,this,pNewInstrument,NULL));
		return pNewInstrument;
	}
}

void CInstrumentFactory::internalUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInstrument++;
	}
	else {
		updateWithoutIndexActionForInstrument++;
	}
#endif
	CWriteableInstrument theOldInstrument;
	beforeUpdate(pInstrument,pNewInstrument);
	if (bNoTransaction) {
		forceCopy(&theOldInstrument,pInstrument,sizeof(CInstrument));
	}
	if (updateIndex) {
	}

	forceCopy(pInstrument,pNewInstrument,sizeof(CInstrument));
	pMem->updateObject(pInstrument);
	if (updateIndex) {
	}
	afterUpdate(pInstrument);
	if (bNoTransaction) {
		commitUpdate(pInstrument,&theOldInstrument);
	}
}

void CInstrumentFactory::update(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction, bool updateIndex)
{
	pNewInstrument->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInstrument,pNewInstrument,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInstrumentResource::alloc(UPDATE_ACTION,this,pInstrument,pNewInstrument,updateIndex));
		internalUpdate(pInstrument,pNewInstrument,updateIndex,false);
	}
}

void CInstrumentFactory::internalRemove(CInstrument *pInstrument, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInstrument++;
#endif
	CWriteableInstrument theOldInstrument;
	beforeRemove(pInstrument);
	if (bNoTransaction) {
		forceCopy(&theOldInstrument,pInstrument,sizeof(CInstrument));
	}
	if (runLevel>=0) {
		pExchangeIDInstrumentIDIndex->removeObject(pInstrument);
	}
	if (runLevel>=0) {
		pInstrumentIDIndex->removeObject(pInstrument);
	}
	pMem->free(pInstrument);
	if(bNoTransaction) {
		commitRemove(&theOldInstrument);
	}
}

void CInstrumentFactory::remove(CInstrument *pInstrument, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInstrument,true);
	}
	else {
		pTransaction->addResource(CInstrumentResource::alloc(DELETE_ACTION,this,pInstrument,NULL));
		internalRemove(pInstrument,false);		
	}
}

CInstrument* CInstrumentFactory::addOrUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument, CTransaction *pTransaction, bool updateIndex)
{
	if(pInstrument == NULL) {
		return add(pNewInstrument,pTransaction);
	}
	else {
		update(pInstrument,pNewInstrument,pTransaction,updateIndex);
		return pInstrument;
	}
}

void CInstrumentFactory::retrieve(CInstrument *pInstrument, CWriteableInstrument *pTargetInstrument)
{
	forceCopy(pTargetInstrument, pInstrument, sizeof(CInstrument));
}
	
int CInstrumentFactory::addActionTrigger(CInstrumentActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInstrumentFactory::removeActionTrigger(CInstrumentActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInstrumentFactory::addCommitTrigger(CInstrumentCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInstrumentFactory::removeCommitTrigger(CInstrumentCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInstrument *CInstrumentFactory::getFirst(void)
{
	CInstrument *pResult=(CInstrument *)(pMem->getFirst());
	return pResult;
}
	
CInstrument *CInstrumentFactory::getNext(void)
{
	CInstrument *pResult=(CInstrument *)(pMem->getNext());
	return pResult;
}
	
void CInstrumentFactory::endGet(void)
{
	pMem->endGet();
}

void CInstrumentFactory::beforeAdd(CWriteableInstrument *pInstrument)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInstrument);
	}
}
	
void CInstrumentFactory::afterAdd(CInstrument *pInstrument)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInstrument);
	}
}

void CInstrumentFactory::beforeUpdate(CInstrument *pInstrument, CWriteableInstrument *pNewInstrument)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInstrument,pNewInstrument);
	}
}
	
void CInstrumentFactory::afterUpdate(CInstrument *pInstrument)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInstrument);
	}
}
	
void CInstrumentFactory::beforeRemove(CInstrument *pInstrument)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInstrument);
	}
}

void CInstrumentFactory::commitAdd(CInstrument *pInstrument)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInstrument++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInstrument);
	}
}

void CInstrumentFactory::commitUpdate(CInstrument *pInstrument, CWriteableInstrument *pOldInstrument)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInstrument++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInstrument,pOldInstrument);
	}
}
	
void CInstrumentFactory::commitRemove(CWriteableInstrument *pInstrument)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInstrument++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInstrument);
	}
}

void CInstrumentFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForExchangeIDArbiInstrumentIDSingelInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2);
extern int compareForExchangeIDArbiInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2);
extern int compareForExchangeIDSingleInstrumentIDIndexinCmbInstrumentDetail(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForCmbInstrumentDetail=0;
int updateWithIndexActionForCmbInstrumentDetail=0;
int updateWithoutIndexActionForCmbInstrumentDetail=0;
int removeActionForCmbInstrumentDetail=0;
int addCommitForCmbInstrumentDetail=0;
int updateCommitForCmbInstrumentDetail=0;
int removeCommitForCmbInstrumentDetail=0;
#endif
void CCmbInstrumentDetailFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDArbiInstrumentIDSingelInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("CmbInstrumentDetail_ExchangeIDArbiInstrumentIDSingelInstrumentIDIndex",pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("CmbInstrumentDetail_ExchangeIDArbiInstrumentIDSingelInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDArbiInstrumentIDSingelInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDArbiInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDArbiInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("CmbInstrumentDetail_ExchangeIDArbiInstrumentIDIndex",pExchangeIDArbiInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("CmbInstrumentDetail_ExchangeIDArbiInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDArbiInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDArbiInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDArbiInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDSingleInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDSingleInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("CmbInstrumentDetail_ExchangeIDSingleInstrumentIDIndex",pExchangeIDSingleInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("CmbInstrumentDetail_ExchangeIDSingleInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDSingleInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDSingleInstrumentIDIndexinCmbInstrumentDetail,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDSingleInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByExchangeIDAndArbiInstrumentID=NULL;
	pLastFoundInSearchAllByExchangeIDAndSingleInstrumentID=NULL;
	pActionTriggers=new vector<CCmbInstrumentDetailActionTrigger *>;
	pCommitTriggers=new vector<CCmbInstrumentDetailCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CCmbInstrumentDetailFactory::CCmbInstrumentDetailFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CCmbInstrumentDetail),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CCmbInstrumentDetailFactory::CCmbInstrumentDetailFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CCmbInstrumentDetail),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CCmbInstrumentDetailFactory::~CCmbInstrumentDetailFactory(void)
{
	if (runLevel>=0) {
		if (pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex!=NULL)
			delete pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDArbiInstrumentIDIndex!=NULL)
			delete pExchangeIDArbiInstrumentIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDSingleInstrumentIDIndex!=NULL)
			delete pExchangeIDSingleInstrumentIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CCmbInstrumentDetailFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CCmbInstrumentDetailFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDSingleInstrumentIDIndex->output(pLogger,indent+1);
	}
}

int CCmbInstrumentDetailFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableCmbInstrumentDetail thisCmbInstrumentDetail;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisCmbInstrumentDetail.readCSV(input,pNames))
		add(&thisCmbInstrumentDetail);
	fclose(input);
	delete pNames;
	return 1;
}

int CCmbInstrumentDetailFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "CmbInstrumentDetail.csv");
	return readCSV(szFileName);
}

int CCmbInstrumentDetailFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableCmbInstrumentDetail *pCmbInstrumentDetail;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableCmbInstrumentDetail::writeCSVHead(output);
	pCmbInstrumentDetail=(CWriteableCmbInstrumentDetail *)(pMem->getFirst());
	while (pCmbInstrumentDetail!=NULL) {
		if (!pCmbInstrumentDetail->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pCmbInstrumentDetail=(CWriteableCmbInstrumentDetail *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CCmbInstrumentDetailFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "CmbInstrumentDetail.csv");
	return writeCSV(szFileName);
}

void CCmbInstrumentDetailFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CCmbInstrumentDetailFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableCmbInstrumentDetail *pCmbInstrumentDetail;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CCmbInstrumentDetailFactory={       Total Count=%d\n", pMem->getCount());
	pCmbInstrumentDetail=(CWriteableCmbInstrumentDetail *)(pMem->getFirst());
	while (pCmbInstrumentDetail!=NULL) {
		pCmbInstrumentDetail->dump(fp,index++);
		pCmbInstrumentDetail=(CWriteableCmbInstrumentDetail *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CCmbInstrumentDetailFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDSingleInstrumentIDIndex->removeAll();
	}
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::internalAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForCmbInstrumentDetail++;
#endif
	CCmbInstrumentDetail *pTarget;	
	beforeAdd(pCmbInstrumentDetail);
	pTarget=(CCmbInstrumentDetail *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough CmbInstrumentDetail in memory database");
		return NULL;
	}
	forceCopy(pTarget, pCmbInstrumentDetail, sizeof(CCmbInstrumentDetail));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDSingleInstrumentIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::add(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction)
{
	pCmbInstrumentDetail->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pCmbInstrumentDetail,true);
	}
	else {
		CCmbInstrumentDetail *pNewCmbInstrumentDetail;
		pNewCmbInstrumentDetail = internalAdd(pCmbInstrumentDetail,false);
		pTransaction->addResource(CCmbInstrumentDetailResource::alloc(CREATE_ACTION,this,pNewCmbInstrumentDetail,NULL));
		return pNewCmbInstrumentDetail;
	}
}

void CCmbInstrumentDetailFactory::internalUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForCmbInstrumentDetail++;
	}
	else {
		updateWithoutIndexActionForCmbInstrumentDetail++;
	}
#endif
	CWriteableCmbInstrumentDetail theOldCmbInstrumentDetail;
	beforeUpdate(pCmbInstrumentDetail,pNewCmbInstrumentDetail);
	if (bNoTransaction) {
		forceCopy(&theOldCmbInstrumentDetail,pCmbInstrumentDetail,sizeof(CCmbInstrumentDetail));
	}
	if (updateIndex) {
	}

	forceCopy(pCmbInstrumentDetail,pNewCmbInstrumentDetail,sizeof(CCmbInstrumentDetail));
	pMem->updateObject(pCmbInstrumentDetail);
	if (updateIndex) {
	}
	afterUpdate(pCmbInstrumentDetail);
	if (bNoTransaction) {
		commitUpdate(pCmbInstrumentDetail,&theOldCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::update(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction, bool updateIndex)
{
	pNewCmbInstrumentDetail->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pCmbInstrumentDetail,pNewCmbInstrumentDetail,updateIndex,true);
	}
	else {
		pTransaction->addResource(CCmbInstrumentDetailResource::alloc(UPDATE_ACTION,this,pCmbInstrumentDetail,pNewCmbInstrumentDetail,updateIndex));
		internalUpdate(pCmbInstrumentDetail,pNewCmbInstrumentDetail,updateIndex,false);
	}
}

void CCmbInstrumentDetailFactory::internalRemove(CCmbInstrumentDetail *pCmbInstrumentDetail, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForCmbInstrumentDetail++;
#endif
	CWriteableCmbInstrumentDetail theOldCmbInstrumentDetail;
	beforeRemove(pCmbInstrumentDetail);
	if (bNoTransaction) {
		forceCopy(&theOldCmbInstrumentDetail,pCmbInstrumentDetail,sizeof(CCmbInstrumentDetail));
	}
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDSingelInstrumentIDIndex->removeObject(pCmbInstrumentDetail);
	}
	if (runLevel>=0) {
		pExchangeIDArbiInstrumentIDIndex->removeObject(pCmbInstrumentDetail);
	}
	if (runLevel>=0) {
		pExchangeIDSingleInstrumentIDIndex->removeObject(pCmbInstrumentDetail);
	}
	pMem->free(pCmbInstrumentDetail);
	if(bNoTransaction) {
		commitRemove(&theOldCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::remove(CCmbInstrumentDetail *pCmbInstrumentDetail, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pCmbInstrumentDetail,true);
	}
	else {
		pTransaction->addResource(CCmbInstrumentDetailResource::alloc(DELETE_ACTION,this,pCmbInstrumentDetail,NULL));
		internalRemove(pCmbInstrumentDetail,false);		
	}
}

CCmbInstrumentDetail* CCmbInstrumentDetailFactory::addOrUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail, CTransaction *pTransaction, bool updateIndex)
{
	if(pCmbInstrumentDetail == NULL) {
		return add(pNewCmbInstrumentDetail,pTransaction);
	}
	else {
		update(pCmbInstrumentDetail,pNewCmbInstrumentDetail,pTransaction,updateIndex);
		return pCmbInstrumentDetail;
	}
}

void CCmbInstrumentDetailFactory::retrieve(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pTargetCmbInstrumentDetail)
{
	forceCopy(pTargetCmbInstrumentDetail, pCmbInstrumentDetail, sizeof(CCmbInstrumentDetail));
}
	
int CCmbInstrumentDetailFactory::addActionTrigger(CCmbInstrumentDetailActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CCmbInstrumentDetailFactory::removeActionTrigger(CCmbInstrumentDetailActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CCmbInstrumentDetailFactory::addCommitTrigger(CCmbInstrumentDetailCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CCmbInstrumentDetailFactory::removeCommitTrigger(CCmbInstrumentDetailCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CCmbInstrumentDetail *CCmbInstrumentDetailFactory::getFirst(void)
{
	CCmbInstrumentDetail *pResult=(CCmbInstrumentDetail *)(pMem->getFirst());
	return pResult;
}
	
CCmbInstrumentDetail *CCmbInstrumentDetailFactory::getNext(void)
{
	CCmbInstrumentDetail *pResult=(CCmbInstrumentDetail *)(pMem->getNext());
	return pResult;
}
	
void CCmbInstrumentDetailFactory::endGet(void)
{
	pMem->endGet();
}

void CCmbInstrumentDetailFactory::beforeAdd(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pCmbInstrumentDetail);
	}
}
	
void CCmbInstrumentDetailFactory::afterAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::beforeUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pNewCmbInstrumentDetail)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pCmbInstrumentDetail,pNewCmbInstrumentDetail);
	}
}
	
void CCmbInstrumentDetailFactory::afterUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pCmbInstrumentDetail);
	}
}
	
void CCmbInstrumentDetailFactory::beforeRemove(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::commitAdd(CCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForCmbInstrumentDetail++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::commitUpdate(CCmbInstrumentDetail *pCmbInstrumentDetail, CWriteableCmbInstrumentDetail *pOldCmbInstrumentDetail)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForCmbInstrumentDetail++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pCmbInstrumentDetail,pOldCmbInstrumentDetail);
	}
}
	
void CCmbInstrumentDetailFactory::commitRemove(CWriteableCmbInstrumentDetail *pCmbInstrumentDetail)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForCmbInstrumentDetail++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pCmbInstrumentDetail);
	}
}

void CCmbInstrumentDetailFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrkIDExIDInvIDHdgFlgIndexinClientTradingID(const void *pV1, const void *pV2);
extern int compareForBrokerIDInvestorIDIndexinClientTradingID(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForClientTradingID=0;
int updateWithIndexActionForClientTradingID=0;
int updateWithoutIndexActionForClientTradingID=0;
int removeActionForClientTradingID=0;
int addCommitForClientTradingID=0;
int updateCommitForClientTradingID=0;
int removeCommitForClientTradingID=0;
#endif
void CClientTradingIDFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrkIDExIDInvIDHdgFlgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDInvIDHdgFlgIndexinClientTradingID,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("ClientTradingID_BrkIDExIDInvIDHdgFlgIndex",pBrkIDExIDInvIDHdgFlgIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("ClientTradingID_BrkIDExIDInvIDHdgFlgIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDInvIDHdgFlgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDInvIDHdgFlgIndexinClientTradingID,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDInvIDHdgFlgIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinClientTradingID,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("ClientTradingID_BrokerIDInvestorIDIndex",pBrokerIDInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("ClientTradingID_BrokerIDInvestorIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinClientTradingID,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		int hashKeySize=1572;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("ClientTradingID.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pBrokerIDExchangeIDPartClientIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("ClientTradingID_BrokerIDExchangeIDPartClientIDHashIndex",pBrokerIDExchangeIDPartClientIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("ClientTradingID_BrokerIDExchangeIDPartClientIDHashIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDExchangeIDPartClientIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDExchangeIDPartClientIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByBrokerIDInvestorID=NULL;
	pLastFoundInSearchAllByBrokerID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CClientTradingIDActionTrigger *>;
	pCommitTriggers=new vector<CClientTradingIDCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CClientTradingIDFactory::CClientTradingIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CClientTradingID),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CClientTradingIDFactory::CClientTradingIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CClientTradingID),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CClientTradingIDFactory::~CClientTradingIDFactory(void)
{
	if (runLevel>=0) {
		if (pBrkIDExIDInvIDHdgFlgIndex!=NULL)
			delete pBrkIDExIDInvIDHdgFlgIndex;
	}
	if (runLevel>=0) {
		if (pBrokerIDInvestorIDIndex!=NULL)
			delete pBrokerIDInvestorIDIndex;
	}
	if (runLevel>=0) {
		if (pBrokerIDExchangeIDPartClientIDHashIndex!=NULL)
			delete pBrokerIDExchangeIDPartClientIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CClientTradingIDFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CClientTradingIDFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrkIDExIDInvIDHdgFlgIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->output(pLogger,indent+1);
	}
}

int CClientTradingIDFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableClientTradingID thisClientTradingID;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisClientTradingID.readCSV(input,pNames))
		add(&thisClientTradingID);
	fclose(input);
	delete pNames;
	return 1;
}

int CClientTradingIDFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "ClientTradingID.csv");
	return readCSV(szFileName);
}

int CClientTradingIDFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableClientTradingID *pClientTradingID;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableClientTradingID::writeCSVHead(output);
	pClientTradingID=(CWriteableClientTradingID *)(pMem->getFirst());
	while (pClientTradingID!=NULL) {
		if (!pClientTradingID->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pClientTradingID=(CWriteableClientTradingID *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CClientTradingIDFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "ClientTradingID.csv");
	return writeCSV(szFileName);
}

void CClientTradingIDFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CClientTradingIDFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableClientTradingID *pClientTradingID;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CClientTradingIDFactory={       Total Count=%d\n", pMem->getCount());
	pClientTradingID=(CWriteableClientTradingID *)(pMem->getFirst());
	while (pClientTradingID!=NULL) {
		pClientTradingID->dump(fp,index++);
		pClientTradingID=(CWriteableClientTradingID *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CClientTradingIDFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrkIDExIDInvIDHdgFlgIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrokerIDExchangeIDPartClientIDHashIndex->removeAll();
	}
}

CClientTradingID *CClientTradingIDFactory::internalAdd(CWriteableClientTradingID *pClientTradingID, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForClientTradingID++;
#endif
	CClientTradingID *pTarget;	
	beforeAdd(pClientTradingID);
	pTarget=(CClientTradingID *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough ClientTradingID in memory database");
		return NULL;
	}
	forceCopy(pTarget, pClientTradingID, sizeof(CClientTradingID));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrkIDExIDInvIDHdgFlgIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrokerIDExchangeIDPartClientIDHashIndex->addObject(pTarget,pTarget->HashBrokerIDExchangeIDPartClientID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CClientTradingID *CClientTradingIDFactory::add(CWriteableClientTradingID *pClientTradingID, CTransaction *pTransaction)
{
	pClientTradingID->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pClientTradingID,true);
	}
	else {
		CClientTradingID *pNewClientTradingID;
		pNewClientTradingID = internalAdd(pClientTradingID,false);
		pTransaction->addResource(CClientTradingIDResource::alloc(CREATE_ACTION,this,pNewClientTradingID,NULL));
		return pNewClientTradingID;
	}
}

void CClientTradingIDFactory::internalUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForClientTradingID++;
	}
	else {
		updateWithoutIndexActionForClientTradingID++;
	}
#endif
	CWriteableClientTradingID theOldClientTradingID;
	beforeUpdate(pClientTradingID,pNewClientTradingID);
	if (bNoTransaction) {
		forceCopy(&theOldClientTradingID,pClientTradingID,sizeof(CClientTradingID));
	}
	if (updateIndex) {
	}

	forceCopy(pClientTradingID,pNewClientTradingID,sizeof(CClientTradingID));
	pMem->updateObject(pClientTradingID);
	if (updateIndex) {
	}
	afterUpdate(pClientTradingID);
	if (bNoTransaction) {
		commitUpdate(pClientTradingID,&theOldClientTradingID);
	}
}

void CClientTradingIDFactory::update(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction, bool updateIndex)
{
	pNewClientTradingID->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pClientTradingID,pNewClientTradingID,updateIndex,true);
	}
	else {
		pTransaction->addResource(CClientTradingIDResource::alloc(UPDATE_ACTION,this,pClientTradingID,pNewClientTradingID,updateIndex));
		internalUpdate(pClientTradingID,pNewClientTradingID,updateIndex,false);
	}
}

void CClientTradingIDFactory::internalRemove(CClientTradingID *pClientTradingID, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForClientTradingID++;
#endif
	CWriteableClientTradingID theOldClientTradingID;
	beforeRemove(pClientTradingID);
	if (bNoTransaction) {
		forceCopy(&theOldClientTradingID,pClientTradingID,sizeof(CClientTradingID));
	}
	if (runLevel>=0) {
		pBrkIDExIDInvIDHdgFlgIndex->removeObject(pClientTradingID);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeObject(pClientTradingID);
	}
	if (runLevel>=0) {
		pBrokerIDExchangeIDPartClientIDHashIndex->removeObject(pClientTradingID,pClientTradingID->HashBrokerIDExchangeIDPartClientID);
	}	
	pMem->free(pClientTradingID);
	if(bNoTransaction) {
		commitRemove(&theOldClientTradingID);
	}
}

void CClientTradingIDFactory::remove(CClientTradingID *pClientTradingID, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pClientTradingID,true);
	}
	else {
		pTransaction->addResource(CClientTradingIDResource::alloc(DELETE_ACTION,this,pClientTradingID,NULL));
		internalRemove(pClientTradingID,false);		
	}
}

CClientTradingID* CClientTradingIDFactory::addOrUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID, CTransaction *pTransaction, bool updateIndex)
{
	if(pClientTradingID == NULL) {
		return add(pNewClientTradingID,pTransaction);
	}
	else {
		update(pClientTradingID,pNewClientTradingID,pTransaction,updateIndex);
		return pClientTradingID;
	}
}

void CClientTradingIDFactory::retrieve(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pTargetClientTradingID)
{
	forceCopy(pTargetClientTradingID, pClientTradingID, sizeof(CClientTradingID));
}
	
int CClientTradingIDFactory::addActionTrigger(CClientTradingIDActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CClientTradingIDFactory::removeActionTrigger(CClientTradingIDActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CClientTradingIDFactory::addCommitTrigger(CClientTradingIDCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CClientTradingIDFactory::removeCommitTrigger(CClientTradingIDCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CClientTradingID *CClientTradingIDFactory::getFirst(void)
{
	CClientTradingID *pResult=(CClientTradingID *)(pMem->getFirst());
	return pResult;
}
	
CClientTradingID *CClientTradingIDFactory::getNext(void)
{
	CClientTradingID *pResult=(CClientTradingID *)(pMem->getNext());
	return pResult;
}
	
void CClientTradingIDFactory::endGet(void)
{
	pMem->endGet();
}

void CClientTradingIDFactory::beforeAdd(CWriteableClientTradingID *pClientTradingID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pClientTradingID);
	}
}
	
void CClientTradingIDFactory::afterAdd(CClientTradingID *pClientTradingID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pClientTradingID);
	}
}

void CClientTradingIDFactory::beforeUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pNewClientTradingID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pClientTradingID,pNewClientTradingID);
	}
}
	
void CClientTradingIDFactory::afterUpdate(CClientTradingID *pClientTradingID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pClientTradingID);
	}
}
	
void CClientTradingIDFactory::beforeRemove(CClientTradingID *pClientTradingID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pClientTradingID);
	}
}

void CClientTradingIDFactory::commitAdd(CClientTradingID *pClientTradingID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForClientTradingID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pClientTradingID);
	}
}

void CClientTradingIDFactory::commitUpdate(CClientTradingID *pClientTradingID, CWriteableClientTradingID *pOldClientTradingID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForClientTradingID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pClientTradingID,pOldClientTradingID);
	}
}
	
void CClientTradingIDFactory::commitRemove(CWriteableClientTradingID *pClientTradingID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForClientTradingID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pClientTradingID);
	}
}

void CClientTradingIDFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void CClientTradingIDFactory::linkAllInvestorAccount(CInvestorAccountFactory *pFactory)
{
	CClientTradingID *pClientTradingID;
	pClientTradingID=getFirst();
	while (pClientTradingID != NULL) {
		pClientTradingID->linkInvestorAccount(pFactory);
		pClientTradingID=getNext();
	}
	endGet();
}

extern int compareForBrokerIDInvestorIDIndexinInvestor(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestor=0;
int updateWithIndexActionForInvestor=0;
int updateWithoutIndexActionForInvestor=0;
int removeActionForInvestor=0;
int addCommitForInvestor=0;
int updateCommitForInvestor=0;
int removeCommitForInvestor=0;
#endif
void CInvestorFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinInvestor,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("Investor_BrokerIDInvestorIDIndex",pBrokerIDInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("Investor_BrokerIDInvestorIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinInvestor,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByInvestorID=NULL;
	pActionTriggers=new vector<CInvestorActionTrigger *>;
	pCommitTriggers=new vector<CInvestorCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorFactory::CInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestor),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorFactory::CInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestor),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorFactory::~CInvestorFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDInvestorIDIndex!=NULL)
			delete pBrokerIDInvestorIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->output(pLogger,indent+1);
	}
}

int CInvestorFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestor thisInvestor;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestor.readCSV(input,pNames))
		add(&thisInvestor);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "Investor.csv");
	return readCSV(szFileName);
}

int CInvestorFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestor *pInvestor;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestor::writeCSVHead(output);
	pInvestor=(CWriteableInvestor *)(pMem->getFirst());
	while (pInvestor!=NULL) {
		if (!pInvestor->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestor=(CWriteableInvestor *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "Investor.csv");
	return writeCSV(szFileName);
}

void CInvestorFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestor *pInvestor;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorFactory={       Total Count=%d\n", pMem->getCount());
	pInvestor=(CWriteableInvestor *)(pMem->getFirst());
	while (pInvestor!=NULL) {
		pInvestor->dump(fp,index++);
		pInvestor=(CWriteableInvestor *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeAll();
	}
}

CInvestor *CInvestorFactory::internalAdd(CWriteableInvestor *pInvestor, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestor++;
#endif
	CInvestor *pTarget;	
	beforeAdd(pInvestor);
	pTarget=(CInvestor *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough Investor in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestor, sizeof(CInvestor));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestor *CInvestorFactory::add(CWriteableInvestor *pInvestor, CTransaction *pTransaction)
{
	pInvestor->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestor,true);
	}
	else {
		CInvestor *pNewInvestor;
		pNewInvestor = internalAdd(pInvestor,false);
		pTransaction->addResource(CInvestorResource::alloc(CREATE_ACTION,this,pNewInvestor,NULL));
		return pNewInvestor;
	}
}

void CInvestorFactory::internalUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestor++;
	}
	else {
		updateWithoutIndexActionForInvestor++;
	}
#endif
	CWriteableInvestor theOldInvestor;
	beforeUpdate(pInvestor,pNewInvestor);
	if (bNoTransaction) {
		forceCopy(&theOldInvestor,pInvestor,sizeof(CInvestor));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestor,pNewInvestor,sizeof(CInvestor));
	pMem->updateObject(pInvestor);
	if (updateIndex) {
	}
	afterUpdate(pInvestor);
	if (bNoTransaction) {
		commitUpdate(pInvestor,&theOldInvestor);
	}
}

void CInvestorFactory::update(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestor->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestor,pNewInvestor,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorResource::alloc(UPDATE_ACTION,this,pInvestor,pNewInvestor,updateIndex));
		internalUpdate(pInvestor,pNewInvestor,updateIndex,false);
	}
}

void CInvestorFactory::internalRemove(CInvestor *pInvestor, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestor++;
#endif
	CWriteableInvestor theOldInvestor;
	beforeRemove(pInvestor);
	if (bNoTransaction) {
		forceCopy(&theOldInvestor,pInvestor,sizeof(CInvestor));
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeObject(pInvestor);
	}
	pMem->free(pInvestor);
	if(bNoTransaction) {
		commitRemove(&theOldInvestor);
	}
}

void CInvestorFactory::remove(CInvestor *pInvestor, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestor,true);
	}
	else {
		pTransaction->addResource(CInvestorResource::alloc(DELETE_ACTION,this,pInvestor,NULL));
		internalRemove(pInvestor,false);		
	}
}

CInvestor* CInvestorFactory::addOrUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestor == NULL) {
		return add(pNewInvestor,pTransaction);
	}
	else {
		update(pInvestor,pNewInvestor,pTransaction,updateIndex);
		return pInvestor;
	}
}

void CInvestorFactory::retrieve(CInvestor *pInvestor, CWriteableInvestor *pTargetInvestor)
{
	forceCopy(pTargetInvestor, pInvestor, sizeof(CInvestor));
}
	
int CInvestorFactory::addActionTrigger(CInvestorActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorFactory::removeActionTrigger(CInvestorActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorFactory::addCommitTrigger(CInvestorCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorFactory::removeCommitTrigger(CInvestorCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestor *CInvestorFactory::getFirst(void)
{
	CInvestor *pResult=(CInvestor *)(pMem->getFirst());
	return pResult;
}
	
CInvestor *CInvestorFactory::getNext(void)
{
	CInvestor *pResult=(CInvestor *)(pMem->getNext());
	return pResult;
}
	
void CInvestorFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorFactory::beforeAdd(CWriteableInvestor *pInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestor);
	}
}
	
void CInvestorFactory::afterAdd(CInvestor *pInvestor)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestor);
	}
}

void CInvestorFactory::beforeUpdate(CInvestor *pInvestor, CWriteableInvestor *pNewInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestor,pNewInvestor);
	}
}
	
void CInvestorFactory::afterUpdate(CInvestor *pInvestor)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestor);
	}
}
	
void CInvestorFactory::beforeRemove(CInvestor *pInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestor);
	}
}

void CInvestorFactory::commitAdd(CInvestor *pInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestor);
	}
}

void CInvestorFactory::commitUpdate(CInvestor *pInvestor, CWriteableInvestor *pOldInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestor,pOldInvestor);
	}
}
	
void CInvestorFactory::commitRemove(CWriteableInvestor *pInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestor);
	}
}

void CInvestorFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDClientIDIndexinInvestorMargin(const void *pV1, const void *pV2);
extern int compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorMargin(const void *pV1, const void *pV2);
extern int compareForBrkIDExIDIstIDVstIDIndexinInvestorMargin(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorMargin=0;
int updateWithIndexActionForInvestorMargin=0;
int updateWithoutIndexActionForInvestorMargin=0;
int removeActionForInvestorMargin=0;
int addCommitForInvestorMargin=0;
int updateCommitForInvestorMargin=0;
int removeCommitForInvestorMargin=0;
#endif
void CInvestorMarginFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDClientIDIndex=new CAVLTree(maxUnit,compareForBrokerIDClientIDIndexinInvestorMargin,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorMargin_BrokerIDClientIDIndex",pBrokerIDClientIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorMargin_BrokerIDClientIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDClientIDIndex=new CAVLTree(maxUnit,compareForBrokerIDClientIDIndexinInvestorMargin,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDClientIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrkIDExIDIstIDVstIDHdgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorMargin,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorMargin_BrkIDExIDIstIDVstIDHdgIndex",pBrkIDExIDIstIDVstIDHdgIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorMargin_BrkIDExIDIstIDVstIDHdgIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDIstIDVstIDHdgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorMargin,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDIstIDVstIDHdgIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrkIDExIDIstIDVstIDIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDIndexinInvestorMargin,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorMargin_BrkIDExIDIstIDVstIDIndex",pBrkIDExIDIstIDVstIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorMargin_BrkIDExIDIstIDVstIDIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDIstIDVstIDIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDIndexinInvestorMargin,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDIstIDVstIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		int hashKeySize=12289;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("InvestorMargin.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pInstrumentAndClientID=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorMargin_InstrumentAndClientID",pInstrumentAndClientID->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorMargin_InstrumentAndClientID");
			if(it != pIndexMap->end()) {
				pInstrumentAndClientID=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pInstrumentAndClientID==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByBrkIDExIDIstIDVstID=NULL;
	pLastFoundInSearchByInstrumentID=NULL;
	pLastFoundInSearchByBrokerID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CInvestorMarginActionTrigger *>;
	pCommitTriggers=new vector<CInvestorMarginCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorMarginFactory::CInvestorMarginFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorMargin),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorMarginFactory::CInvestorMarginFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorMargin),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorMarginFactory::~CInvestorMarginFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDClientIDIndex!=NULL)
			delete pBrokerIDClientIDIndex;
	}
	if (runLevel>=0) {
		if (pBrkIDExIDIstIDVstIDHdgIndex!=NULL)
			delete pBrkIDExIDIstIDVstIDHdgIndex;
	}
	if (runLevel>=0) {
		if (pBrkIDExIDIstIDVstIDIndex!=NULL)
			delete pBrkIDExIDIstIDVstIDIndex;
	}
	if (runLevel>=0) {
		if (pInstrumentAndClientID!=NULL)
			delete pInstrumentAndClientID;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorMarginFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorMarginFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDClientIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDIndex->output(pLogger,indent+1);
	}
}

int CInvestorMarginFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorMargin thisInvestorMargin;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorMargin.readCSV(input,pNames))
		add(&thisInvestorMargin);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorMarginFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorMargin.csv");
	return readCSV(szFileName);
}

int CInvestorMarginFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorMargin *pInvestorMargin;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorMargin::writeCSVHead(output);
	pInvestorMargin=(CWriteableInvestorMargin *)(pMem->getFirst());
	while (pInvestorMargin!=NULL) {
		if (!pInvestorMargin->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorMargin=(CWriteableInvestorMargin *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorMarginFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorMargin.csv");
	return writeCSV(szFileName);
}

void CInvestorMarginFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorMarginFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorMargin *pInvestorMargin;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorMarginFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorMargin=(CWriteableInvestorMargin *)(pMem->getFirst());
	while (pInvestorMargin!=NULL) {
		pInvestorMargin->dump(fp,index++);
		pInvestorMargin=(CWriteableInvestorMargin *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorMarginFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDClientIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pInstrumentAndClientID->removeAll();
	}
}

CInvestorMargin *CInvestorMarginFactory::internalAdd(CWriteableInvestorMargin *pInvestorMargin, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorMargin++;
#endif
	CInvestorMargin *pTarget;	
	beforeAdd(pInvestorMargin);
	pTarget=(CInvestorMargin *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorMargin in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorMargin, sizeof(CInvestorMargin));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDClientIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pInstrumentAndClientID->addObject(pTarget,pTarget->HashInstrumentAndClientID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorMargin *CInvestorMarginFactory::add(CWriteableInvestorMargin *pInvestorMargin, CTransaction *pTransaction)
{
	pInvestorMargin->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorMargin,true);
	}
	else {
		CInvestorMargin *pNewInvestorMargin;
		pNewInvestorMargin = internalAdd(pInvestorMargin,false);
		pTransaction->addResource(CInvestorMarginResource::alloc(CREATE_ACTION,this,pNewInvestorMargin,NULL));
		return pNewInvestorMargin;
	}
}

void CInvestorMarginFactory::internalUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorMargin++;
	}
	else {
		updateWithoutIndexActionForInvestorMargin++;
	}
#endif
	CWriteableInvestorMargin theOldInvestorMargin;
	beforeUpdate(pInvestorMargin,pNewInvestorMargin);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorMargin,pInvestorMargin,sizeof(CInvestorMargin));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorMargin,pNewInvestorMargin,sizeof(CInvestorMargin));
	pMem->updateObject(pInvestorMargin);
	if (updateIndex) {
	}
	afterUpdate(pInvestorMargin);
	if (bNoTransaction) {
		commitUpdate(pInvestorMargin,&theOldInvestorMargin);
	}
}

void CInvestorMarginFactory::update(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorMargin->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorMargin,pNewInvestorMargin,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorMarginResource::alloc(UPDATE_ACTION,this,pInvestorMargin,pNewInvestorMargin,updateIndex));
		internalUpdate(pInvestorMargin,pNewInvestorMargin,updateIndex,false);
	}
}

void CInvestorMarginFactory::internalRemove(CInvestorMargin *pInvestorMargin, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorMargin++;
#endif
	CWriteableInvestorMargin theOldInvestorMargin;
	beforeRemove(pInvestorMargin);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorMargin,pInvestorMargin,sizeof(CInvestorMargin));
	}
	if (runLevel>=0) {
		pBrokerIDClientIDIndex->removeObject(pInvestorMargin);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->removeObject(pInvestorMargin);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDIndex->removeObject(pInvestorMargin);
	}
	if (runLevel>=0) {
		pInstrumentAndClientID->removeObject(pInvestorMargin,pInvestorMargin->HashInstrumentAndClientID);
	}	
	pMem->free(pInvestorMargin);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorMargin);
	}
}

void CInvestorMarginFactory::remove(CInvestorMargin *pInvestorMargin, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorMargin,true);
	}
	else {
		pTransaction->addResource(CInvestorMarginResource::alloc(DELETE_ACTION,this,pInvestorMargin,NULL));
		internalRemove(pInvestorMargin,false);		
	}
}

CInvestorMargin* CInvestorMarginFactory::addOrUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorMargin == NULL) {
		return add(pNewInvestorMargin,pTransaction);
	}
	else {
		update(pInvestorMargin,pNewInvestorMargin,pTransaction,updateIndex);
		return pInvestorMargin;
	}
}

void CInvestorMarginFactory::retrieve(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pTargetInvestorMargin)
{
	forceCopy(pTargetInvestorMargin, pInvestorMargin, sizeof(CInvestorMargin));
}
	
int CInvestorMarginFactory::addActionTrigger(CInvestorMarginActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorMarginFactory::removeActionTrigger(CInvestorMarginActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorMarginFactory::addCommitTrigger(CInvestorMarginCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorMarginFactory::removeCommitTrigger(CInvestorMarginCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorMargin *CInvestorMarginFactory::getFirst(void)
{
	CInvestorMargin *pResult=(CInvestorMargin *)(pMem->getFirst());
	return pResult;
}
	
CInvestorMargin *CInvestorMarginFactory::getNext(void)
{
	CInvestorMargin *pResult=(CInvestorMargin *)(pMem->getNext());
	return pResult;
}
	
void CInvestorMarginFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorMarginFactory::beforeAdd(CWriteableInvestorMargin *pInvestorMargin)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorMargin);
	}
}
	
void CInvestorMarginFactory::afterAdd(CInvestorMargin *pInvestorMargin)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorMargin);
	}
}

void CInvestorMarginFactory::beforeUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pNewInvestorMargin)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorMargin,pNewInvestorMargin);
	}
}
	
void CInvestorMarginFactory::afterUpdate(CInvestorMargin *pInvestorMargin)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorMargin);
	}
}
	
void CInvestorMarginFactory::beforeRemove(CInvestorMargin *pInvestorMargin)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorMargin);
	}
}

void CInvestorMarginFactory::commitAdd(CInvestorMargin *pInvestorMargin)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorMargin++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorMargin);
	}
}

void CInvestorMarginFactory::commitUpdate(CInvestorMargin *pInvestorMargin, CWriteableInvestorMargin *pOldInvestorMargin)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorMargin++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorMargin,pOldInvestorMargin);
	}
}
	
void CInvestorMarginFactory::commitRemove(CWriteableInvestorMargin *pInvestorMargin)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorMargin++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorMargin);
	}
}

void CInvestorMarginFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForInstrumentIDIndexinInvestorFee(const void *pV1, const void *pV2);
extern int compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorFee(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorFee=0;
int updateWithIndexActionForInvestorFee=0;
int updateWithoutIndexActionForInvestorFee=0;
int removeActionForInvestorFee=0;
int addCommitForInvestorFee=0;
int updateCommitForInvestorFee=0;
int removeCommitForInvestorFee=0;
#endif
void CInvestorFeeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pInstrumentIDIndex=new CAVLTree(maxUnit,compareForInstrumentIDIndexinInvestorFee,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorFee_InstrumentIDIndex",pInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorFee_InstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pInstrumentIDIndex=new CAVLTree(maxUnit,compareForInstrumentIDIndexinInvestorFee,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrkIDExIDIstIDVstIDHdgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorFee,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorFee_BrkIDExIDIstIDVstIDHdgIndex",pBrkIDExIDIstIDVstIDHdgIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorFee_BrkIDExIDIstIDVstIDHdgIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDIstIDVstIDHdgIndex=new CAVLTree(maxUnit,compareForBrkIDExIDIstIDVstIDHdgIndexinInvestorFee,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDIstIDVstIDHdgIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByInstrumentID=NULL;
	pLastFoundInSearchByBrokerID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CInvestorFeeActionTrigger *>;
	pCommitTriggers=new vector<CInvestorFeeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorFeeFactory::CInvestorFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorFee),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorFeeFactory::CInvestorFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorFee),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorFeeFactory::~CInvestorFeeFactory(void)
{
	if (runLevel>=0) {
		if (pInstrumentIDIndex!=NULL)
			delete pInstrumentIDIndex;
	}
	if (runLevel>=0) {
		if (pBrkIDExIDIstIDVstIDHdgIndex!=NULL)
			delete pBrkIDExIDIstIDVstIDHdgIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorFeeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorFeeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pInstrumentIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->output(pLogger,indent+1);
	}
}

int CInvestorFeeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorFee thisInvestorFee;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorFee.readCSV(input,pNames))
		add(&thisInvestorFee);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorFeeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorFee.csv");
	return readCSV(szFileName);
}

int CInvestorFeeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorFee *pInvestorFee;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorFee::writeCSVHead(output);
	pInvestorFee=(CWriteableInvestorFee *)(pMem->getFirst());
	while (pInvestorFee!=NULL) {
		if (!pInvestorFee->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorFee=(CWriteableInvestorFee *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorFeeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorFee.csv");
	return writeCSV(szFileName);
}

void CInvestorFeeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorFeeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorFee *pInvestorFee;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorFeeFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorFee=(CWriteableInvestorFee *)(pMem->getFirst());
	while (pInvestorFee!=NULL) {
		pInvestorFee->dump(fp,index++);
		pInvestorFee=(CWriteableInvestorFee *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorFeeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pInstrumentIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->removeAll();
	}
}

CInvestorFee *CInvestorFeeFactory::internalAdd(CWriteableInvestorFee *pInvestorFee, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorFee++;
#endif
	CInvestorFee *pTarget;	
	beforeAdd(pInvestorFee);
	pTarget=(CInvestorFee *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorFee in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorFee, sizeof(CInvestorFee));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pInstrumentIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorFee *CInvestorFeeFactory::add(CWriteableInvestorFee *pInvestorFee, CTransaction *pTransaction)
{
	pInvestorFee->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorFee,true);
	}
	else {
		CInvestorFee *pNewInvestorFee;
		pNewInvestorFee = internalAdd(pInvestorFee,false);
		pTransaction->addResource(CInvestorFeeResource::alloc(CREATE_ACTION,this,pNewInvestorFee,NULL));
		return pNewInvestorFee;
	}
}

void CInvestorFeeFactory::internalUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorFee++;
	}
	else {
		updateWithoutIndexActionForInvestorFee++;
	}
#endif
	CWriteableInvestorFee theOldInvestorFee;
	beforeUpdate(pInvestorFee,pNewInvestorFee);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorFee,pInvestorFee,sizeof(CInvestorFee));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorFee,pNewInvestorFee,sizeof(CInvestorFee));
	pMem->updateObject(pInvestorFee);
	if (updateIndex) {
	}
	afterUpdate(pInvestorFee);
	if (bNoTransaction) {
		commitUpdate(pInvestorFee,&theOldInvestorFee);
	}
}

void CInvestorFeeFactory::update(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorFee->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorFee,pNewInvestorFee,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorFeeResource::alloc(UPDATE_ACTION,this,pInvestorFee,pNewInvestorFee,updateIndex));
		internalUpdate(pInvestorFee,pNewInvestorFee,updateIndex,false);
	}
}

void CInvestorFeeFactory::internalRemove(CInvestorFee *pInvestorFee, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorFee++;
#endif
	CWriteableInvestorFee theOldInvestorFee;
	beforeRemove(pInvestorFee);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorFee,pInvestorFee,sizeof(CInvestorFee));
	}
	if (runLevel>=0) {
		pInstrumentIDIndex->removeObject(pInvestorFee);
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHdgIndex->removeObject(pInvestorFee);
	}
	pMem->free(pInvestorFee);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorFee);
	}
}

void CInvestorFeeFactory::remove(CInvestorFee *pInvestorFee, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorFee,true);
	}
	else {
		pTransaction->addResource(CInvestorFeeResource::alloc(DELETE_ACTION,this,pInvestorFee,NULL));
		internalRemove(pInvestorFee,false);		
	}
}

CInvestorFee* CInvestorFeeFactory::addOrUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorFee == NULL) {
		return add(pNewInvestorFee,pTransaction);
	}
	else {
		update(pInvestorFee,pNewInvestorFee,pTransaction,updateIndex);
		return pInvestorFee;
	}
}

void CInvestorFeeFactory::retrieve(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pTargetInvestorFee)
{
	forceCopy(pTargetInvestorFee, pInvestorFee, sizeof(CInvestorFee));
}
	
int CInvestorFeeFactory::addActionTrigger(CInvestorFeeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorFeeFactory::removeActionTrigger(CInvestorFeeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorFeeFactory::addCommitTrigger(CInvestorFeeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorFeeFactory::removeCommitTrigger(CInvestorFeeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorFee *CInvestorFeeFactory::getFirst(void)
{
	CInvestorFee *pResult=(CInvestorFee *)(pMem->getFirst());
	return pResult;
}
	
CInvestorFee *CInvestorFeeFactory::getNext(void)
{
	CInvestorFee *pResult=(CInvestorFee *)(pMem->getNext());
	return pResult;
}
	
void CInvestorFeeFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorFeeFactory::beforeAdd(CWriteableInvestorFee *pInvestorFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorFee);
	}
}
	
void CInvestorFeeFactory::afterAdd(CInvestorFee *pInvestorFee)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorFee);
	}
}

void CInvestorFeeFactory::beforeUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pNewInvestorFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorFee,pNewInvestorFee);
	}
}
	
void CInvestorFeeFactory::afterUpdate(CInvestorFee *pInvestorFee)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorFee);
	}
}
	
void CInvestorFeeFactory::beforeRemove(CInvestorFee *pInvestorFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorFee);
	}
}

void CInvestorFeeFactory::commitAdd(CInvestorFee *pInvestorFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorFee);
	}
}

void CInvestorFeeFactory::commitUpdate(CInvestorFee *pInvestorFee, CWriteableInvestorFee *pOldInvestorFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorFee,pOldInvestorFee);
	}
}
	
void CInvestorFeeFactory::commitRemove(CWriteableInvestorFee *pInvestorFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorFee);
	}
}

void CInvestorFeeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDUserIDIndexinUser(const void *pV1, const void *pV2);
extern int compareForUserIDIndexinUser(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForUser=0;
int updateWithIndexActionForUser=0;
int updateWithoutIndexActionForUser=0;
int removeActionForUser=0;
int addCommitForUser=0;
int updateCommitForUser=0;
int removeCommitForUser=0;
#endif
void CUserFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDUserIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDIndexinUser,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("User_BrokerIDUserIDIndex",pBrokerIDUserIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("User_BrokerIDUserIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDUserIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDIndexinUser,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDUserIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pUserIDIndex=new CAVLTree(maxUnit,compareForUserIDIndexinUser,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("User_UserIDIndex",pUserIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("User_UserIDIndex");
			if(it != pIndexMap->end()) {
				pUserIDIndex=new CAVLTree(maxUnit,compareForUserIDIndexinUser,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pUserIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchStartByUserID=NULL;
	pActionTriggers=new vector<CUserActionTrigger *>;
	pCommitTriggers=new vector<CUserCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CUserFactory::CUserFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUser),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CUserFactory::CUserFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUser),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CUserFactory::~CUserFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDUserIDIndex!=NULL)
			delete pBrokerIDUserIDIndex;
	}
	if (runLevel>=0) {
		if (pUserIDIndex!=NULL)
			delete pUserIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CUserFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDUserIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pUserIDIndex->output(pLogger,indent+1);
	}
}

int CUserFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableUser thisUser;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisUser.readCSV(input,pNames))
		add(&thisUser);
	fclose(input);
	delete pNames;
	return 1;
}

int CUserFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "User.csv");
	return readCSV(szFileName);
}

int CUserFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableUser *pUser;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableUser::writeCSVHead(output);
	pUser=(CWriteableUser *)(pMem->getFirst());
	while (pUser!=NULL) {
		if (!pUser->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pUser=(CWriteableUser *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CUserFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "User.csv");
	return writeCSV(szFileName);
}

void CUserFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CUserFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableUser *pUser;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CUserFactory={       Total Count=%d\n", pMem->getCount());
	pUser=(CWriteableUser *)(pMem->getFirst());
	while (pUser!=NULL) {
		pUser->dump(fp,index++);
		pUser=(CWriteableUser *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CUserFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDUserIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pUserIDIndex->removeAll();
	}
}

CUser *CUserFactory::internalAdd(CWriteableUser *pUser, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForUser++;
#endif
	CUser *pTarget;	
	beforeAdd(pUser);
	pTarget=(CUser *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough User in memory database");
		return NULL;
	}
	forceCopy(pTarget, pUser, sizeof(CUser));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDUserIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pUserIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CUser *CUserFactory::add(CWriteableUser *pUser, CTransaction *pTransaction)
{
	pUser->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pUser,true);
	}
	else {
		CUser *pNewUser;
		pNewUser = internalAdd(pUser,false);
		pTransaction->addResource(CUserResource::alloc(CREATE_ACTION,this,pNewUser,NULL));
		return pNewUser;
	}
}

void CUserFactory::internalUpdate(CUser *pUser, CWriteableUser *pNewUser, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForUser++;
	}
	else {
		updateWithoutIndexActionForUser++;
	}
#endif
	CWriteableUser theOldUser;
	beforeUpdate(pUser,pNewUser);
	if (bNoTransaction) {
		forceCopy(&theOldUser,pUser,sizeof(CUser));
	}
	if (updateIndex) {
	}

	forceCopy(pUser,pNewUser,sizeof(CUser));
	pMem->updateObject(pUser);
	if (updateIndex) {
	}
	afterUpdate(pUser);
	if (bNoTransaction) {
		commitUpdate(pUser,&theOldUser);
	}
}

void CUserFactory::update(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction, bool updateIndex)
{
	pNewUser->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pUser,pNewUser,updateIndex,true);
	}
	else {
		pTransaction->addResource(CUserResource::alloc(UPDATE_ACTION,this,pUser,pNewUser,updateIndex));
		internalUpdate(pUser,pNewUser,updateIndex,false);
	}
}

void CUserFactory::internalRemove(CUser *pUser, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForUser++;
#endif
	CWriteableUser theOldUser;
	beforeRemove(pUser);
	if (bNoTransaction) {
		forceCopy(&theOldUser,pUser,sizeof(CUser));
	}
	if (runLevel>=0) {
		pBrokerIDUserIDIndex->removeObject(pUser);
	}
	if (runLevel>=0) {
		pUserIDIndex->removeObject(pUser);
	}
	pMem->free(pUser);
	if(bNoTransaction) {
		commitRemove(&theOldUser);
	}
}

void CUserFactory::remove(CUser *pUser, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pUser,true);
	}
	else {
		pTransaction->addResource(CUserResource::alloc(DELETE_ACTION,this,pUser,NULL));
		internalRemove(pUser,false);		
	}
}

CUser* CUserFactory::addOrUpdate(CUser *pUser, CWriteableUser *pNewUser, CTransaction *pTransaction, bool updateIndex)
{
	if(pUser == NULL) {
		return add(pNewUser,pTransaction);
	}
	else {
		update(pUser,pNewUser,pTransaction,updateIndex);
		return pUser;
	}
}

void CUserFactory::retrieve(CUser *pUser, CWriteableUser *pTargetUser)
{
	forceCopy(pTargetUser, pUser, sizeof(CUser));
}
	
int CUserFactory::addActionTrigger(CUserActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CUserFactory::removeActionTrigger(CUserActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CUserFactory::addCommitTrigger(CUserCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CUserFactory::removeCommitTrigger(CUserCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CUser *CUserFactory::getFirst(void)
{
	CUser *pResult=(CUser *)(pMem->getFirst());
	return pResult;
}
	
CUser *CUserFactory::getNext(void)
{
	CUser *pResult=(CUser *)(pMem->getNext());
	return pResult;
}
	
void CUserFactory::endGet(void)
{
	pMem->endGet();
}

void CUserFactory::beforeAdd(CWriteableUser *pUser)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pUser);
	}
}
	
void CUserFactory::afterAdd(CUser *pUser)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pUser);
	}
}

void CUserFactory::beforeUpdate(CUser *pUser, CWriteableUser *pNewUser)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pUser,pNewUser);
	}
}
	
void CUserFactory::afterUpdate(CUser *pUser)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pUser);
	}
}
	
void CUserFactory::beforeRemove(CUser *pUser)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pUser);
	}
}

void CUserFactory::commitAdd(CUser *pUser)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForUser++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pUser);
	}
}

void CUserFactory::commitUpdate(CUser *pUser, CWriteableUser *pOldUser)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForUser++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pUser,pOldUser);
	}
}
	
void CUserFactory::commitRemove(CWriteableUser *pUser)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForUser++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pUser);
	}
}

void CUserFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrokerIDUserIDInvestorIDIndexinUserInvestor(const void *pV1, const void *pV2);
extern int compareForBrokerIDInvestorIDIndexinUserInvestor(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForUserInvestor=0;
int updateWithIndexActionForUserInvestor=0;
int updateWithoutIndexActionForUserInvestor=0;
int removeActionForUserInvestor=0;
int addCommitForUserInvestor=0;
int updateCommitForUserInvestor=0;
int removeCommitForUserInvestor=0;
#endif
void CUserInvestorFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDUserIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDInvestorIDIndexinUserInvestor,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserInvestor_BrokerIDUserIDInvestorIDIndex",pBrokerIDUserIDInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserInvestor_BrokerIDUserIDInvestorIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDUserIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDInvestorIDIndexinUserInvestor,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDUserIDInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinUserInvestor,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserInvestor_BrokerIDInvestorIDIndex",pBrokerIDInvestorIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserInvestor_BrokerIDInvestorIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDInvestorIDIndex=new CAVLTree(maxUnit,compareForBrokerIDInvestorIDIndexinUserInvestor,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDInvestorIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByBrokerIDInvestorID=NULL;
	pLastFoundInSearchAllByUserID=NULL;
	pLastFoundInSearchAllByBrokerIDUserID=NULL;
	pLastFoundInSearchAllByBrokerID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CUserInvestorActionTrigger *>;
	pCommitTriggers=new vector<CUserInvestorCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CUserInvestorFactory::CUserInvestorFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserInvestor),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CUserInvestorFactory::CUserInvestorFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserInvestor),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CUserInvestorFactory::~CUserInvestorFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDUserIDInvestorIDIndex!=NULL)
			delete pBrokerIDUserIDInvestorIDIndex;
	}
	if (runLevel>=0) {
		if (pBrokerIDInvestorIDIndex!=NULL)
			delete pBrokerIDInvestorIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CUserInvestorFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserInvestorFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrokerIDUserIDInvestorIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->output(pLogger,indent+1);
	}
}

int CUserInvestorFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableUserInvestor thisUserInvestor;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisUserInvestor.readCSV(input,pNames))
		add(&thisUserInvestor);
	fclose(input);
	delete pNames;
	return 1;
}

int CUserInvestorFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "UserInvestor.csv");
	return readCSV(szFileName);
}

int CUserInvestorFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableUserInvestor *pUserInvestor;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableUserInvestor::writeCSVHead(output);
	pUserInvestor=(CWriteableUserInvestor *)(pMem->getFirst());
	while (pUserInvestor!=NULL) {
		if (!pUserInvestor->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pUserInvestor=(CWriteableUserInvestor *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CUserInvestorFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserInvestor.csv");
	return writeCSV(szFileName);
}

void CUserInvestorFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CUserInvestorFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableUserInvestor *pUserInvestor;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CUserInvestorFactory={       Total Count=%d\n", pMem->getCount());
	pUserInvestor=(CWriteableUserInvestor *)(pMem->getFirst());
	while (pUserInvestor!=NULL) {
		pUserInvestor->dump(fp,index++);
		pUserInvestor=(CWriteableUserInvestor *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CUserInvestorFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDUserIDInvestorIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeAll();
	}
}

CUserInvestor *CUserInvestorFactory::internalAdd(CWriteableUserInvestor *pUserInvestor, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForUserInvestor++;
#endif
	CUserInvestor *pTarget;	
	beforeAdd(pUserInvestor);
	pTarget=(CUserInvestor *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough UserInvestor in memory database");
		return NULL;
	}
	forceCopy(pTarget, pUserInvestor, sizeof(CUserInvestor));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDUserIDInvestorIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CUserInvestor *CUserInvestorFactory::add(CWriteableUserInvestor *pUserInvestor, CTransaction *pTransaction)
{
	pUserInvestor->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pUserInvestor,true);
	}
	else {
		CUserInvestor *pNewUserInvestor;
		pNewUserInvestor = internalAdd(pUserInvestor,false);
		pTransaction->addResource(CUserInvestorResource::alloc(CREATE_ACTION,this,pNewUserInvestor,NULL));
		return pNewUserInvestor;
	}
}

void CUserInvestorFactory::internalUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForUserInvestor++;
	}
	else {
		updateWithoutIndexActionForUserInvestor++;
	}
#endif
	CWriteableUserInvestor theOldUserInvestor;
	beforeUpdate(pUserInvestor,pNewUserInvestor);
	if (bNoTransaction) {
		forceCopy(&theOldUserInvestor,pUserInvestor,sizeof(CUserInvestor));
	}
	if (updateIndex) {
	}

	forceCopy(pUserInvestor,pNewUserInvestor,sizeof(CUserInvestor));
	pMem->updateObject(pUserInvestor);
	if (updateIndex) {
	}
	afterUpdate(pUserInvestor);
	if (bNoTransaction) {
		commitUpdate(pUserInvestor,&theOldUserInvestor);
	}
}

void CUserInvestorFactory::update(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction, bool updateIndex)
{
	pNewUserInvestor->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pUserInvestor,pNewUserInvestor,updateIndex,true);
	}
	else {
		pTransaction->addResource(CUserInvestorResource::alloc(UPDATE_ACTION,this,pUserInvestor,pNewUserInvestor,updateIndex));
		internalUpdate(pUserInvestor,pNewUserInvestor,updateIndex,false);
	}
}

void CUserInvestorFactory::internalRemove(CUserInvestor *pUserInvestor, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForUserInvestor++;
#endif
	CWriteableUserInvestor theOldUserInvestor;
	beforeRemove(pUserInvestor);
	if (bNoTransaction) {
		forceCopy(&theOldUserInvestor,pUserInvestor,sizeof(CUserInvestor));
	}
	if (runLevel>=0) {
		pBrokerIDUserIDInvestorIDIndex->removeObject(pUserInvestor);
	}
	if (runLevel>=0) {
		pBrokerIDInvestorIDIndex->removeObject(pUserInvestor);
	}
	pMem->free(pUserInvestor);
	if(bNoTransaction) {
		commitRemove(&theOldUserInvestor);
	}
}

void CUserInvestorFactory::remove(CUserInvestor *pUserInvestor, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pUserInvestor,true);
	}
	else {
		pTransaction->addResource(CUserInvestorResource::alloc(DELETE_ACTION,this,pUserInvestor,NULL));
		internalRemove(pUserInvestor,false);		
	}
}

CUserInvestor* CUserInvestorFactory::addOrUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor, CTransaction *pTransaction, bool updateIndex)
{
	if(pUserInvestor == NULL) {
		return add(pNewUserInvestor,pTransaction);
	}
	else {
		update(pUserInvestor,pNewUserInvestor,pTransaction,updateIndex);
		return pUserInvestor;
	}
}

void CUserInvestorFactory::retrieve(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pTargetUserInvestor)
{
	forceCopy(pTargetUserInvestor, pUserInvestor, sizeof(CUserInvestor));
}
	
int CUserInvestorFactory::addActionTrigger(CUserInvestorActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CUserInvestorFactory::removeActionTrigger(CUserInvestorActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CUserInvestorFactory::addCommitTrigger(CUserInvestorCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CUserInvestorFactory::removeCommitTrigger(CUserInvestorCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CUserInvestor *CUserInvestorFactory::getFirst(void)
{
	CUserInvestor *pResult=(CUserInvestor *)(pMem->getFirst());
	return pResult;
}
	
CUserInvestor *CUserInvestorFactory::getNext(void)
{
	CUserInvestor *pResult=(CUserInvestor *)(pMem->getNext());
	return pResult;
}
	
void CUserInvestorFactory::endGet(void)
{
	pMem->endGet();
}

void CUserInvestorFactory::beforeAdd(CWriteableUserInvestor *pUserInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pUserInvestor);
	}
}
	
void CUserInvestorFactory::afterAdd(CUserInvestor *pUserInvestor)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pUserInvestor);
	}
}

void CUserInvestorFactory::beforeUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pNewUserInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pUserInvestor,pNewUserInvestor);
	}
}
	
void CUserInvestorFactory::afterUpdate(CUserInvestor *pUserInvestor)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pUserInvestor);
	}
}
	
void CUserInvestorFactory::beforeRemove(CUserInvestor *pUserInvestor)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pUserInvestor);
	}
}

void CUserInvestorFactory::commitAdd(CUserInvestor *pUserInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForUserInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pUserInvestor);
	}
}

void CUserInvestorFactory::commitUpdate(CUserInvestor *pUserInvestor, CWriteableUserInvestor *pOldUserInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForUserInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pUserInvestor,pOldUserInvestor);
	}
}
	
void CUserInvestorFactory::commitRemove(CWriteableUserInvestor *pUserInvestor)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForUserInvestor++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pUserInvestor);
	}
}

void CUserInvestorFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForOrderUserIDIndexinOrderInsertFailed(const void *pV1, const void *pV2);
extern int compareForOrderLocalIDIndexinOrderInsertFailed(const void *pV1, const void *pV2);
extern int compareForExchangeIDOrderSysIDIndexinOrderInsertFailed(const void *pV1, const void *pV2);
extern int compareForExchangeIDSeatIDOrderLocalIDIndexinOrderInsertFailed(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForOrderInsertFailed=0;
int updateWithIndexActionForOrderInsertFailed=0;
int updateWithoutIndexActionForOrderInsertFailed=0;
int removeActionForOrderInsertFailed=0;
int addCommitForOrderInsertFailed=0;
int updateCommitForOrderInsertFailed=0;
int removeCommitForOrderInsertFailed=0;
#endif
void COrderInsertFailedFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pOrderUserIDIndex=new CAVLTree(maxUnit,compareForOrderUserIDIndexinOrderInsertFailed,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("OrderInsertFailed_OrderUserIDIndex",pOrderUserIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("OrderInsertFailed_OrderUserIDIndex");
			if(it != pIndexMap->end()) {
				pOrderUserIDIndex=new CAVLTree(maxUnit,compareForOrderUserIDIndexinOrderInsertFailed,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pOrderUserIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pOrderLocalIDIndex=new CAVLTree(maxUnit,compareForOrderLocalIDIndexinOrderInsertFailed,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("OrderInsertFailed_OrderLocalIDIndex",pOrderLocalIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("OrderInsertFailed_OrderLocalIDIndex");
			if(it != pIndexMap->end()) {
				pOrderLocalIDIndex=new CAVLTree(maxUnit,compareForOrderLocalIDIndexinOrderInsertFailed,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pOrderLocalIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDOrderSysIDIndex=new CAVLTree(maxUnit,compareForExchangeIDOrderSysIDIndexinOrderInsertFailed,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("OrderInsertFailed_ExchangeIDOrderSysIDIndex",pExchangeIDOrderSysIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("OrderInsertFailed_ExchangeIDOrderSysIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDOrderSysIDIndex=new CAVLTree(maxUnit,compareForExchangeIDOrderSysIDIndexinOrderInsertFailed,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDOrderSysIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDSeatIDOrderLocalIDIndex=new CAVLTree(maxUnit,compareForExchangeIDSeatIDOrderLocalIDIndexinOrderInsertFailed,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("OrderInsertFailed_ExchangeIDSeatIDOrderLocalIDIndex",pExchangeIDSeatIDOrderLocalIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("OrderInsertFailed_ExchangeIDSeatIDOrderLocalIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDSeatIDOrderLocalIDIndex=new CAVLTree(maxUnit,compareForExchangeIDSeatIDOrderLocalIDIndexinOrderInsertFailed,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDSeatIDOrderLocalIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByExchIDInvIDUserID=NULL;
	pLastFoundInSearchAllByExchIDInstruIDUserID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<COrderInsertFailedActionTrigger *>;
	pCommitTriggers=new vector<COrderInsertFailedCommitTrigger *>;
	m_activeCommitTrigger=true;
}

COrderInsertFailedFactory::COrderInsertFailedFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderInsertFailed),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

COrderInsertFailedFactory::COrderInsertFailedFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderInsertFailed),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

COrderInsertFailedFactory::~COrderInsertFailedFactory(void)
{
	if (runLevel>=0) {
		if (pOrderUserIDIndex!=NULL)
			delete pOrderUserIDIndex;
	}
	if (runLevel>=0) {
		if (pOrderLocalIDIndex!=NULL)
			delete pOrderLocalIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDOrderSysIDIndex!=NULL)
			delete pExchangeIDOrderSysIDIndex;
	}
	if (runLevel>=0) {
		if (pExchangeIDSeatIDOrderLocalIDIndex!=NULL)
			delete pExchangeIDSeatIDOrderLocalIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void COrderInsertFailedFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderInsertFailedFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pOrderUserIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pOrderLocalIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDOrderSysIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pExchangeIDSeatIDOrderLocalIDIndex->output(pLogger,indent+1);
	}
}

int COrderInsertFailedFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableOrderInsertFailed thisOrderInsertFailed;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisOrderInsertFailed.readCSV(input,pNames))
		add(&thisOrderInsertFailed);
	fclose(input);
	delete pNames;
	return 1;
}

int COrderInsertFailedFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "OrderInsertFailed.csv");
	return readCSV(szFileName);
}

int COrderInsertFailedFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableOrderInsertFailed *pOrderInsertFailed;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableOrderInsertFailed::writeCSVHead(output);
	pOrderInsertFailed=(CWriteableOrderInsertFailed *)(pMem->getFirst());
	while (pOrderInsertFailed!=NULL) {
		if (!pOrderInsertFailed->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pOrderInsertFailed=(CWriteableOrderInsertFailed *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int COrderInsertFailedFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderInsertFailed.csv");
	return writeCSV(szFileName);
}

void COrderInsertFailedFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void COrderInsertFailedFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableOrderInsertFailed *pOrderInsertFailed;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"COrderInsertFailedFactory={       Total Count=%d\n", pMem->getCount());
	pOrderInsertFailed=(CWriteableOrderInsertFailed *)(pMem->getFirst());
	while (pOrderInsertFailed!=NULL) {
		pOrderInsertFailed->dump(fp,index++);
		pOrderInsertFailed=(CWriteableOrderInsertFailed *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void COrderInsertFailedFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pOrderUserIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pOrderLocalIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDOrderSysIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pExchangeIDSeatIDOrderLocalIDIndex->removeAll();
	}
}

COrderInsertFailed *COrderInsertFailedFactory::internalAdd(CWriteableOrderInsertFailed *pOrderInsertFailed, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForOrderInsertFailed++;
#endif
	COrderInsertFailed *pTarget;	
	beforeAdd(pOrderInsertFailed);
	pTarget=(COrderInsertFailed *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough OrderInsertFailed in memory database");
		return NULL;
	}
	forceCopy(pTarget, pOrderInsertFailed, sizeof(COrderInsertFailed));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pOrderUserIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pOrderLocalIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDOrderSysIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pExchangeIDSeatIDOrderLocalIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

COrderInsertFailed *COrderInsertFailedFactory::add(CWriteableOrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction)
{
	pOrderInsertFailed->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pOrderInsertFailed,true);
	}
	else {
		COrderInsertFailed *pNewOrderInsertFailed;
		pNewOrderInsertFailed = internalAdd(pOrderInsertFailed,false);
		pTransaction->addResource(COrderInsertFailedResource::alloc(CREATE_ACTION,this,pNewOrderInsertFailed,NULL));
		return pNewOrderInsertFailed;
	}
}

void COrderInsertFailedFactory::internalUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForOrderInsertFailed++;
	}
	else {
		updateWithoutIndexActionForOrderInsertFailed++;
	}
#endif
	CWriteableOrderInsertFailed theOldOrderInsertFailed;
	beforeUpdate(pOrderInsertFailed,pNewOrderInsertFailed);
	if (bNoTransaction) {
		forceCopy(&theOldOrderInsertFailed,pOrderInsertFailed,sizeof(COrderInsertFailed));
	}
	if (updateIndex) {
	}

	forceCopy(pOrderInsertFailed,pNewOrderInsertFailed,sizeof(COrderInsertFailed));
	pMem->updateObject(pOrderInsertFailed);
	if (updateIndex) {
	}
	afterUpdate(pOrderInsertFailed);
	if (bNoTransaction) {
		commitUpdate(pOrderInsertFailed,&theOldOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::update(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction, bool updateIndex)
{
	pNewOrderInsertFailed->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pOrderInsertFailed,pNewOrderInsertFailed,updateIndex,true);
	}
	else {
		pTransaction->addResource(COrderInsertFailedResource::alloc(UPDATE_ACTION,this,pOrderInsertFailed,pNewOrderInsertFailed,updateIndex));
		internalUpdate(pOrderInsertFailed,pNewOrderInsertFailed,updateIndex,false);
	}
}

void COrderInsertFailedFactory::internalRemove(COrderInsertFailed *pOrderInsertFailed, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForOrderInsertFailed++;
#endif
	CWriteableOrderInsertFailed theOldOrderInsertFailed;
	beforeRemove(pOrderInsertFailed);
	if (bNoTransaction) {
		forceCopy(&theOldOrderInsertFailed,pOrderInsertFailed,sizeof(COrderInsertFailed));
	}
	if (runLevel>=0) {
		pOrderUserIDIndex->removeObject(pOrderInsertFailed);
	}
	if (runLevel>=0) {
		pOrderLocalIDIndex->removeObject(pOrderInsertFailed);
	}
	if (runLevel>=0) {
		pExchangeIDOrderSysIDIndex->removeObject(pOrderInsertFailed);
	}
	if (runLevel>=0) {
		pExchangeIDSeatIDOrderLocalIDIndex->removeObject(pOrderInsertFailed);
	}
	pMem->free(pOrderInsertFailed);
	if(bNoTransaction) {
		commitRemove(&theOldOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::remove(COrderInsertFailed *pOrderInsertFailed, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pOrderInsertFailed,true);
	}
	else {
		pTransaction->addResource(COrderInsertFailedResource::alloc(DELETE_ACTION,this,pOrderInsertFailed,NULL));
		internalRemove(pOrderInsertFailed,false);		
	}
}

COrderInsertFailed* COrderInsertFailedFactory::addOrUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed, CTransaction *pTransaction, bool updateIndex)
{
	if(pOrderInsertFailed == NULL) {
		return add(pNewOrderInsertFailed,pTransaction);
	}
	else {
		update(pOrderInsertFailed,pNewOrderInsertFailed,pTransaction,updateIndex);
		return pOrderInsertFailed;
	}
}

void COrderInsertFailedFactory::retrieve(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pTargetOrderInsertFailed)
{
	forceCopy(pTargetOrderInsertFailed, pOrderInsertFailed, sizeof(COrderInsertFailed));
}
	
int COrderInsertFailedFactory::addActionTrigger(COrderInsertFailedActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int COrderInsertFailedFactory::removeActionTrigger(COrderInsertFailedActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int COrderInsertFailedFactory::addCommitTrigger(COrderInsertFailedCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int COrderInsertFailedFactory::removeCommitTrigger(COrderInsertFailedCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

COrderInsertFailed *COrderInsertFailedFactory::getFirst(void)
{
	COrderInsertFailed *pResult=(COrderInsertFailed *)(pMem->getFirst());
	return pResult;
}
	
COrderInsertFailed *COrderInsertFailedFactory::getNext(void)
{
	COrderInsertFailed *pResult=(COrderInsertFailed *)(pMem->getNext());
	return pResult;
}
	
void COrderInsertFailedFactory::endGet(void)
{
	pMem->endGet();
}

void COrderInsertFailedFactory::beforeAdd(CWriteableOrderInsertFailed *pOrderInsertFailed)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pOrderInsertFailed);
	}
}
	
void COrderInsertFailedFactory::afterAdd(COrderInsertFailed *pOrderInsertFailed)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::beforeUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pNewOrderInsertFailed)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pOrderInsertFailed,pNewOrderInsertFailed);
	}
}
	
void COrderInsertFailedFactory::afterUpdate(COrderInsertFailed *pOrderInsertFailed)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pOrderInsertFailed);
	}
}
	
void COrderInsertFailedFactory::beforeRemove(COrderInsertFailed *pOrderInsertFailed)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::commitAdd(COrderInsertFailed *pOrderInsertFailed)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForOrderInsertFailed++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::commitUpdate(COrderInsertFailed *pOrderInsertFailed, CWriteableOrderInsertFailed *pOldOrderInsertFailed)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForOrderInsertFailed++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pOrderInsertFailed,pOldOrderInsertFailed);
	}
}
	
void COrderInsertFailedFactory::commitRemove(CWriteableOrderInsertFailed *pOrderInsertFailed)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForOrderInsertFailed++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pOrderInsertFailed);
	}
}

void COrderInsertFailedFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void COrderInsertFailedFactory::linkAllInvestorAccount(CInvestorAccountFactory *pFactory)
{
	COrderInsertFailed *pOrderInsertFailed;
	pOrderInsertFailed=getFirst();
	while (pOrderInsertFailed != NULL) {
		pOrderInsertFailed->linkInvestorAccount(pFactory);
		pOrderInsertFailed=getNext();
	}
	endGet();
}

void COrderInsertFailedFactory::linkAllInvestorPosition(CInvestorPositionFactory *pFactory)
{
	COrderInsertFailed *pOrderInsertFailed;
	pOrderInsertFailed=getFirst();
	while (pOrderInsertFailed != NULL) {
		pOrderInsertFailed->linkInvestorPosition(pFactory);
		pOrderInsertFailed=getNext();
	}
	endGet();
}

void COrderInsertFailedFactory::linkAllInstrument(CInstrumentFactory *pFactory)
{
	COrderInsertFailed *pOrderInsertFailed;
	pOrderInsertFailed=getFirst();
	while (pOrderInsertFailed != NULL) {
		pOrderInsertFailed->linkInstrument(pFactory);
		pOrderInsertFailed=getNext();
	}
	endGet();
}

void COrderInsertFailedFactory::linkAllInvestorMargin(CInvestorMarginFactory *pFactory)
{
	COrderInsertFailed *pOrderInsertFailed;
	pOrderInsertFailed=getFirst();
	while (pOrderInsertFailed != NULL) {
		pOrderInsertFailed->linkInvestorMargin(pFactory);
		pOrderInsertFailed=getNext();
	}
	endGet();
}

void COrderInsertFailedFactory::linkAllInvestorFee(CInvestorFeeFactory *pFactory)
{
	COrderInsertFailed *pOrderInsertFailed;
	pOrderInsertFailed=getFirst();
	while (pOrderInsertFailed != NULL) {
		pOrderInsertFailed->linkInvestorFee(pFactory);
		pOrderInsertFailed=getNext();
	}
	endGet();
}

extern int compareForBrkExIDInsUserInvIndexinUserTradingRight(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForUserTradingRight=0;
int updateWithIndexActionForUserTradingRight=0;
int updateWithoutIndexActionForUserTradingRight=0;
int removeActionForUserTradingRight=0;
int addCommitForUserTradingRight=0;
int updateCommitForUserTradingRight=0;
int removeCommitForUserTradingRight=0;
#endif
void CUserTradingRightFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrkExIDInsUserInvIndex=new CAVLTree(maxUnit,compareForBrkExIDInsUserInvIndexinUserTradingRight,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserTradingRight_BrkExIDInsUserInvIndex",pBrkExIDInsUserInvIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserTradingRight_BrkExIDInsUserInvIndex");
			if(it != pIndexMap->end()) {
				pBrkExIDInsUserInvIndex=new CAVLTree(maxUnit,compareForBrkExIDInsUserInvIndexinUserTradingRight,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkExIDInsUserInvIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CUserTradingRightActionTrigger *>;
	pCommitTriggers=new vector<CUserTradingRightCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CUserTradingRightFactory::CUserTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserTradingRight),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CUserTradingRightFactory::CUserTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserTradingRight),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CUserTradingRightFactory::~CUserTradingRightFactory(void)
{
	if (runLevel>=0) {
		if (pBrkExIDInsUserInvIndex!=NULL)
			delete pBrkExIDInsUserInvIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CUserTradingRightFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserTradingRightFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrkExIDInsUserInvIndex->output(pLogger,indent+1);
	}
}

int CUserTradingRightFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableUserTradingRight thisUserTradingRight;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisUserTradingRight.readCSV(input,pNames))
		add(&thisUserTradingRight);
	fclose(input);
	delete pNames;
	return 1;
}

int CUserTradingRightFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "UserTradingRight.csv");
	return readCSV(szFileName);
}

int CUserTradingRightFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableUserTradingRight *pUserTradingRight;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableUserTradingRight::writeCSVHead(output);
	pUserTradingRight=(CWriteableUserTradingRight *)(pMem->getFirst());
	while (pUserTradingRight!=NULL) {
		if (!pUserTradingRight->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pUserTradingRight=(CWriteableUserTradingRight *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CUserTradingRightFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserTradingRight.csv");
	return writeCSV(szFileName);
}

void CUserTradingRightFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CUserTradingRightFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableUserTradingRight *pUserTradingRight;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CUserTradingRightFactory={       Total Count=%d\n", pMem->getCount());
	pUserTradingRight=(CWriteableUserTradingRight *)(pMem->getFirst());
	while (pUserTradingRight!=NULL) {
		pUserTradingRight->dump(fp,index++);
		pUserTradingRight=(CWriteableUserTradingRight *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CUserTradingRightFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrkExIDInsUserInvIndex->removeAll();
	}
}

CUserTradingRight *CUserTradingRightFactory::internalAdd(CWriteableUserTradingRight *pUserTradingRight, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForUserTradingRight++;
#endif
	CUserTradingRight *pTarget;	
	beforeAdd(pUserTradingRight);
	pTarget=(CUserTradingRight *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough UserTradingRight in memory database");
		return NULL;
	}
	forceCopy(pTarget, pUserTradingRight, sizeof(CUserTradingRight));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrkExIDInsUserInvIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CUserTradingRight *CUserTradingRightFactory::add(CWriteableUserTradingRight *pUserTradingRight, CTransaction *pTransaction)
{
	pUserTradingRight->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pUserTradingRight,true);
	}
	else {
		CUserTradingRight *pNewUserTradingRight;
		pNewUserTradingRight = internalAdd(pUserTradingRight,false);
		pTransaction->addResource(CUserTradingRightResource::alloc(CREATE_ACTION,this,pNewUserTradingRight,NULL));
		return pNewUserTradingRight;
	}
}

void CUserTradingRightFactory::internalUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForUserTradingRight++;
	}
	else {
		updateWithoutIndexActionForUserTradingRight++;
	}
#endif
	CWriteableUserTradingRight theOldUserTradingRight;
	beforeUpdate(pUserTradingRight,pNewUserTradingRight);
	if (bNoTransaction) {
		forceCopy(&theOldUserTradingRight,pUserTradingRight,sizeof(CUserTradingRight));
	}
	if (updateIndex) {
	}

	forceCopy(pUserTradingRight,pNewUserTradingRight,sizeof(CUserTradingRight));
	pMem->updateObject(pUserTradingRight);
	if (updateIndex) {
	}
	afterUpdate(pUserTradingRight);
	if (bNoTransaction) {
		commitUpdate(pUserTradingRight,&theOldUserTradingRight);
	}
}

void CUserTradingRightFactory::update(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	pNewUserTradingRight->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pUserTradingRight,pNewUserTradingRight,updateIndex,true);
	}
	else {
		pTransaction->addResource(CUserTradingRightResource::alloc(UPDATE_ACTION,this,pUserTradingRight,pNewUserTradingRight,updateIndex));
		internalUpdate(pUserTradingRight,pNewUserTradingRight,updateIndex,false);
	}
}

void CUserTradingRightFactory::internalRemove(CUserTradingRight *pUserTradingRight, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForUserTradingRight++;
#endif
	CWriteableUserTradingRight theOldUserTradingRight;
	beforeRemove(pUserTradingRight);
	if (bNoTransaction) {
		forceCopy(&theOldUserTradingRight,pUserTradingRight,sizeof(CUserTradingRight));
	}
	if (runLevel>=0) {
		pBrkExIDInsUserInvIndex->removeObject(pUserTradingRight);
	}
	pMem->free(pUserTradingRight);
	if(bNoTransaction) {
		commitRemove(&theOldUserTradingRight);
	}
}

void CUserTradingRightFactory::remove(CUserTradingRight *pUserTradingRight, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pUserTradingRight,true);
	}
	else {
		pTransaction->addResource(CUserTradingRightResource::alloc(DELETE_ACTION,this,pUserTradingRight,NULL));
		internalRemove(pUserTradingRight,false);		
	}
}

CUserTradingRight* CUserTradingRightFactory::addOrUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	if(pUserTradingRight == NULL) {
		return add(pNewUserTradingRight,pTransaction);
	}
	else {
		update(pUserTradingRight,pNewUserTradingRight,pTransaction,updateIndex);
		return pUserTradingRight;
	}
}

void CUserTradingRightFactory::retrieve(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pTargetUserTradingRight)
{
	forceCopy(pTargetUserTradingRight, pUserTradingRight, sizeof(CUserTradingRight));
}
	
int CUserTradingRightFactory::addActionTrigger(CUserTradingRightActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CUserTradingRightFactory::removeActionTrigger(CUserTradingRightActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CUserTradingRightFactory::addCommitTrigger(CUserTradingRightCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CUserTradingRightFactory::removeCommitTrigger(CUserTradingRightCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CUserTradingRight *CUserTradingRightFactory::getFirst(void)
{
	CUserTradingRight *pResult=(CUserTradingRight *)(pMem->getFirst());
	return pResult;
}
	
CUserTradingRight *CUserTradingRightFactory::getNext(void)
{
	CUserTradingRight *pResult=(CUserTradingRight *)(pMem->getNext());
	return pResult;
}
	
void CUserTradingRightFactory::endGet(void)
{
	pMem->endGet();
}

void CUserTradingRightFactory::beforeAdd(CWriteableUserTradingRight *pUserTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pUserTradingRight);
	}
}
	
void CUserTradingRightFactory::afterAdd(CUserTradingRight *pUserTradingRight)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pUserTradingRight);
	}
}

void CUserTradingRightFactory::beforeUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pNewUserTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pUserTradingRight,pNewUserTradingRight);
	}
}
	
void CUserTradingRightFactory::afterUpdate(CUserTradingRight *pUserTradingRight)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pUserTradingRight);
	}
}
	
void CUserTradingRightFactory::beforeRemove(CUserTradingRight *pUserTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pUserTradingRight);
	}
}

void CUserTradingRightFactory::commitAdd(CUserTradingRight *pUserTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForUserTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pUserTradingRight);
	}
}

void CUserTradingRightFactory::commitUpdate(CUserTradingRight *pUserTradingRight, CWriteableUserTradingRight *pOldUserTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForUserTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pUserTradingRight,pOldUserTradingRight);
	}
}
	
void CUserTradingRightFactory::commitRemove(CWriteableUserTradingRight *pUserTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForUserTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pUserTradingRight);
	}
}

void CUserTradingRightFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForCurrentTime=0;
int updateWithIndexActionForCurrentTime=0;
int updateWithoutIndexActionForCurrentTime=0;
int removeActionForCurrentTime=0;
int addCommitForCurrentTime=0;
int updateCommitForCurrentTime=0;
int removeCommitForCurrentTime=0;
#endif
void CCurrentTimeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	pActionTriggers=new vector<CCurrentTimeActionTrigger *>;
	pCommitTriggers=new vector<CCurrentTimeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CCurrentTimeFactory::CCurrentTimeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CCurrentTime),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CCurrentTimeFactory::CCurrentTimeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CCurrentTime),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CCurrentTimeFactory::~CCurrentTimeFactory(void)
{
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CCurrentTimeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CCurrentTimeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CCurrentTimeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableCurrentTime thisCurrentTime;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisCurrentTime.readCSV(input,pNames))
		add(&thisCurrentTime);
	fclose(input);
	delete pNames;
	return 1;
}

int CCurrentTimeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "CurrentTime.csv");
	return readCSV(szFileName);
}

int CCurrentTimeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableCurrentTime *pCurrentTime;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableCurrentTime::writeCSVHead(output);
	pCurrentTime=(CWriteableCurrentTime *)(pMem->getFirst());
	while (pCurrentTime!=NULL) {
		if (!pCurrentTime->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pCurrentTime=(CWriteableCurrentTime *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CCurrentTimeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "CurrentTime.csv");
	return writeCSV(szFileName);
}

void CCurrentTimeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CCurrentTimeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableCurrentTime *pCurrentTime;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CCurrentTimeFactory={       Total Count=%d\n", pMem->getCount());
	pCurrentTime=(CWriteableCurrentTime *)(pMem->getFirst());
	while (pCurrentTime!=NULL) {
		pCurrentTime->dump(fp,index++);
		pCurrentTime=(CWriteableCurrentTime *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CCurrentTimeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
}

CCurrentTime *CCurrentTimeFactory::internalAdd(CWriteableCurrentTime *pCurrentTime, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForCurrentTime++;
#endif
	CCurrentTime *pTarget;	
	beforeAdd(pCurrentTime);
	pTarget=(CCurrentTime *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough CurrentTime in memory database");
		return NULL;
	}
	forceCopy(pTarget, pCurrentTime, sizeof(CCurrentTime));
	pMem->updateObject(pTarget);
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CCurrentTime *CCurrentTimeFactory::add(CWriteableCurrentTime *pCurrentTime, CTransaction *pTransaction)
{
	pCurrentTime->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pCurrentTime,true);
	}
	else {
		CCurrentTime *pNewCurrentTime;
		pNewCurrentTime = internalAdd(pCurrentTime,false);
		pTransaction->addResource(CCurrentTimeResource::alloc(CREATE_ACTION,this,pNewCurrentTime,NULL));
		return pNewCurrentTime;
	}
}

void CCurrentTimeFactory::internalUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForCurrentTime++;
	}
	else {
		updateWithoutIndexActionForCurrentTime++;
	}
#endif
	CWriteableCurrentTime theOldCurrentTime;
	beforeUpdate(pCurrentTime,pNewCurrentTime);
	if (bNoTransaction) {
		forceCopy(&theOldCurrentTime,pCurrentTime,sizeof(CCurrentTime));
	}
	if (updateIndex) {
	}

	forceCopy(pCurrentTime,pNewCurrentTime,sizeof(CCurrentTime));
	pMem->updateObject(pCurrentTime);
	if (updateIndex) {
	}
	afterUpdate(pCurrentTime);
	if (bNoTransaction) {
		commitUpdate(pCurrentTime,&theOldCurrentTime);
	}
}

void CCurrentTimeFactory::update(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction, bool updateIndex)
{
	pNewCurrentTime->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pCurrentTime,pNewCurrentTime,updateIndex,true);
	}
	else {
		pTransaction->addResource(CCurrentTimeResource::alloc(UPDATE_ACTION,this,pCurrentTime,pNewCurrentTime,updateIndex));
		internalUpdate(pCurrentTime,pNewCurrentTime,updateIndex,false);
	}
}

void CCurrentTimeFactory::internalRemove(CCurrentTime *pCurrentTime, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForCurrentTime++;
#endif
	CWriteableCurrentTime theOldCurrentTime;
	beforeRemove(pCurrentTime);
	if (bNoTransaction) {
		forceCopy(&theOldCurrentTime,pCurrentTime,sizeof(CCurrentTime));
	}
	pMem->free(pCurrentTime);
	if(bNoTransaction) {
		commitRemove(&theOldCurrentTime);
	}
}

void CCurrentTimeFactory::remove(CCurrentTime *pCurrentTime, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pCurrentTime,true);
	}
	else {
		pTransaction->addResource(CCurrentTimeResource::alloc(DELETE_ACTION,this,pCurrentTime,NULL));
		internalRemove(pCurrentTime,false);		
	}
}

CCurrentTime* CCurrentTimeFactory::addOrUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime, CTransaction *pTransaction, bool updateIndex)
{
	if(pCurrentTime == NULL) {
		return add(pNewCurrentTime,pTransaction);
	}
	else {
		update(pCurrentTime,pNewCurrentTime,pTransaction,updateIndex);
		return pCurrentTime;
	}
}

void CCurrentTimeFactory::retrieve(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pTargetCurrentTime)
{
	forceCopy(pTargetCurrentTime, pCurrentTime, sizeof(CCurrentTime));
}
	
int CCurrentTimeFactory::addActionTrigger(CCurrentTimeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CCurrentTimeFactory::removeActionTrigger(CCurrentTimeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CCurrentTimeFactory::addCommitTrigger(CCurrentTimeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CCurrentTimeFactory::removeCommitTrigger(CCurrentTimeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CCurrentTime *CCurrentTimeFactory::getFirst(void)
{
	CCurrentTime *pResult=(CCurrentTime *)(pMem->getFirst());
	return pResult;
}
	
CCurrentTime *CCurrentTimeFactory::getNext(void)
{
	CCurrentTime *pResult=(CCurrentTime *)(pMem->getNext());
	return pResult;
}
	
void CCurrentTimeFactory::endGet(void)
{
	pMem->endGet();
}

void CCurrentTimeFactory::beforeAdd(CWriteableCurrentTime *pCurrentTime)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pCurrentTime);
	}
}
	
void CCurrentTimeFactory::afterAdd(CCurrentTime *pCurrentTime)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pCurrentTime);
	}
}

void CCurrentTimeFactory::beforeUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pNewCurrentTime)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pCurrentTime,pNewCurrentTime);
	}
}
	
void CCurrentTimeFactory::afterUpdate(CCurrentTime *pCurrentTime)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pCurrentTime);
	}
}
	
void CCurrentTimeFactory::beforeRemove(CCurrentTime *pCurrentTime)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pCurrentTime);
	}
}

void CCurrentTimeFactory::commitAdd(CCurrentTime *pCurrentTime)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForCurrentTime++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pCurrentTime);
	}
}

void CCurrentTimeFactory::commitUpdate(CCurrentTime *pCurrentTime, CWriteableCurrentTime *pOldCurrentTime)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForCurrentTime++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pCurrentTime,pOldCurrentTime);
	}
}
	
void CCurrentTimeFactory::commitRemove(CWriteableCurrentTime *pCurrentTime)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForCurrentTime++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pCurrentTime);
	}
}

void CCurrentTimeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForSessionIDFrontIDIndexinUserSession(const void *pV1, const void *pV2);
extern int compareForBrokerIDUserIDSFIDIndexinUserSession(const void *pV1, const void *pV2);
extern int compareForUserIndexinUserSession(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForUserSession=0;
int updateWithIndexActionForUserSession=0;
int updateWithoutIndexActionForUserSession=0;
int removeActionForUserSession=0;
int addCommitForUserSession=0;
int updateCommitForUserSession=0;
int removeCommitForUserSession=0;
#endif
void CUserSessionFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pSessionIDFrontIDIndex=new CAVLTree(maxUnit,compareForSessionIDFrontIDIndexinUserSession,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserSession_SessionIDFrontIDIndex",pSessionIDFrontIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserSession_SessionIDFrontIDIndex");
			if(it != pIndexMap->end()) {
				pSessionIDFrontIDIndex=new CAVLTree(maxUnit,compareForSessionIDFrontIDIndexinUserSession,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pSessionIDFrontIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pBrokerIDUserIDSFIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDSFIDIndexinUserSession,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserSession_BrokerIDUserIDSFIDIndex",pBrokerIDUserIDSFIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserSession_BrokerIDUserIDSFIDIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDUserIDSFIDIndex=new CAVLTree(maxUnit,compareForBrokerIDUserIDSFIDIndexinUserSession,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDUserIDSFIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	if (runLevel>=0) {
		if(!reuse) {
			pUserIndex=new CAVLTree(maxUnit,compareForUserIndexinUserSession,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserSession_UserIndex",pUserIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserSession_UserIndex");
			if(it != pIndexMap->end()) {
				pUserIndex=new CAVLTree(maxUnit,compareForUserIndexinUserSession,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pUserIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByUserID=NULL;
	pActionTriggers=new vector<CUserSessionActionTrigger *>;
	pCommitTriggers=new vector<CUserSessionCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CUserSessionFactory::CUserSessionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserSession),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CUserSessionFactory::CUserSessionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserSession),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CUserSessionFactory::~CUserSessionFactory(void)
{
	if (runLevel>=0) {
		if (pSessionIDFrontIDIndex!=NULL)
			delete pSessionIDFrontIDIndex;
	}
	if (runLevel>=0) {
		if (pBrokerIDUserIDSFIDIndex!=NULL)
			delete pBrokerIDUserIDSFIDIndex;
	}
	if (runLevel>=0) {
		if (pUserIndex!=NULL)
			delete pUserIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CUserSessionFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserSessionFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pSessionIDFrontIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pBrokerIDUserIDSFIDIndex->output(pLogger,indent+1);
	}
	if (runLevel>=0) {
		pUserIndex->output(pLogger,indent+1);
	}
}

int CUserSessionFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableUserSession thisUserSession;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisUserSession.readCSV(input,pNames))
		add(&thisUserSession);
	fclose(input);
	delete pNames;
	return 1;
}

int CUserSessionFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "UserSession.csv");
	return readCSV(szFileName);
}

int CUserSessionFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableUserSession *pUserSession;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableUserSession::writeCSVHead(output);
	pUserSession=(CWriteableUserSession *)(pMem->getFirst());
	while (pUserSession!=NULL) {
		if (!pUserSession->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pUserSession=(CWriteableUserSession *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CUserSessionFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserSession.csv");
	return writeCSV(szFileName);
}

void CUserSessionFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CUserSessionFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableUserSession *pUserSession;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CUserSessionFactory={       Total Count=%d\n", pMem->getCount());
	pUserSession=(CWriteableUserSession *)(pMem->getFirst());
	while (pUserSession!=NULL) {
		pUserSession->dump(fp,index++);
		pUserSession=(CWriteableUserSession *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CUserSessionFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pSessionIDFrontIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pBrokerIDUserIDSFIDIndex->removeAll();
	}
	if (runLevel>=0) {
		pUserIndex->removeAll();
	}
}

CUserSession *CUserSessionFactory::internalAdd(CWriteableUserSession *pUserSession, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForUserSession++;
#endif
	CUserSession *pTarget;	
	beforeAdd(pUserSession);
	pTarget=(CUserSession *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough UserSession in memory database");
		return NULL;
	}
	forceCopy(pTarget, pUserSession, sizeof(CUserSession));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pSessionIDFrontIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pBrokerIDUserIDSFIDIndex->addObject(pTarget);
	}
	if (runLevel>=0) {
		pUserIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CUserSession *CUserSessionFactory::add(CWriteableUserSession *pUserSession, CTransaction *pTransaction)
{
	pUserSession->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pUserSession,true);
	}
	else {
		CUserSession *pNewUserSession;
		pNewUserSession = internalAdd(pUserSession,false);
		pTransaction->addResource(CUserSessionResource::alloc(CREATE_ACTION,this,pNewUserSession,NULL));
		return pNewUserSession;
	}
}

void CUserSessionFactory::internalUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForUserSession++;
	}
	else {
		updateWithoutIndexActionForUserSession++;
	}
#endif
	CWriteableUserSession theOldUserSession;
	beforeUpdate(pUserSession,pNewUserSession);
	if (bNoTransaction) {
		forceCopy(&theOldUserSession,pUserSession,sizeof(CUserSession));
	}
	CAVLNode *pBrokerIDUserIDSFIDIndexNode=NULL;
	CAVLNode *pUserIndexNode=NULL;
	if (updateIndex) {
		if (runLevel>=0) {
			pBrokerIDUserIDSFIDIndexNode=pBrokerIDUserIDSFIDIndex->findObject(pUserSession);
		}
		if (runLevel>=0) {
			pUserIndexNode=pUserIndex->findObject(pUserSession);
		}
	}

	forceCopy(pUserSession,pNewUserSession,sizeof(CUserSession));
	pMem->updateObject(pUserSession);
	if (updateIndex) {
		if (runLevel>=0) {
			pBrokerIDUserIDSFIDIndex->updateNode(pBrokerIDUserIDSFIDIndexNode);
		}
		if (runLevel>=0) {
			pUserIndex->updateNode(pUserIndexNode);
		}
	}
	afterUpdate(pUserSession);
	if (bNoTransaction) {
		commitUpdate(pUserSession,&theOldUserSession);
	}
}

void CUserSessionFactory::update(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction, bool updateIndex)
{
	pNewUserSession->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pUserSession,pNewUserSession,updateIndex,true);
	}
	else {
		pTransaction->addResource(CUserSessionResource::alloc(UPDATE_ACTION,this,pUserSession,pNewUserSession,updateIndex));
		internalUpdate(pUserSession,pNewUserSession,updateIndex,false);
	}
}

void CUserSessionFactory::internalRemove(CUserSession *pUserSession, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForUserSession++;
#endif
	CWriteableUserSession theOldUserSession;
	beforeRemove(pUserSession);
	if (bNoTransaction) {
		forceCopy(&theOldUserSession,pUserSession,sizeof(CUserSession));
	}
	if (runLevel>=0) {
		pSessionIDFrontIDIndex->removeObject(pUserSession);
	}
	if (runLevel>=0) {
		pBrokerIDUserIDSFIDIndex->removeObject(pUserSession);
	}
	if (runLevel>=0) {
		pUserIndex->removeObject(pUserSession);
	}
	pMem->free(pUserSession);
	if(bNoTransaction) {
		commitRemove(&theOldUserSession);
	}
}

void CUserSessionFactory::remove(CUserSession *pUserSession, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pUserSession,true);
	}
	else {
		pTransaction->addResource(CUserSessionResource::alloc(DELETE_ACTION,this,pUserSession,NULL));
		internalRemove(pUserSession,false);		
	}
}

CUserSession* CUserSessionFactory::addOrUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession, CTransaction *pTransaction, bool updateIndex)
{
	if(pUserSession == NULL) {
		return add(pNewUserSession,pTransaction);
	}
	else {
		update(pUserSession,pNewUserSession,pTransaction,updateIndex);
		return pUserSession;
	}
}

void CUserSessionFactory::retrieve(CUserSession *pUserSession, CWriteableUserSession *pTargetUserSession)
{
	forceCopy(pTargetUserSession, pUserSession, sizeof(CUserSession));
}
	
int CUserSessionFactory::addActionTrigger(CUserSessionActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CUserSessionFactory::removeActionTrigger(CUserSessionActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CUserSessionFactory::addCommitTrigger(CUserSessionCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CUserSessionFactory::removeCommitTrigger(CUserSessionCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CUserSession *CUserSessionFactory::getFirst(void)
{
	CUserSession *pResult=(CUserSession *)(pMem->getFirst());
	return pResult;
}
	
CUserSession *CUserSessionFactory::getNext(void)
{
	CUserSession *pResult=(CUserSession *)(pMem->getNext());
	return pResult;
}
	
void CUserSessionFactory::endGet(void)
{
	pMem->endGet();
}

void CUserSessionFactory::beforeAdd(CWriteableUserSession *pUserSession)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pUserSession);
	}
}
	
void CUserSessionFactory::afterAdd(CUserSession *pUserSession)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pUserSession);
	}
}

void CUserSessionFactory::beforeUpdate(CUserSession *pUserSession, CWriteableUserSession *pNewUserSession)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pUserSession,pNewUserSession);
	}
}
	
void CUserSessionFactory::afterUpdate(CUserSession *pUserSession)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pUserSession);
	}
}
	
void CUserSessionFactory::beforeRemove(CUserSession *pUserSession)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pUserSession);
	}
}

void CUserSessionFactory::commitAdd(CUserSession *pUserSession)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForUserSession++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pUserSession);
	}
}

void CUserSessionFactory::commitUpdate(CUserSession *pUserSession, CWriteableUserSession *pOldUserSession)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForUserSession++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pUserSession,pOldUserSession);
	}
}
	
void CUserSessionFactory::commitRemove(CWriteableUserSession *pUserSession)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForUserSession++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pUserSession);
	}
}

void CUserSessionFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForMaxLocalID=0;
int updateWithIndexActionForMaxLocalID=0;
int updateWithoutIndexActionForMaxLocalID=0;
int removeActionForMaxLocalID=0;
int addCommitForMaxLocalID=0;
int updateCommitForMaxLocalID=0;
int removeCommitForMaxLocalID=0;
#endif
void CMaxLocalIDFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=769;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("MaxLocalID.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pFrontIDSessionIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("MaxLocalID_FrontIDSessionIDHashIndex",pFrontIDSessionIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("MaxLocalID_FrontIDSessionIDHashIndex");
			if(it != pIndexMap->end()) {
				pFrontIDSessionIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pFrontIDSessionIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CMaxLocalIDActionTrigger *>;
	pCommitTriggers=new vector<CMaxLocalIDCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CMaxLocalIDFactory::CMaxLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CMaxLocalID),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CMaxLocalIDFactory::CMaxLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CMaxLocalID),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CMaxLocalIDFactory::~CMaxLocalIDFactory(void)
{
	if (runLevel>=0) {
		if (pFrontIDSessionIDHashIndex!=NULL)
			delete pFrontIDSessionIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CMaxLocalIDFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CMaxLocalIDFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CMaxLocalIDFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableMaxLocalID thisMaxLocalID;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisMaxLocalID.readCSV(input,pNames))
		add(&thisMaxLocalID);
	fclose(input);
	delete pNames;
	return 1;
}

int CMaxLocalIDFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "MaxLocalID.csv");
	return readCSV(szFileName);
}

int CMaxLocalIDFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableMaxLocalID *pMaxLocalID;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableMaxLocalID::writeCSVHead(output);
	pMaxLocalID=(CWriteableMaxLocalID *)(pMem->getFirst());
	while (pMaxLocalID!=NULL) {
		if (!pMaxLocalID->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pMaxLocalID=(CWriteableMaxLocalID *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CMaxLocalIDFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "MaxLocalID.csv");
	return writeCSV(szFileName);
}

void CMaxLocalIDFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CMaxLocalIDFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableMaxLocalID *pMaxLocalID;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CMaxLocalIDFactory={       Total Count=%d\n", pMem->getCount());
	pMaxLocalID=(CWriteableMaxLocalID *)(pMem->getFirst());
	while (pMaxLocalID!=NULL) {
		pMaxLocalID->dump(fp,index++);
		pMaxLocalID=(CWriteableMaxLocalID *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CMaxLocalIDFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pFrontIDSessionIDHashIndex->removeAll();
	}
}

CMaxLocalID *CMaxLocalIDFactory::internalAdd(CWriteableMaxLocalID *pMaxLocalID, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForMaxLocalID++;
#endif
	CMaxLocalID *pTarget;	
	beforeAdd(pMaxLocalID);
	pTarget=(CMaxLocalID *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough MaxLocalID in memory database");
		return NULL;
	}
	forceCopy(pTarget, pMaxLocalID, sizeof(CMaxLocalID));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pFrontIDSessionIDHashIndex->addObject(pTarget,pTarget->HashFrontIDSessionID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CMaxLocalID *CMaxLocalIDFactory::add(CWriteableMaxLocalID *pMaxLocalID, CTransaction *pTransaction)
{
	pMaxLocalID->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pMaxLocalID,true);
	}
	else {
		CMaxLocalID *pNewMaxLocalID;
		pNewMaxLocalID = internalAdd(pMaxLocalID,false);
		pTransaction->addResource(CMaxLocalIDResource::alloc(CREATE_ACTION,this,pNewMaxLocalID,NULL));
		return pNewMaxLocalID;
	}
}

void CMaxLocalIDFactory::internalUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForMaxLocalID++;
	}
	else {
		updateWithoutIndexActionForMaxLocalID++;
	}
#endif
	CWriteableMaxLocalID theOldMaxLocalID;
	beforeUpdate(pMaxLocalID,pNewMaxLocalID);
	if (bNoTransaction) {
		forceCopy(&theOldMaxLocalID,pMaxLocalID,sizeof(CMaxLocalID));
	}
	if (updateIndex) {
	}

	forceCopy(pMaxLocalID,pNewMaxLocalID,sizeof(CMaxLocalID));
	pMem->updateObject(pMaxLocalID);
	if (updateIndex) {
	}
	afterUpdate(pMaxLocalID);
	if (bNoTransaction) {
		commitUpdate(pMaxLocalID,&theOldMaxLocalID);
	}
}

void CMaxLocalIDFactory::update(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction, bool updateIndex)
{
	pNewMaxLocalID->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pMaxLocalID,pNewMaxLocalID,updateIndex,true);
	}
	else {
		pTransaction->addResource(CMaxLocalIDResource::alloc(UPDATE_ACTION,this,pMaxLocalID,pNewMaxLocalID,updateIndex));
		internalUpdate(pMaxLocalID,pNewMaxLocalID,updateIndex,false);
	}
}

void CMaxLocalIDFactory::internalRemove(CMaxLocalID *pMaxLocalID, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForMaxLocalID++;
#endif
	CWriteableMaxLocalID theOldMaxLocalID;
	beforeRemove(pMaxLocalID);
	if (bNoTransaction) {
		forceCopy(&theOldMaxLocalID,pMaxLocalID,sizeof(CMaxLocalID));
	}
	if (runLevel>=0) {
		pFrontIDSessionIDHashIndex->removeObject(pMaxLocalID,pMaxLocalID->HashFrontIDSessionID);
	}	
	pMem->free(pMaxLocalID);
	if(bNoTransaction) {
		commitRemove(&theOldMaxLocalID);
	}
}

void CMaxLocalIDFactory::remove(CMaxLocalID *pMaxLocalID, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pMaxLocalID,true);
	}
	else {
		pTransaction->addResource(CMaxLocalIDResource::alloc(DELETE_ACTION,this,pMaxLocalID,NULL));
		internalRemove(pMaxLocalID,false);		
	}
}

CMaxLocalID* CMaxLocalIDFactory::addOrUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID, CTransaction *pTransaction, bool updateIndex)
{
	if(pMaxLocalID == NULL) {
		return add(pNewMaxLocalID,pTransaction);
	}
	else {
		update(pMaxLocalID,pNewMaxLocalID,pTransaction,updateIndex);
		return pMaxLocalID;
	}
}

void CMaxLocalIDFactory::retrieve(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pTargetMaxLocalID)
{
	forceCopy(pTargetMaxLocalID, pMaxLocalID, sizeof(CMaxLocalID));
}
	
int CMaxLocalIDFactory::addActionTrigger(CMaxLocalIDActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CMaxLocalIDFactory::removeActionTrigger(CMaxLocalIDActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CMaxLocalIDFactory::addCommitTrigger(CMaxLocalIDCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CMaxLocalIDFactory::removeCommitTrigger(CMaxLocalIDCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CMaxLocalID *CMaxLocalIDFactory::getFirst(void)
{
	CMaxLocalID *pResult=(CMaxLocalID *)(pMem->getFirst());
	return pResult;
}
	
CMaxLocalID *CMaxLocalIDFactory::getNext(void)
{
	CMaxLocalID *pResult=(CMaxLocalID *)(pMem->getNext());
	return pResult;
}
	
void CMaxLocalIDFactory::endGet(void)
{
	pMem->endGet();
}

void CMaxLocalIDFactory::beforeAdd(CWriteableMaxLocalID *pMaxLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pMaxLocalID);
	}
}
	
void CMaxLocalIDFactory::afterAdd(CMaxLocalID *pMaxLocalID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pMaxLocalID);
	}
}

void CMaxLocalIDFactory::beforeUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pNewMaxLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pMaxLocalID,pNewMaxLocalID);
	}
}
	
void CMaxLocalIDFactory::afterUpdate(CMaxLocalID *pMaxLocalID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pMaxLocalID);
	}
}
	
void CMaxLocalIDFactory::beforeRemove(CMaxLocalID *pMaxLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pMaxLocalID);
	}
}

void CMaxLocalIDFactory::commitAdd(CMaxLocalID *pMaxLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForMaxLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pMaxLocalID);
	}
}

void CMaxLocalIDFactory::commitUpdate(CMaxLocalID *pMaxLocalID, CWriteableMaxLocalID *pOldMaxLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForMaxLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pMaxLocalID,pOldMaxLocalID);
	}
}
	
void CMaxLocalIDFactory::commitRemove(CWriteableMaxLocalID *pMaxLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForMaxLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pMaxLocalID);
	}
}

void CMaxLocalIDFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForBrkUserIDLocalID=0;
int updateWithIndexActionForBrkUserIDLocalID=0;
int updateWithoutIndexActionForBrkUserIDLocalID=0;
int removeActionForBrkUserIDLocalID=0;
int addCommitForBrkUserIDLocalID=0;
int updateCommitForBrkUserIDLocalID=0;
int removeCommitForBrkUserIDLocalID=0;
#endif
void CBrkUserIDLocalIDFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=769;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("BrkUserIDLocalID.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pBrokerIDUserIDLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("BrkUserIDLocalID_BrokerIDUserIDLocalIDHashIndex",pBrokerIDUserIDLocalIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("BrkUserIDLocalID_BrokerIDUserIDLocalIDHashIndex");
			if(it != pIndexMap->end()) {
				pBrokerIDUserIDLocalIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerIDUserIDLocalIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CBrkUserIDLocalIDActionTrigger *>;
	pCommitTriggers=new vector<CBrkUserIDLocalIDCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CBrkUserIDLocalIDFactory::CBrkUserIDLocalIDFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CBrkUserIDLocalID),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CBrkUserIDLocalIDFactory::CBrkUserIDLocalIDFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CBrkUserIDLocalID),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CBrkUserIDLocalIDFactory::~CBrkUserIDLocalIDFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerIDUserIDLocalIDHashIndex!=NULL)
			delete pBrokerIDUserIDLocalIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CBrkUserIDLocalIDFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CBrkUserIDLocalIDFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CBrkUserIDLocalIDFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableBrkUserIDLocalID thisBrkUserIDLocalID;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisBrkUserIDLocalID.readCSV(input,pNames))
		add(&thisBrkUserIDLocalID);
	fclose(input);
	delete pNames;
	return 1;
}

int CBrkUserIDLocalIDFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "BrkUserIDLocalID.csv");
	return readCSV(szFileName);
}

int CBrkUserIDLocalIDFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableBrkUserIDLocalID *pBrkUserIDLocalID;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableBrkUserIDLocalID::writeCSVHead(output);
	pBrkUserIDLocalID=(CWriteableBrkUserIDLocalID *)(pMem->getFirst());
	while (pBrkUserIDLocalID!=NULL) {
		if (!pBrkUserIDLocalID->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pBrkUserIDLocalID=(CWriteableBrkUserIDLocalID *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CBrkUserIDLocalIDFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "BrkUserIDLocalID.csv");
	return writeCSV(szFileName);
}

void CBrkUserIDLocalIDFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CBrkUserIDLocalIDFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableBrkUserIDLocalID *pBrkUserIDLocalID;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CBrkUserIDLocalIDFactory={       Total Count=%d\n", pMem->getCount());
	pBrkUserIDLocalID=(CWriteableBrkUserIDLocalID *)(pMem->getFirst());
	while (pBrkUserIDLocalID!=NULL) {
		pBrkUserIDLocalID->dump(fp,index++);
		pBrkUserIDLocalID=(CWriteableBrkUserIDLocalID *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CBrkUserIDLocalIDFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerIDUserIDLocalIDHashIndex->removeAll();
	}
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::internalAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForBrkUserIDLocalID++;
#endif
	CBrkUserIDLocalID *pTarget;	
	beforeAdd(pBrkUserIDLocalID);
	pTarget=(CBrkUserIDLocalID *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough BrkUserIDLocalID in memory database");
		return NULL;
	}
	forceCopy(pTarget, pBrkUserIDLocalID, sizeof(CBrkUserIDLocalID));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerIDUserIDLocalIDHashIndex->addObject(pTarget,pTarget->HashBrokerIDUserIDLocalID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::add(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction)
{
	pBrkUserIDLocalID->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pBrkUserIDLocalID,true);
	}
	else {
		CBrkUserIDLocalID *pNewBrkUserIDLocalID;
		pNewBrkUserIDLocalID = internalAdd(pBrkUserIDLocalID,false);
		pTransaction->addResource(CBrkUserIDLocalIDResource::alloc(CREATE_ACTION,this,pNewBrkUserIDLocalID,NULL));
		return pNewBrkUserIDLocalID;
	}
}

void CBrkUserIDLocalIDFactory::internalUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForBrkUserIDLocalID++;
	}
	else {
		updateWithoutIndexActionForBrkUserIDLocalID++;
	}
#endif
	CWriteableBrkUserIDLocalID theOldBrkUserIDLocalID;
	beforeUpdate(pBrkUserIDLocalID,pNewBrkUserIDLocalID);
	if (bNoTransaction) {
		forceCopy(&theOldBrkUserIDLocalID,pBrkUserIDLocalID,sizeof(CBrkUserIDLocalID));
	}
	if (updateIndex) {
	}

	forceCopy(pBrkUserIDLocalID,pNewBrkUserIDLocalID,sizeof(CBrkUserIDLocalID));
	pMem->updateObject(pBrkUserIDLocalID);
	if (updateIndex) {
	}
	afterUpdate(pBrkUserIDLocalID);
	if (bNoTransaction) {
		commitUpdate(pBrkUserIDLocalID,&theOldBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::update(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction, bool updateIndex)
{
	pNewBrkUserIDLocalID->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pBrkUserIDLocalID,pNewBrkUserIDLocalID,updateIndex,true);
	}
	else {
		pTransaction->addResource(CBrkUserIDLocalIDResource::alloc(UPDATE_ACTION,this,pBrkUserIDLocalID,pNewBrkUserIDLocalID,updateIndex));
		internalUpdate(pBrkUserIDLocalID,pNewBrkUserIDLocalID,updateIndex,false);
	}
}

void CBrkUserIDLocalIDFactory::internalRemove(CBrkUserIDLocalID *pBrkUserIDLocalID, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForBrkUserIDLocalID++;
#endif
	CWriteableBrkUserIDLocalID theOldBrkUserIDLocalID;
	beforeRemove(pBrkUserIDLocalID);
	if (bNoTransaction) {
		forceCopy(&theOldBrkUserIDLocalID,pBrkUserIDLocalID,sizeof(CBrkUserIDLocalID));
	}
	if (runLevel>=0) {
		pBrokerIDUserIDLocalIDHashIndex->removeObject(pBrkUserIDLocalID,pBrkUserIDLocalID->HashBrokerIDUserIDLocalID);
	}	
	pMem->free(pBrkUserIDLocalID);
	if(bNoTransaction) {
		commitRemove(&theOldBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::remove(CBrkUserIDLocalID *pBrkUserIDLocalID, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pBrkUserIDLocalID,true);
	}
	else {
		pTransaction->addResource(CBrkUserIDLocalIDResource::alloc(DELETE_ACTION,this,pBrkUserIDLocalID,NULL));
		internalRemove(pBrkUserIDLocalID,false);		
	}
}

CBrkUserIDLocalID* CBrkUserIDLocalIDFactory::addOrUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID, CTransaction *pTransaction, bool updateIndex)
{
	if(pBrkUserIDLocalID == NULL) {
		return add(pNewBrkUserIDLocalID,pTransaction);
	}
	else {
		update(pBrkUserIDLocalID,pNewBrkUserIDLocalID,pTransaction,updateIndex);
		return pBrkUserIDLocalID;
	}
}

void CBrkUserIDLocalIDFactory::retrieve(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pTargetBrkUserIDLocalID)
{
	forceCopy(pTargetBrkUserIDLocalID, pBrkUserIDLocalID, sizeof(CBrkUserIDLocalID));
}
	
int CBrkUserIDLocalIDFactory::addActionTrigger(CBrkUserIDLocalIDActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CBrkUserIDLocalIDFactory::removeActionTrigger(CBrkUserIDLocalIDActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CBrkUserIDLocalIDFactory::addCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CBrkUserIDLocalIDFactory::removeCommitTrigger(CBrkUserIDLocalIDCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::getFirst(void)
{
	CBrkUserIDLocalID *pResult=(CBrkUserIDLocalID *)(pMem->getFirst());
	return pResult;
}
	
CBrkUserIDLocalID *CBrkUserIDLocalIDFactory::getNext(void)
{
	CBrkUserIDLocalID *pResult=(CBrkUserIDLocalID *)(pMem->getNext());
	return pResult;
}
	
void CBrkUserIDLocalIDFactory::endGet(void)
{
	pMem->endGet();
}

void CBrkUserIDLocalIDFactory::beforeAdd(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pBrkUserIDLocalID);
	}
}
	
void CBrkUserIDLocalIDFactory::afterAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::beforeUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pNewBrkUserIDLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pBrkUserIDLocalID,pNewBrkUserIDLocalID);
	}
}
	
void CBrkUserIDLocalIDFactory::afterUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pBrkUserIDLocalID);
	}
}
	
void CBrkUserIDLocalIDFactory::beforeRemove(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::commitAdd(CBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForBrkUserIDLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::commitUpdate(CBrkUserIDLocalID *pBrkUserIDLocalID, CWriteableBrkUserIDLocalID *pOldBrkUserIDLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForBrkUserIDLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pBrkUserIDLocalID,pOldBrkUserIDLocalID);
	}
}
	
void CBrkUserIDLocalIDFactory::commitRemove(CWriteableBrkUserIDLocalID *pBrkUserIDLocalID)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForBrkUserIDLocalID++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pBrkUserIDLocalID);
	}
}

void CBrkUserIDLocalIDFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

void CBrkUserIDLocalIDFactory::linkAllPreOrder(CPreOrderFactory *pFactory)
{
	CBrkUserIDLocalID *pBrkUserIDLocalID;
	pBrkUserIDLocalID=getFirst();
	while (pBrkUserIDLocalID != NULL) {
		pBrkUserIDLocalID->linkPreOrder(pFactory);
		pBrkUserIDLocalID=getNext();
	}
	endGet();
}

#ifdef COUNT_OPERATION
int addActionForPartClientInsGroupPosition=0;
int updateWithIndexActionForPartClientInsGroupPosition=0;
int updateWithoutIndexActionForPartClientInsGroupPosition=0;
int removeActionForPartClientInsGroupPosition=0;
int addCommitForPartClientInsGroupPosition=0;
int updateCommitForPartClientInsGroupPosition=0;
int removeCommitForPartClientInsGroupPosition=0;
#endif
void CPartClientInsGroupPositionFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=1572869;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("PartClientInsGroupPosition.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pPartClientAndInsGroupHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("PartClientInsGroupPosition_PartClientAndInsGroupHashIndex",pPartClientAndInsGroupHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("PartClientInsGroupPosition_PartClientAndInsGroupHashIndex");
			if(it != pIndexMap->end()) {
				pPartClientAndInsGroupHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pPartClientAndInsGroupHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CPartClientInsGroupPositionActionTrigger *>;
	pCommitTriggers=new vector<CPartClientInsGroupPositionCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CPartClientInsGroupPositionFactory::CPartClientInsGroupPositionFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CPartClientInsGroupPosition),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CPartClientInsGroupPositionFactory::CPartClientInsGroupPositionFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CPartClientInsGroupPosition),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CPartClientInsGroupPositionFactory::~CPartClientInsGroupPositionFactory(void)
{
	if (runLevel>=0) {
		if (pPartClientAndInsGroupHashIndex!=NULL)
			delete pPartClientAndInsGroupHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CPartClientInsGroupPositionFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CPartClientInsGroupPositionFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CPartClientInsGroupPositionFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteablePartClientInsGroupPosition thisPartClientInsGroupPosition;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisPartClientInsGroupPosition.readCSV(input,pNames))
		add(&thisPartClientInsGroupPosition);
	fclose(input);
	delete pNames;
	return 1;
}

int CPartClientInsGroupPositionFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "PartClientInsGroupPosition.csv");
	return readCSV(szFileName);
}

int CPartClientInsGroupPositionFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteablePartClientInsGroupPosition::writeCSVHead(output);
	pPartClientInsGroupPosition=(CWriteablePartClientInsGroupPosition *)(pMem->getFirst());
	while (pPartClientInsGroupPosition!=NULL) {
		if (!pPartClientInsGroupPosition->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pPartClientInsGroupPosition=(CWriteablePartClientInsGroupPosition *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CPartClientInsGroupPositionFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "PartClientInsGroupPosition.csv");
	return writeCSV(szFileName);
}

void CPartClientInsGroupPositionFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CPartClientInsGroupPositionFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CPartClientInsGroupPositionFactory={       Total Count=%d\n", pMem->getCount());
	pPartClientInsGroupPosition=(CWriteablePartClientInsGroupPosition *)(pMem->getFirst());
	while (pPartClientInsGroupPosition!=NULL) {
		pPartClientInsGroupPosition->dump(fp,index++);
		pPartClientInsGroupPosition=(CWriteablePartClientInsGroupPosition *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CPartClientInsGroupPositionFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pPartClientAndInsGroupHashIndex->removeAll();
	}
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionFactory::internalAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForPartClientInsGroupPosition++;
#endif
	CPartClientInsGroupPosition *pTarget;	
	beforeAdd(pPartClientInsGroupPosition);
	pTarget=(CPartClientInsGroupPosition *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough PartClientInsGroupPosition in memory database");
		return NULL;
	}
	forceCopy(pTarget, pPartClientInsGroupPosition, sizeof(CPartClientInsGroupPosition));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pPartClientAndInsGroupHashIndex->addObject(pTarget,pTarget->HashPartClientAndInsGroup);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionFactory::add(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction)
{
	pPartClientInsGroupPosition->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pPartClientInsGroupPosition,true);
	}
	else {
		CPartClientInsGroupPosition *pNewPartClientInsGroupPosition;
		pNewPartClientInsGroupPosition = internalAdd(pPartClientInsGroupPosition,false);
		pTransaction->addResource(CPartClientInsGroupPositionResource::alloc(CREATE_ACTION,this,pNewPartClientInsGroupPosition,NULL));
		return pNewPartClientInsGroupPosition;
	}
}

void CPartClientInsGroupPositionFactory::internalUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForPartClientInsGroupPosition++;
	}
	else {
		updateWithoutIndexActionForPartClientInsGroupPosition++;
	}
#endif
	CWriteablePartClientInsGroupPosition theOldPartClientInsGroupPosition;
	beforeUpdate(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition);
	if (bNoTransaction) {
		forceCopy(&theOldPartClientInsGroupPosition,pPartClientInsGroupPosition,sizeof(CPartClientInsGroupPosition));
	}
	if (updateIndex) {
	}

	forceCopy(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition,sizeof(CPartClientInsGroupPosition));
	pMem->updateObject(pPartClientInsGroupPosition);
	if (updateIndex) {
	}
	afterUpdate(pPartClientInsGroupPosition);
	if (bNoTransaction) {
		commitUpdate(pPartClientInsGroupPosition,&theOldPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::update(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction, bool updateIndex)
{
	pNewPartClientInsGroupPosition->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition,updateIndex,true);
	}
	else {
		pTransaction->addResource(CPartClientInsGroupPositionResource::alloc(UPDATE_ACTION,this,pPartClientInsGroupPosition,pNewPartClientInsGroupPosition,updateIndex));
		internalUpdate(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition,updateIndex,false);
	}
}

void CPartClientInsGroupPositionFactory::internalRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForPartClientInsGroupPosition++;
#endif
	CWriteablePartClientInsGroupPosition theOldPartClientInsGroupPosition;
	beforeRemove(pPartClientInsGroupPosition);
	if (bNoTransaction) {
		forceCopy(&theOldPartClientInsGroupPosition,pPartClientInsGroupPosition,sizeof(CPartClientInsGroupPosition));
	}
	if (runLevel>=0) {
		pPartClientAndInsGroupHashIndex->removeObject(pPartClientInsGroupPosition,pPartClientInsGroupPosition->HashPartClientAndInsGroup);
	}	
	pMem->free(pPartClientInsGroupPosition);
	if(bNoTransaction) {
		commitRemove(&theOldPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::remove(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pPartClientInsGroupPosition,true);
	}
	else {
		pTransaction->addResource(CPartClientInsGroupPositionResource::alloc(DELETE_ACTION,this,pPartClientInsGroupPosition,NULL));
		internalRemove(pPartClientInsGroupPosition,false);		
	}
}

CPartClientInsGroupPosition* CPartClientInsGroupPositionFactory::addOrUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition, CTransaction *pTransaction, bool updateIndex)
{
	if(pPartClientInsGroupPosition == NULL) {
		return add(pNewPartClientInsGroupPosition,pTransaction);
	}
	else {
		update(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition,pTransaction,updateIndex);
		return pPartClientInsGroupPosition;
	}
}

void CPartClientInsGroupPositionFactory::retrieve(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pTargetPartClientInsGroupPosition)
{
	forceCopy(pTargetPartClientInsGroupPosition, pPartClientInsGroupPosition, sizeof(CPartClientInsGroupPosition));
}
	
int CPartClientInsGroupPositionFactory::addActionTrigger(CPartClientInsGroupPositionActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CPartClientInsGroupPositionFactory::removeActionTrigger(CPartClientInsGroupPositionActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CPartClientInsGroupPositionFactory::addCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CPartClientInsGroupPositionFactory::removeCommitTrigger(CPartClientInsGroupPositionCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CPartClientInsGroupPosition *CPartClientInsGroupPositionFactory::getFirst(void)
{
	CPartClientInsGroupPosition *pResult=(CPartClientInsGroupPosition *)(pMem->getFirst());
	return pResult;
}
	
CPartClientInsGroupPosition *CPartClientInsGroupPositionFactory::getNext(void)
{
	CPartClientInsGroupPosition *pResult=(CPartClientInsGroupPosition *)(pMem->getNext());
	return pResult;
}
	
void CPartClientInsGroupPositionFactory::endGet(void)
{
	pMem->endGet();
}

void CPartClientInsGroupPositionFactory::beforeAdd(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pPartClientInsGroupPosition);
	}
}
	
void CPartClientInsGroupPositionFactory::afterAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::beforeUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pNewPartClientInsGroupPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pPartClientInsGroupPosition,pNewPartClientInsGroupPosition);
	}
}
	
void CPartClientInsGroupPositionFactory::afterUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pPartClientInsGroupPosition);
	}
}
	
void CPartClientInsGroupPositionFactory::beforeRemove(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::commitAdd(CPartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForPartClientInsGroupPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::commitUpdate(CPartClientInsGroupPosition *pPartClientInsGroupPosition, CWriteablePartClientInsGroupPosition *pOldPartClientInsGroupPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForPartClientInsGroupPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pPartClientInsGroupPosition,pOldPartClientInsGroupPosition);
	}
}
	
void CPartClientInsGroupPositionFactory::commitRemove(CWriteablePartClientInsGroupPosition *pPartClientInsGroupPosition)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForPartClientInsGroupPosition++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pPartClientInsGroupPosition);
	}
}

void CPartClientInsGroupPositionFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForClientMarginCombType=0;
int updateWithIndexActionForClientMarginCombType=0;
int updateWithoutIndexActionForClientMarginCombType=0;
int removeActionForClientMarginCombType=0;
int addCommitForClientMarginCombType=0;
int updateCommitForClientMarginCombType=0;
int removeCommitForClientMarginCombType=0;
#endif
void CClientMarginCombTypeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=6151;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("ClientMarginCombType.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pClientAndInsGroupHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("ClientMarginCombType_ClientAndInsGroupHashIndex",pClientAndInsGroupHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("ClientMarginCombType_ClientAndInsGroupHashIndex");
			if(it != pIndexMap->end()) {
				pClientAndInsGroupHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pClientAndInsGroupHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CClientMarginCombTypeActionTrigger *>;
	pCommitTriggers=new vector<CClientMarginCombTypeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CClientMarginCombTypeFactory::CClientMarginCombTypeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CClientMarginCombType),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CClientMarginCombTypeFactory::CClientMarginCombTypeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CClientMarginCombType),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CClientMarginCombTypeFactory::~CClientMarginCombTypeFactory(void)
{
	if (runLevel>=0) {
		if (pClientAndInsGroupHashIndex!=NULL)
			delete pClientAndInsGroupHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CClientMarginCombTypeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CClientMarginCombTypeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CClientMarginCombTypeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableClientMarginCombType thisClientMarginCombType;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisClientMarginCombType.readCSV(input,pNames))
		add(&thisClientMarginCombType);
	fclose(input);
	delete pNames;
	return 1;
}

int CClientMarginCombTypeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "ClientMarginCombType.csv");
	return readCSV(szFileName);
}

int CClientMarginCombTypeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableClientMarginCombType *pClientMarginCombType;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableClientMarginCombType::writeCSVHead(output);
	pClientMarginCombType=(CWriteableClientMarginCombType *)(pMem->getFirst());
	while (pClientMarginCombType!=NULL) {
		if (!pClientMarginCombType->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pClientMarginCombType=(CWriteableClientMarginCombType *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CClientMarginCombTypeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "ClientMarginCombType.csv");
	return writeCSV(szFileName);
}

void CClientMarginCombTypeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CClientMarginCombTypeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableClientMarginCombType *pClientMarginCombType;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CClientMarginCombTypeFactory={       Total Count=%d\n", pMem->getCount());
	pClientMarginCombType=(CWriteableClientMarginCombType *)(pMem->getFirst());
	while (pClientMarginCombType!=NULL) {
		pClientMarginCombType->dump(fp,index++);
		pClientMarginCombType=(CWriteableClientMarginCombType *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CClientMarginCombTypeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pClientAndInsGroupHashIndex->removeAll();
	}
}

CClientMarginCombType *CClientMarginCombTypeFactory::internalAdd(CWriteableClientMarginCombType *pClientMarginCombType, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForClientMarginCombType++;
#endif
	CClientMarginCombType *pTarget;	
	beforeAdd(pClientMarginCombType);
	pTarget=(CClientMarginCombType *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough ClientMarginCombType in memory database");
		return NULL;
	}
	forceCopy(pTarget, pClientMarginCombType, sizeof(CClientMarginCombType));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pClientAndInsGroupHashIndex->addObject(pTarget,pTarget->HashClientAndInsGroup);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CClientMarginCombType *CClientMarginCombTypeFactory::add(CWriteableClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction)
{
	pClientMarginCombType->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pClientMarginCombType,true);
	}
	else {
		CClientMarginCombType *pNewClientMarginCombType;
		pNewClientMarginCombType = internalAdd(pClientMarginCombType,false);
		pTransaction->addResource(CClientMarginCombTypeResource::alloc(CREATE_ACTION,this,pNewClientMarginCombType,NULL));
		return pNewClientMarginCombType;
	}
}

void CClientMarginCombTypeFactory::internalUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForClientMarginCombType++;
	}
	else {
		updateWithoutIndexActionForClientMarginCombType++;
	}
#endif
	CWriteableClientMarginCombType theOldClientMarginCombType;
	beforeUpdate(pClientMarginCombType,pNewClientMarginCombType);
	if (bNoTransaction) {
		forceCopy(&theOldClientMarginCombType,pClientMarginCombType,sizeof(CClientMarginCombType));
	}
	if (updateIndex) {
	}

	forceCopy(pClientMarginCombType,pNewClientMarginCombType,sizeof(CClientMarginCombType));
	pMem->updateObject(pClientMarginCombType);
	if (updateIndex) {
	}
	afterUpdate(pClientMarginCombType);
	if (bNoTransaction) {
		commitUpdate(pClientMarginCombType,&theOldClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::update(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction, bool updateIndex)
{
	pNewClientMarginCombType->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pClientMarginCombType,pNewClientMarginCombType,updateIndex,true);
	}
	else {
		pTransaction->addResource(CClientMarginCombTypeResource::alloc(UPDATE_ACTION,this,pClientMarginCombType,pNewClientMarginCombType,updateIndex));
		internalUpdate(pClientMarginCombType,pNewClientMarginCombType,updateIndex,false);
	}
}

void CClientMarginCombTypeFactory::internalRemove(CClientMarginCombType *pClientMarginCombType, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForClientMarginCombType++;
#endif
	CWriteableClientMarginCombType theOldClientMarginCombType;
	beforeRemove(pClientMarginCombType);
	if (bNoTransaction) {
		forceCopy(&theOldClientMarginCombType,pClientMarginCombType,sizeof(CClientMarginCombType));
	}
	if (runLevel>=0) {
		pClientAndInsGroupHashIndex->removeObject(pClientMarginCombType,pClientMarginCombType->HashClientAndInsGroup);
	}	
	pMem->free(pClientMarginCombType);
	if(bNoTransaction) {
		commitRemove(&theOldClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::remove(CClientMarginCombType *pClientMarginCombType, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pClientMarginCombType,true);
	}
	else {
		pTransaction->addResource(CClientMarginCombTypeResource::alloc(DELETE_ACTION,this,pClientMarginCombType,NULL));
		internalRemove(pClientMarginCombType,false);		
	}
}

CClientMarginCombType* CClientMarginCombTypeFactory::addOrUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType, CTransaction *pTransaction, bool updateIndex)
{
	if(pClientMarginCombType == NULL) {
		return add(pNewClientMarginCombType,pTransaction);
	}
	else {
		update(pClientMarginCombType,pNewClientMarginCombType,pTransaction,updateIndex);
		return pClientMarginCombType;
	}
}

void CClientMarginCombTypeFactory::retrieve(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pTargetClientMarginCombType)
{
	forceCopy(pTargetClientMarginCombType, pClientMarginCombType, sizeof(CClientMarginCombType));
}
	
int CClientMarginCombTypeFactory::addActionTrigger(CClientMarginCombTypeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CClientMarginCombTypeFactory::removeActionTrigger(CClientMarginCombTypeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CClientMarginCombTypeFactory::addCommitTrigger(CClientMarginCombTypeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CClientMarginCombTypeFactory::removeCommitTrigger(CClientMarginCombTypeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CClientMarginCombType *CClientMarginCombTypeFactory::getFirst(void)
{
	CClientMarginCombType *pResult=(CClientMarginCombType *)(pMem->getFirst());
	return pResult;
}
	
CClientMarginCombType *CClientMarginCombTypeFactory::getNext(void)
{
	CClientMarginCombType *pResult=(CClientMarginCombType *)(pMem->getNext());
	return pResult;
}
	
void CClientMarginCombTypeFactory::endGet(void)
{
	pMem->endGet();
}

void CClientMarginCombTypeFactory::beforeAdd(CWriteableClientMarginCombType *pClientMarginCombType)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pClientMarginCombType);
	}
}
	
void CClientMarginCombTypeFactory::afterAdd(CClientMarginCombType *pClientMarginCombType)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::beforeUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pNewClientMarginCombType)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pClientMarginCombType,pNewClientMarginCombType);
	}
}
	
void CClientMarginCombTypeFactory::afterUpdate(CClientMarginCombType *pClientMarginCombType)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pClientMarginCombType);
	}
}
	
void CClientMarginCombTypeFactory::beforeRemove(CClientMarginCombType *pClientMarginCombType)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::commitAdd(CClientMarginCombType *pClientMarginCombType)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForClientMarginCombType++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::commitUpdate(CClientMarginCombType *pClientMarginCombType, CWriteableClientMarginCombType *pOldClientMarginCombType)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForClientMarginCombType++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pClientMarginCombType,pOldClientMarginCombType);
	}
}
	
void CClientMarginCombTypeFactory::commitRemove(CWriteableClientMarginCombType *pClientMarginCombType)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForClientMarginCombType++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pClientMarginCombType);
	}
}

void CClientMarginCombTypeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForInstrumentGroup=0;
int updateWithIndexActionForInstrumentGroup=0;
int updateWithoutIndexActionForInstrumentGroup=0;
int removeActionForInstrumentGroup=0;
int addCommitForInstrumentGroup=0;
int updateCommitForInstrumentGroup=0;
int removeCommitForInstrumentGroup=0;
#endif
void CInstrumentGroupFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=6151;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("InstrumentGroup.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pBrokerInstrumentIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InstrumentGroup_BrokerInstrumentIDHashIndex",pBrokerInstrumentIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InstrumentGroup_BrokerInstrumentIDHashIndex");
			if(it != pIndexMap->end()) {
				pBrokerInstrumentIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrokerInstrumentIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CInstrumentGroupActionTrigger *>;
	pCommitTriggers=new vector<CInstrumentGroupCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInstrumentGroupFactory::CInstrumentGroupFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInstrumentGroup),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInstrumentGroupFactory::CInstrumentGroupFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInstrumentGroup),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInstrumentGroupFactory::~CInstrumentGroupFactory(void)
{
	if (runLevel>=0) {
		if (pBrokerInstrumentIDHashIndex!=NULL)
			delete pBrokerInstrumentIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInstrumentGroupFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInstrumentGroupFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CInstrumentGroupFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInstrumentGroup thisInstrumentGroup;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInstrumentGroup.readCSV(input,pNames))
		add(&thisInstrumentGroup);
	fclose(input);
	delete pNames;
	return 1;
}

int CInstrumentGroupFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InstrumentGroup.csv");
	return readCSV(szFileName);
}

int CInstrumentGroupFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInstrumentGroup *pInstrumentGroup;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInstrumentGroup::writeCSVHead(output);
	pInstrumentGroup=(CWriteableInstrumentGroup *)(pMem->getFirst());
	while (pInstrumentGroup!=NULL) {
		if (!pInstrumentGroup->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInstrumentGroup=(CWriteableInstrumentGroup *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInstrumentGroupFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InstrumentGroup.csv");
	return writeCSV(szFileName);
}

void CInstrumentGroupFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInstrumentGroupFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInstrumentGroup *pInstrumentGroup;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInstrumentGroupFactory={       Total Count=%d\n", pMem->getCount());
	pInstrumentGroup=(CWriteableInstrumentGroup *)(pMem->getFirst());
	while (pInstrumentGroup!=NULL) {
		pInstrumentGroup->dump(fp,index++);
		pInstrumentGroup=(CWriteableInstrumentGroup *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInstrumentGroupFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrokerInstrumentIDHashIndex->removeAll();
	}
}

CInstrumentGroup *CInstrumentGroupFactory::internalAdd(CWriteableInstrumentGroup *pInstrumentGroup, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInstrumentGroup++;
#endif
	CInstrumentGroup *pTarget;	
	beforeAdd(pInstrumentGroup);
	pTarget=(CInstrumentGroup *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InstrumentGroup in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInstrumentGroup, sizeof(CInstrumentGroup));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrokerInstrumentIDHashIndex->addObject(pTarget,pTarget->HashBrokerInstrumentID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInstrumentGroup *CInstrumentGroupFactory::add(CWriteableInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction)
{
	pInstrumentGroup->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInstrumentGroup,true);
	}
	else {
		CInstrumentGroup *pNewInstrumentGroup;
		pNewInstrumentGroup = internalAdd(pInstrumentGroup,false);
		pTransaction->addResource(CInstrumentGroupResource::alloc(CREATE_ACTION,this,pNewInstrumentGroup,NULL));
		return pNewInstrumentGroup;
	}
}

void CInstrumentGroupFactory::internalUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInstrumentGroup++;
	}
	else {
		updateWithoutIndexActionForInstrumentGroup++;
	}
#endif
	CWriteableInstrumentGroup theOldInstrumentGroup;
	beforeUpdate(pInstrumentGroup,pNewInstrumentGroup);
	if (bNoTransaction) {
		forceCopy(&theOldInstrumentGroup,pInstrumentGroup,sizeof(CInstrumentGroup));
	}
	if (updateIndex) {
	}

	forceCopy(pInstrumentGroup,pNewInstrumentGroup,sizeof(CInstrumentGroup));
	pMem->updateObject(pInstrumentGroup);
	if (updateIndex) {
	}
	afterUpdate(pInstrumentGroup);
	if (bNoTransaction) {
		commitUpdate(pInstrumentGroup,&theOldInstrumentGroup);
	}
}

void CInstrumentGroupFactory::update(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction, bool updateIndex)
{
	pNewInstrumentGroup->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInstrumentGroup,pNewInstrumentGroup,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInstrumentGroupResource::alloc(UPDATE_ACTION,this,pInstrumentGroup,pNewInstrumentGroup,updateIndex));
		internalUpdate(pInstrumentGroup,pNewInstrumentGroup,updateIndex,false);
	}
}

void CInstrumentGroupFactory::internalRemove(CInstrumentGroup *pInstrumentGroup, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInstrumentGroup++;
#endif
	CWriteableInstrumentGroup theOldInstrumentGroup;
	beforeRemove(pInstrumentGroup);
	if (bNoTransaction) {
		forceCopy(&theOldInstrumentGroup,pInstrumentGroup,sizeof(CInstrumentGroup));
	}
	if (runLevel>=0) {
		pBrokerInstrumentIDHashIndex->removeObject(pInstrumentGroup,pInstrumentGroup->HashBrokerInstrumentID);
	}	
	pMem->free(pInstrumentGroup);
	if(bNoTransaction) {
		commitRemove(&theOldInstrumentGroup);
	}
}

void CInstrumentGroupFactory::remove(CInstrumentGroup *pInstrumentGroup, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInstrumentGroup,true);
	}
	else {
		pTransaction->addResource(CInstrumentGroupResource::alloc(DELETE_ACTION,this,pInstrumentGroup,NULL));
		internalRemove(pInstrumentGroup,false);		
	}
}

CInstrumentGroup* CInstrumentGroupFactory::addOrUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup, CTransaction *pTransaction, bool updateIndex)
{
	if(pInstrumentGroup == NULL) {
		return add(pNewInstrumentGroup,pTransaction);
	}
	else {
		update(pInstrumentGroup,pNewInstrumentGroup,pTransaction,updateIndex);
		return pInstrumentGroup;
	}
}

void CInstrumentGroupFactory::retrieve(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pTargetInstrumentGroup)
{
	forceCopy(pTargetInstrumentGroup, pInstrumentGroup, sizeof(CInstrumentGroup));
}
	
int CInstrumentGroupFactory::addActionTrigger(CInstrumentGroupActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInstrumentGroupFactory::removeActionTrigger(CInstrumentGroupActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInstrumentGroupFactory::addCommitTrigger(CInstrumentGroupCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInstrumentGroupFactory::removeCommitTrigger(CInstrumentGroupCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInstrumentGroup *CInstrumentGroupFactory::getFirst(void)
{
	CInstrumentGroup *pResult=(CInstrumentGroup *)(pMem->getFirst());
	return pResult;
}
	
CInstrumentGroup *CInstrumentGroupFactory::getNext(void)
{
	CInstrumentGroup *pResult=(CInstrumentGroup *)(pMem->getNext());
	return pResult;
}
	
void CInstrumentGroupFactory::endGet(void)
{
	pMem->endGet();
}

void CInstrumentGroupFactory::beforeAdd(CWriteableInstrumentGroup *pInstrumentGroup)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInstrumentGroup);
	}
}
	
void CInstrumentGroupFactory::afterAdd(CInstrumentGroup *pInstrumentGroup)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInstrumentGroup);
	}
}

void CInstrumentGroupFactory::beforeUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pNewInstrumentGroup)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInstrumentGroup,pNewInstrumentGroup);
	}
}
	
void CInstrumentGroupFactory::afterUpdate(CInstrumentGroup *pInstrumentGroup)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInstrumentGroup);
	}
}
	
void CInstrumentGroupFactory::beforeRemove(CInstrumentGroup *pInstrumentGroup)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInstrumentGroup);
	}
}

void CInstrumentGroupFactory::commitAdd(CInstrumentGroup *pInstrumentGroup)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInstrumentGroup++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInstrumentGroup);
	}
}

void CInstrumentGroupFactory::commitUpdate(CInstrumentGroup *pInstrumentGroup, CWriteableInstrumentGroup *pOldInstrumentGroup)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInstrumentGroup++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInstrumentGroup,pOldInstrumentGroup);
	}
}
	
void CInstrumentGroupFactory::commitRemove(CWriteableInstrumentGroup *pInstrumentGroup)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInstrumentGroup++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInstrumentGroup);
	}
}

void CInstrumentGroupFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForTradeDateInstrumentIDIndexinSGEDeferRate(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForSGEDeferRate=0;
int updateWithIndexActionForSGEDeferRate=0;
int updateWithoutIndexActionForSGEDeferRate=0;
int removeActionForSGEDeferRate=0;
int addCommitForSGEDeferRate=0;
int updateCommitForSGEDeferRate=0;
int removeCommitForSGEDeferRate=0;
#endif
void CSGEDeferRateFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pTradeDateInstrumentIDIndex=new CAVLTree(maxUnit,compareForTradeDateInstrumentIDIndexinSGEDeferRate,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("SGEDeferRate_TradeDateInstrumentIDIndex",pTradeDateInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("SGEDeferRate_TradeDateInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pTradeDateInstrumentIDIndex=new CAVLTree(maxUnit,compareForTradeDateInstrumentIDIndexinSGEDeferRate,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pTradeDateInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAllByInstrumentID=NULL;
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CSGEDeferRateActionTrigger *>;
	pCommitTriggers=new vector<CSGEDeferRateCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CSGEDeferRateFactory::CSGEDeferRateFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSGEDeferRate),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CSGEDeferRateFactory::CSGEDeferRateFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSGEDeferRate),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CSGEDeferRateFactory::~CSGEDeferRateFactory(void)
{
	if (runLevel>=0) {
		if (pTradeDateInstrumentIDIndex!=NULL)
			delete pTradeDateInstrumentIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CSGEDeferRateFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSGEDeferRateFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pTradeDateInstrumentIDIndex->output(pLogger,indent+1);
	}
}

int CSGEDeferRateFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableSGEDeferRate thisSGEDeferRate;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisSGEDeferRate.readCSV(input,pNames))
		add(&thisSGEDeferRate);
	fclose(input);
	delete pNames;
	return 1;
}

int CSGEDeferRateFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "SGEDeferRate.csv");
	return readCSV(szFileName);
}

int CSGEDeferRateFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableSGEDeferRate *pSGEDeferRate;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableSGEDeferRate::writeCSVHead(output);
	pSGEDeferRate=(CWriteableSGEDeferRate *)(pMem->getFirst());
	while (pSGEDeferRate!=NULL) {
		if (!pSGEDeferRate->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pSGEDeferRate=(CWriteableSGEDeferRate *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CSGEDeferRateFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SGEDeferRate.csv");
	return writeCSV(szFileName);
}

void CSGEDeferRateFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CSGEDeferRateFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableSGEDeferRate *pSGEDeferRate;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CSGEDeferRateFactory={       Total Count=%d\n", pMem->getCount());
	pSGEDeferRate=(CWriteableSGEDeferRate *)(pMem->getFirst());
	while (pSGEDeferRate!=NULL) {
		pSGEDeferRate->dump(fp,index++);
		pSGEDeferRate=(CWriteableSGEDeferRate *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CSGEDeferRateFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pTradeDateInstrumentIDIndex->removeAll();
	}
}

CSGEDeferRate *CSGEDeferRateFactory::internalAdd(CWriteableSGEDeferRate *pSGEDeferRate, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForSGEDeferRate++;
#endif
	CSGEDeferRate *pTarget;	
	beforeAdd(pSGEDeferRate);
	pTarget=(CSGEDeferRate *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough SGEDeferRate in memory database");
		return NULL;
	}
	forceCopy(pTarget, pSGEDeferRate, sizeof(CSGEDeferRate));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pTradeDateInstrumentIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CSGEDeferRate *CSGEDeferRateFactory::add(CWriteableSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction)
{
	pSGEDeferRate->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pSGEDeferRate,true);
	}
	else {
		CSGEDeferRate *pNewSGEDeferRate;
		pNewSGEDeferRate = internalAdd(pSGEDeferRate,false);
		pTransaction->addResource(CSGEDeferRateResource::alloc(CREATE_ACTION,this,pNewSGEDeferRate,NULL));
		return pNewSGEDeferRate;
	}
}

void CSGEDeferRateFactory::internalUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForSGEDeferRate++;
	}
	else {
		updateWithoutIndexActionForSGEDeferRate++;
	}
#endif
	CWriteableSGEDeferRate theOldSGEDeferRate;
	beforeUpdate(pSGEDeferRate,pNewSGEDeferRate);
	if (bNoTransaction) {
		forceCopy(&theOldSGEDeferRate,pSGEDeferRate,sizeof(CSGEDeferRate));
	}
	if (updateIndex) {
	}

	forceCopy(pSGEDeferRate,pNewSGEDeferRate,sizeof(CSGEDeferRate));
	pMem->updateObject(pSGEDeferRate);
	if (updateIndex) {
	}
	afterUpdate(pSGEDeferRate);
	if (bNoTransaction) {
		commitUpdate(pSGEDeferRate,&theOldSGEDeferRate);
	}
}

void CSGEDeferRateFactory::update(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction, bool updateIndex)
{
	pNewSGEDeferRate->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pSGEDeferRate,pNewSGEDeferRate,updateIndex,true);
	}
	else {
		pTransaction->addResource(CSGEDeferRateResource::alloc(UPDATE_ACTION,this,pSGEDeferRate,pNewSGEDeferRate,updateIndex));
		internalUpdate(pSGEDeferRate,pNewSGEDeferRate,updateIndex,false);
	}
}

void CSGEDeferRateFactory::internalRemove(CSGEDeferRate *pSGEDeferRate, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForSGEDeferRate++;
#endif
	CWriteableSGEDeferRate theOldSGEDeferRate;
	beforeRemove(pSGEDeferRate);
	if (bNoTransaction) {
		forceCopy(&theOldSGEDeferRate,pSGEDeferRate,sizeof(CSGEDeferRate));
	}
	if (runLevel>=0) {
		pTradeDateInstrumentIDIndex->removeObject(pSGEDeferRate);
	}
	pMem->free(pSGEDeferRate);
	if(bNoTransaction) {
		commitRemove(&theOldSGEDeferRate);
	}
}

void CSGEDeferRateFactory::remove(CSGEDeferRate *pSGEDeferRate, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pSGEDeferRate,true);
	}
	else {
		pTransaction->addResource(CSGEDeferRateResource::alloc(DELETE_ACTION,this,pSGEDeferRate,NULL));
		internalRemove(pSGEDeferRate,false);		
	}
}

CSGEDeferRate* CSGEDeferRateFactory::addOrUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate, CTransaction *pTransaction, bool updateIndex)
{
	if(pSGEDeferRate == NULL) {
		return add(pNewSGEDeferRate,pTransaction);
	}
	else {
		update(pSGEDeferRate,pNewSGEDeferRate,pTransaction,updateIndex);
		return pSGEDeferRate;
	}
}

void CSGEDeferRateFactory::retrieve(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pTargetSGEDeferRate)
{
	forceCopy(pTargetSGEDeferRate, pSGEDeferRate, sizeof(CSGEDeferRate));
}
	
int CSGEDeferRateFactory::addActionTrigger(CSGEDeferRateActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CSGEDeferRateFactory::removeActionTrigger(CSGEDeferRateActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CSGEDeferRateFactory::addCommitTrigger(CSGEDeferRateCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CSGEDeferRateFactory::removeCommitTrigger(CSGEDeferRateCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CSGEDeferRate *CSGEDeferRateFactory::getFirst(void)
{
	CSGEDeferRate *pResult=(CSGEDeferRate *)(pMem->getFirst());
	return pResult;
}
	
CSGEDeferRate *CSGEDeferRateFactory::getNext(void)
{
	CSGEDeferRate *pResult=(CSGEDeferRate *)(pMem->getNext());
	return pResult;
}
	
void CSGEDeferRateFactory::endGet(void)
{
	pMem->endGet();
}

void CSGEDeferRateFactory::beforeAdd(CWriteableSGEDeferRate *pSGEDeferRate)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pSGEDeferRate);
	}
}
	
void CSGEDeferRateFactory::afterAdd(CSGEDeferRate *pSGEDeferRate)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pSGEDeferRate);
	}
}

void CSGEDeferRateFactory::beforeUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pNewSGEDeferRate)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pSGEDeferRate,pNewSGEDeferRate);
	}
}
	
void CSGEDeferRateFactory::afterUpdate(CSGEDeferRate *pSGEDeferRate)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pSGEDeferRate);
	}
}
	
void CSGEDeferRateFactory::beforeRemove(CSGEDeferRate *pSGEDeferRate)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pSGEDeferRate);
	}
}

void CSGEDeferRateFactory::commitAdd(CSGEDeferRate *pSGEDeferRate)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForSGEDeferRate++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pSGEDeferRate);
	}
}

void CSGEDeferRateFactory::commitUpdate(CSGEDeferRate *pSGEDeferRate, CWriteableSGEDeferRate *pOldSGEDeferRate)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForSGEDeferRate++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pSGEDeferRate,pOldSGEDeferRate);
	}
}
	
void CSGEDeferRateFactory::commitRemove(CWriteableSGEDeferRate *pSGEDeferRate)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForSGEDeferRate++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pSGEDeferRate);
	}
}

void CSGEDeferRateFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForBrkExIDInsInvIndexinInvestorTradingRight(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForInvestorTradingRight=0;
int updateWithIndexActionForInvestorTradingRight=0;
int updateWithoutIndexActionForInvestorTradingRight=0;
int removeActionForInvestorTradingRight=0;
int addCommitForInvestorTradingRight=0;
int updateCommitForInvestorTradingRight=0;
int removeCommitForInvestorTradingRight=0;
#endif
void CInvestorTradingRightFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pBrkExIDInsInvIndex=new CAVLTree(maxUnit,compareForBrkExIDInsInvIndexinInvestorTradingRight,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorTradingRight_BrkExIDInsInvIndex",pBrkExIDInsInvIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorTradingRight_BrkExIDInsInvIndex");
			if(it != pIndexMap->end()) {
				pBrkExIDInsInvIndex=new CAVLTree(maxUnit,compareForBrkExIDInsInvIndexinInvestorTradingRight,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkExIDInsInvIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CInvestorTradingRightActionTrigger *>;
	pCommitTriggers=new vector<CInvestorTradingRightCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorTradingRightFactory::CInvestorTradingRightFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorTradingRight),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorTradingRightFactory::CInvestorTradingRightFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorTradingRight),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorTradingRightFactory::~CInvestorTradingRightFactory(void)
{
	if (runLevel>=0) {
		if (pBrkExIDInsInvIndex!=NULL)
			delete pBrkExIDInsInvIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorTradingRightFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorTradingRightFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pBrkExIDInsInvIndex->output(pLogger,indent+1);
	}
}

int CInvestorTradingRightFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorTradingRight thisInvestorTradingRight;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorTradingRight.readCSV(input,pNames))
		add(&thisInvestorTradingRight);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorTradingRightFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorTradingRight.csv");
	return readCSV(szFileName);
}

int CInvestorTradingRightFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorTradingRight *pInvestorTradingRight;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorTradingRight::writeCSVHead(output);
	pInvestorTradingRight=(CWriteableInvestorTradingRight *)(pMem->getFirst());
	while (pInvestorTradingRight!=NULL) {
		if (!pInvestorTradingRight->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorTradingRight=(CWriteableInvestorTradingRight *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorTradingRightFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorTradingRight.csv");
	return writeCSV(szFileName);
}

void CInvestorTradingRightFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorTradingRightFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorTradingRight *pInvestorTradingRight;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorTradingRightFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorTradingRight=(CWriteableInvestorTradingRight *)(pMem->getFirst());
	while (pInvestorTradingRight!=NULL) {
		pInvestorTradingRight->dump(fp,index++);
		pInvestorTradingRight=(CWriteableInvestorTradingRight *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorTradingRightFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrkExIDInsInvIndex->removeAll();
	}
}

CInvestorTradingRight *CInvestorTradingRightFactory::internalAdd(CWriteableInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorTradingRight++;
#endif
	CInvestorTradingRight *pTarget;	
	beforeAdd(pInvestorTradingRight);
	pTarget=(CInvestorTradingRight *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorTradingRight in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorTradingRight, sizeof(CInvestorTradingRight));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrkExIDInsInvIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorTradingRight *CInvestorTradingRightFactory::add(CWriteableInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction)
{
	pInvestorTradingRight->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorTradingRight,true);
	}
	else {
		CInvestorTradingRight *pNewInvestorTradingRight;
		pNewInvestorTradingRight = internalAdd(pInvestorTradingRight,false);
		pTransaction->addResource(CInvestorTradingRightResource::alloc(CREATE_ACTION,this,pNewInvestorTradingRight,NULL));
		return pNewInvestorTradingRight;
	}
}

void CInvestorTradingRightFactory::internalUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorTradingRight++;
	}
	else {
		updateWithoutIndexActionForInvestorTradingRight++;
	}
#endif
	CWriteableInvestorTradingRight theOldInvestorTradingRight;
	beforeUpdate(pInvestorTradingRight,pNewInvestorTradingRight);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorTradingRight,pInvestorTradingRight,sizeof(CInvestorTradingRight));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorTradingRight,pNewInvestorTradingRight,sizeof(CInvestorTradingRight));
	pMem->updateObject(pInvestorTradingRight);
	if (updateIndex) {
	}
	afterUpdate(pInvestorTradingRight);
	if (bNoTransaction) {
		commitUpdate(pInvestorTradingRight,&theOldInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::update(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorTradingRight->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorTradingRight,pNewInvestorTradingRight,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorTradingRightResource::alloc(UPDATE_ACTION,this,pInvestorTradingRight,pNewInvestorTradingRight,updateIndex));
		internalUpdate(pInvestorTradingRight,pNewInvestorTradingRight,updateIndex,false);
	}
}

void CInvestorTradingRightFactory::internalRemove(CInvestorTradingRight *pInvestorTradingRight, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorTradingRight++;
#endif
	CWriteableInvestorTradingRight theOldInvestorTradingRight;
	beforeRemove(pInvestorTradingRight);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorTradingRight,pInvestorTradingRight,sizeof(CInvestorTradingRight));
	}
	if (runLevel>=0) {
		pBrkExIDInsInvIndex->removeObject(pInvestorTradingRight);
	}
	pMem->free(pInvestorTradingRight);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::remove(CInvestorTradingRight *pInvestorTradingRight, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorTradingRight,true);
	}
	else {
		pTransaction->addResource(CInvestorTradingRightResource::alloc(DELETE_ACTION,this,pInvestorTradingRight,NULL));
		internalRemove(pInvestorTradingRight,false);		
	}
}

CInvestorTradingRight* CInvestorTradingRightFactory::addOrUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorTradingRight == NULL) {
		return add(pNewInvestorTradingRight,pTransaction);
	}
	else {
		update(pInvestorTradingRight,pNewInvestorTradingRight,pTransaction,updateIndex);
		return pInvestorTradingRight;
	}
}

void CInvestorTradingRightFactory::retrieve(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pTargetInvestorTradingRight)
{
	forceCopy(pTargetInvestorTradingRight, pInvestorTradingRight, sizeof(CInvestorTradingRight));
}
	
int CInvestorTradingRightFactory::addActionTrigger(CInvestorTradingRightActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorTradingRightFactory::removeActionTrigger(CInvestorTradingRightActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorTradingRightFactory::addCommitTrigger(CInvestorTradingRightCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorTradingRightFactory::removeCommitTrigger(CInvestorTradingRightCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorTradingRight *CInvestorTradingRightFactory::getFirst(void)
{
	CInvestorTradingRight *pResult=(CInvestorTradingRight *)(pMem->getFirst());
	return pResult;
}
	
CInvestorTradingRight *CInvestorTradingRightFactory::getNext(void)
{
	CInvestorTradingRight *pResult=(CInvestorTradingRight *)(pMem->getNext());
	return pResult;
}
	
void CInvestorTradingRightFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorTradingRightFactory::beforeAdd(CWriteableInvestorTradingRight *pInvestorTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorTradingRight);
	}
}
	
void CInvestorTradingRightFactory::afterAdd(CInvestorTradingRight *pInvestorTradingRight)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::beforeUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pNewInvestorTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorTradingRight,pNewInvestorTradingRight);
	}
}
	
void CInvestorTradingRightFactory::afterUpdate(CInvestorTradingRight *pInvestorTradingRight)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorTradingRight);
	}
}
	
void CInvestorTradingRightFactory::beforeRemove(CInvestorTradingRight *pInvestorTradingRight)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::commitAdd(CInvestorTradingRight *pInvestorTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::commitUpdate(CInvestorTradingRight *pInvestorTradingRight, CWriteableInvestorTradingRight *pOldInvestorTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorTradingRight,pOldInvestorTradingRight);
	}
}
	
void CInvestorTradingRightFactory::commitRemove(CWriteableInvestorTradingRight *pInvestorTradingRight)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorTradingRight++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorTradingRight);
	}
}

void CInvestorTradingRightFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForUserIPMaskIndexinUserIP(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForUserIP=0;
int updateWithIndexActionForUserIP=0;
int updateWithoutIndexActionForUserIP=0;
int removeActionForUserIP=0;
int addCommitForUserIP=0;
int updateCommitForUserIP=0;
int removeCommitForUserIP=0;
#endif
void CUserIPFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pUserIPMaskIndex=new CAVLTree(maxUnit,compareForUserIPMaskIndexinUserIP,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("UserIP_UserIPMaskIndex",pUserIPMaskIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("UserIP_UserIPMaskIndex");
			if(it != pIndexMap->end()) {
				pUserIPMaskIndex=new CAVLTree(maxUnit,compareForUserIPMaskIndexinUserIP,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pUserIPMaskIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchByUserID=NULL;
	pActionTriggers=new vector<CUserIPActionTrigger *>;
	pCommitTriggers=new vector<CUserIPCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CUserIPFactory::CUserIPFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserIP),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CUserIPFactory::CUserIPFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CUserIP),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CUserIPFactory::~CUserIPFactory(void)
{
	if (runLevel>=0) {
		if (pUserIPMaskIndex!=NULL)
			delete pUserIPMaskIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CUserIPFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CUserIPFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pUserIPMaskIndex->output(pLogger,indent+1);
	}
}

int CUserIPFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableUserIP thisUserIP;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisUserIP.readCSV(input,pNames))
		add(&thisUserIP);
	fclose(input);
	delete pNames;
	return 1;
}

int CUserIPFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "UserIP.csv");
	return readCSV(szFileName);
}

int CUserIPFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableUserIP *pUserIP;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableUserIP::writeCSVHead(output);
	pUserIP=(CWriteableUserIP *)(pMem->getFirst());
	while (pUserIP!=NULL) {
		if (!pUserIP->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pUserIP=(CWriteableUserIP *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CUserIPFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "UserIP.csv");
	return writeCSV(szFileName);
}

void CUserIPFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CUserIPFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableUserIP *pUserIP;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CUserIPFactory={       Total Count=%d\n", pMem->getCount());
	pUserIP=(CWriteableUserIP *)(pMem->getFirst());
	while (pUserIP!=NULL) {
		pUserIP->dump(fp,index++);
		pUserIP=(CWriteableUserIP *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CUserIPFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pUserIPMaskIndex->removeAll();
	}
}

CUserIP *CUserIPFactory::internalAdd(CWriteableUserIP *pUserIP, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForUserIP++;
#endif
	CUserIP *pTarget;	
	beforeAdd(pUserIP);
	pTarget=(CUserIP *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough UserIP in memory database");
		return NULL;
	}
	forceCopy(pTarget, pUserIP, sizeof(CUserIP));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pUserIPMaskIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CUserIP *CUserIPFactory::add(CWriteableUserIP *pUserIP, CTransaction *pTransaction)
{
	pUserIP->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pUserIP,true);
	}
	else {
		CUserIP *pNewUserIP;
		pNewUserIP = internalAdd(pUserIP,false);
		pTransaction->addResource(CUserIPResource::alloc(CREATE_ACTION,this,pNewUserIP,NULL));
		return pNewUserIP;
	}
}

void CUserIPFactory::internalUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForUserIP++;
	}
	else {
		updateWithoutIndexActionForUserIP++;
	}
#endif
	CWriteableUserIP theOldUserIP;
	beforeUpdate(pUserIP,pNewUserIP);
	if (bNoTransaction) {
		forceCopy(&theOldUserIP,pUserIP,sizeof(CUserIP));
	}
	if (updateIndex) {
	}

	forceCopy(pUserIP,pNewUserIP,sizeof(CUserIP));
	pMem->updateObject(pUserIP);
	if (updateIndex) {
	}
	afterUpdate(pUserIP);
	if (bNoTransaction) {
		commitUpdate(pUserIP,&theOldUserIP);
	}
}

void CUserIPFactory::update(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction, bool updateIndex)
{
	pNewUserIP->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pUserIP,pNewUserIP,updateIndex,true);
	}
	else {
		pTransaction->addResource(CUserIPResource::alloc(UPDATE_ACTION,this,pUserIP,pNewUserIP,updateIndex));
		internalUpdate(pUserIP,pNewUserIP,updateIndex,false);
	}
}

void CUserIPFactory::internalRemove(CUserIP *pUserIP, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForUserIP++;
#endif
	CWriteableUserIP theOldUserIP;
	beforeRemove(pUserIP);
	if (bNoTransaction) {
		forceCopy(&theOldUserIP,pUserIP,sizeof(CUserIP));
	}
	if (runLevel>=0) {
		pUserIPMaskIndex->removeObject(pUserIP);
	}
	pMem->free(pUserIP);
	if(bNoTransaction) {
		commitRemove(&theOldUserIP);
	}
}

void CUserIPFactory::remove(CUserIP *pUserIP, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pUserIP,true);
	}
	else {
		pTransaction->addResource(CUserIPResource::alloc(DELETE_ACTION,this,pUserIP,NULL));
		internalRemove(pUserIP,false);		
	}
}

CUserIP* CUserIPFactory::addOrUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP, CTransaction *pTransaction, bool updateIndex)
{
	if(pUserIP == NULL) {
		return add(pNewUserIP,pTransaction);
	}
	else {
		update(pUserIP,pNewUserIP,pTransaction,updateIndex);
		return pUserIP;
	}
}

void CUserIPFactory::retrieve(CUserIP *pUserIP, CWriteableUserIP *pTargetUserIP)
{
	forceCopy(pTargetUserIP, pUserIP, sizeof(CUserIP));
}
	
int CUserIPFactory::addActionTrigger(CUserIPActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CUserIPFactory::removeActionTrigger(CUserIPActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CUserIPFactory::addCommitTrigger(CUserIPCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CUserIPFactory::removeCommitTrigger(CUserIPCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CUserIP *CUserIPFactory::getFirst(void)
{
	CUserIP *pResult=(CUserIP *)(pMem->getFirst());
	return pResult;
}
	
CUserIP *CUserIPFactory::getNext(void)
{
	CUserIP *pResult=(CUserIP *)(pMem->getNext());
	return pResult;
}
	
void CUserIPFactory::endGet(void)
{
	pMem->endGet();
}

void CUserIPFactory::beforeAdd(CWriteableUserIP *pUserIP)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pUserIP);
	}
}
	
void CUserIPFactory::afterAdd(CUserIP *pUserIP)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pUserIP);
	}
}

void CUserIPFactory::beforeUpdate(CUserIP *pUserIP, CWriteableUserIP *pNewUserIP)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pUserIP,pNewUserIP);
	}
}
	
void CUserIPFactory::afterUpdate(CUserIP *pUserIP)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pUserIP);
	}
}
	
void CUserIPFactory::beforeRemove(CUserIP *pUserIP)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pUserIP);
	}
}

void CUserIPFactory::commitAdd(CUserIP *pUserIP)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForUserIP++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pUserIP);
	}
}

void CUserIPFactory::commitUpdate(CUserIP *pUserIP, CWriteableUserIP *pOldUserIP)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForUserIP++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pUserIP,pOldUserIP);
	}
}
	
void CUserIPFactory::commitRemove(CWriteableUserIP *pUserIP)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForUserIP++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pUserIP);
	}
}

void CUserIPFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForInvestorOptionFee=0;
int updateWithIndexActionForInvestorOptionFee=0;
int updateWithoutIndexActionForInvestorOptionFee=0;
int removeActionForInvestorOptionFee=0;
int addCommitForInvestorOptionFee=0;
int updateCommitForInvestorOptionFee=0;
int removeCommitForInvestorOptionFee=0;
#endif
void CInvestorOptionFeeFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		int hashKeySize=6151;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("InvestorOptionFee.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			pBrkIDExIDIstIDVstIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("InvestorOptionFee_BrkIDExIDIstIDVstIDHashIndex",pBrkIDExIDIstIDVstIDHashIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("InvestorOptionFee_BrkIDExIDIstIDVstIDHashIndex");
			if(it != pIndexMap->end()) {
				pBrkIDExIDIstIDVstIDHashIndex=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pBrkIDExIDIstIDVstIDHashIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CInvestorOptionFeeActionTrigger *>;
	pCommitTriggers=new vector<CInvestorOptionFeeCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CInvestorOptionFeeFactory::CInvestorOptionFeeFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorOptionFee),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CInvestorOptionFeeFactory::CInvestorOptionFeeFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CInvestorOptionFee),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CInvestorOptionFeeFactory::~CInvestorOptionFeeFactory(void)
{
	if (runLevel>=0) {
		if (pBrkIDExIDIstIDVstIDHashIndex!=NULL)
			delete pBrkIDExIDIstIDVstIDHashIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CInvestorOptionFeeFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CInvestorOptionFeeFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int CInvestorOptionFeeFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableInvestorOptionFee thisInvestorOptionFee;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisInvestorOptionFee.readCSV(input,pNames))
		add(&thisInvestorOptionFee);
	fclose(input);
	delete pNames;
	return 1;
}

int CInvestorOptionFeeFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "InvestorOptionFee.csv");
	return readCSV(szFileName);
}

int CInvestorOptionFeeFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableInvestorOptionFee *pInvestorOptionFee;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableInvestorOptionFee::writeCSVHead(output);
	pInvestorOptionFee=(CWriteableInvestorOptionFee *)(pMem->getFirst());
	while (pInvestorOptionFee!=NULL) {
		if (!pInvestorOptionFee->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pInvestorOptionFee=(CWriteableInvestorOptionFee *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CInvestorOptionFeeFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "InvestorOptionFee.csv");
	return writeCSV(szFileName);
}

void CInvestorOptionFeeFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CInvestorOptionFeeFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableInvestorOptionFee *pInvestorOptionFee;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CInvestorOptionFeeFactory={       Total Count=%d\n", pMem->getCount());
	pInvestorOptionFee=(CWriteableInvestorOptionFee *)(pMem->getFirst());
	while (pInvestorOptionFee!=NULL) {
		pInvestorOptionFee->dump(fp,index++);
		pInvestorOptionFee=(CWriteableInvestorOptionFee *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CInvestorOptionFeeFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHashIndex->removeAll();
	}
}

CInvestorOptionFee *CInvestorOptionFeeFactory::internalAdd(CWriteableInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForInvestorOptionFee++;
#endif
	CInvestorOptionFee *pTarget;	
	beforeAdd(pInvestorOptionFee);
	pTarget=(CInvestorOptionFee *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough InvestorOptionFee in memory database");
		return NULL;
	}
	forceCopy(pTarget, pInvestorOptionFee, sizeof(CInvestorOptionFee));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHashIndex->addObject(pTarget,pTarget->HashBrkIDExIDIstIDVstID);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CInvestorOptionFee *CInvestorOptionFeeFactory::add(CWriteableInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction)
{
	pInvestorOptionFee->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pInvestorOptionFee,true);
	}
	else {
		CInvestorOptionFee *pNewInvestorOptionFee;
		pNewInvestorOptionFee = internalAdd(pInvestorOptionFee,false);
		pTransaction->addResource(CInvestorOptionFeeResource::alloc(CREATE_ACTION,this,pNewInvestorOptionFee,NULL));
		return pNewInvestorOptionFee;
	}
}

void CInvestorOptionFeeFactory::internalUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForInvestorOptionFee++;
	}
	else {
		updateWithoutIndexActionForInvestorOptionFee++;
	}
#endif
	CWriteableInvestorOptionFee theOldInvestorOptionFee;
	beforeUpdate(pInvestorOptionFee,pNewInvestorOptionFee);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorOptionFee,pInvestorOptionFee,sizeof(CInvestorOptionFee));
	}
	if (updateIndex) {
	}

	forceCopy(pInvestorOptionFee,pNewInvestorOptionFee,sizeof(CInvestorOptionFee));
	pMem->updateObject(pInvestorOptionFee);
	if (updateIndex) {
	}
	afterUpdate(pInvestorOptionFee);
	if (bNoTransaction) {
		commitUpdate(pInvestorOptionFee,&theOldInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::update(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction, bool updateIndex)
{
	pNewInvestorOptionFee->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pInvestorOptionFee,pNewInvestorOptionFee,updateIndex,true);
	}
	else {
		pTransaction->addResource(CInvestorOptionFeeResource::alloc(UPDATE_ACTION,this,pInvestorOptionFee,pNewInvestorOptionFee,updateIndex));
		internalUpdate(pInvestorOptionFee,pNewInvestorOptionFee,updateIndex,false);
	}
}

void CInvestorOptionFeeFactory::internalRemove(CInvestorOptionFee *pInvestorOptionFee, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForInvestorOptionFee++;
#endif
	CWriteableInvestorOptionFee theOldInvestorOptionFee;
	beforeRemove(pInvestorOptionFee);
	if (bNoTransaction) {
		forceCopy(&theOldInvestorOptionFee,pInvestorOptionFee,sizeof(CInvestorOptionFee));
	}
	if (runLevel>=0) {
		pBrkIDExIDIstIDVstIDHashIndex->removeObject(pInvestorOptionFee,pInvestorOptionFee->HashBrkIDExIDIstIDVstID);
	}	
	pMem->free(pInvestorOptionFee);
	if(bNoTransaction) {
		commitRemove(&theOldInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::remove(CInvestorOptionFee *pInvestorOptionFee, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pInvestorOptionFee,true);
	}
	else {
		pTransaction->addResource(CInvestorOptionFeeResource::alloc(DELETE_ACTION,this,pInvestorOptionFee,NULL));
		internalRemove(pInvestorOptionFee,false);		
	}
}

CInvestorOptionFee* CInvestorOptionFeeFactory::addOrUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee, CTransaction *pTransaction, bool updateIndex)
{
	if(pInvestorOptionFee == NULL) {
		return add(pNewInvestorOptionFee,pTransaction);
	}
	else {
		update(pInvestorOptionFee,pNewInvestorOptionFee,pTransaction,updateIndex);
		return pInvestorOptionFee;
	}
}

void CInvestorOptionFeeFactory::retrieve(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pTargetInvestorOptionFee)
{
	forceCopy(pTargetInvestorOptionFee, pInvestorOptionFee, sizeof(CInvestorOptionFee));
}
	
int CInvestorOptionFeeFactory::addActionTrigger(CInvestorOptionFeeActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CInvestorOptionFeeFactory::removeActionTrigger(CInvestorOptionFeeActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CInvestorOptionFeeFactory::addCommitTrigger(CInvestorOptionFeeCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CInvestorOptionFeeFactory::removeCommitTrigger(CInvestorOptionFeeCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CInvestorOptionFee *CInvestorOptionFeeFactory::getFirst(void)
{
	CInvestorOptionFee *pResult=(CInvestorOptionFee *)(pMem->getFirst());
	return pResult;
}
	
CInvestorOptionFee *CInvestorOptionFeeFactory::getNext(void)
{
	CInvestorOptionFee *pResult=(CInvestorOptionFee *)(pMem->getNext());
	return pResult;
}
	
void CInvestorOptionFeeFactory::endGet(void)
{
	pMem->endGet();
}

void CInvestorOptionFeeFactory::beforeAdd(CWriteableInvestorOptionFee *pInvestorOptionFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pInvestorOptionFee);
	}
}
	
void CInvestorOptionFeeFactory::afterAdd(CInvestorOptionFee *pInvestorOptionFee)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::beforeUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pNewInvestorOptionFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pInvestorOptionFee,pNewInvestorOptionFee);
	}
}
	
void CInvestorOptionFeeFactory::afterUpdate(CInvestorOptionFee *pInvestorOptionFee)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pInvestorOptionFee);
	}
}
	
void CInvestorOptionFeeFactory::beforeRemove(CInvestorOptionFee *pInvestorOptionFee)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::commitAdd(CInvestorOptionFee *pInvestorOptionFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForInvestorOptionFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::commitUpdate(CInvestorOptionFee *pInvestorOptionFee, CWriteableInvestorOptionFee *pOldInvestorOptionFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForInvestorOptionFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pInvestorOptionFee,pOldInvestorOptionFee);
	}
}
	
void CInvestorOptionFeeFactory::commitRemove(CWriteableInvestorOptionFee *pInvestorOptionFee)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForInvestorOptionFee++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pInvestorOptionFee);
	}
}

void CInvestorOptionFeeFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForExchangeIDAndInstrumentIDIndexinMarketData(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForMarketData=0;
int updateWithIndexActionForMarketData=0;
int updateWithoutIndexActionForMarketData=0;
int removeActionForMarketData=0;
int addCommitForMarketData=0;
int updateCommitForMarketData=0;
int removeCommitForMarketData=0;
#endif
void CMarketDataFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pExchangeIDAndInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDAndInstrumentIDIndexinMarketData,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("MarketData_ExchangeIDAndInstrumentIDIndex",pExchangeIDAndInstrumentIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("MarketData_ExchangeIDAndInstrumentIDIndex");
			if(it != pIndexMap->end()) {
				pExchangeIDAndInstrumentIDIndex=new CAVLTree(maxUnit,compareForExchangeIDAndInstrumentIDIndexinMarketData,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pExchangeIDAndInstrumentIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pLastFoundInSearchAll=NULL;
	pActionTriggers=new vector<CMarketDataActionTrigger *>;
	pCommitTriggers=new vector<CMarketDataCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CMarketDataFactory::CMarketDataFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CMarketData),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CMarketDataFactory::CMarketDataFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CMarketData),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CMarketDataFactory::~CMarketDataFactory(void)
{
	if (runLevel>=0) {
		if (pExchangeIDAndInstrumentIDIndex!=NULL)
			delete pExchangeIDAndInstrumentIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CMarketDataFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CMarketDataFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pExchangeIDAndInstrumentIDIndex->output(pLogger,indent+1);
	}
}

int CMarketDataFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableMarketData thisMarketData;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisMarketData.readCSV(input,pNames))
		add(&thisMarketData);
	fclose(input);
	delete pNames;
	return 1;
}

int CMarketDataFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "MarketData.csv");
	return readCSV(szFileName);
}

int CMarketDataFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableMarketData *pMarketData;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableMarketData::writeCSVHead(output);
	pMarketData=(CWriteableMarketData *)(pMem->getFirst());
	while (pMarketData!=NULL) {
		if (!pMarketData->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pMarketData=(CWriteableMarketData *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CMarketDataFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "MarketData.csv");
	return writeCSV(szFileName);
}

void CMarketDataFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CMarketDataFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableMarketData *pMarketData;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CMarketDataFactory={       Total Count=%d\n", pMem->getCount());
	pMarketData=(CWriteableMarketData *)(pMem->getFirst());
	while (pMarketData!=NULL) {
		pMarketData->dump(fp,index++);
		pMarketData=(CWriteableMarketData *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CMarketDataFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pExchangeIDAndInstrumentIDIndex->removeAll();
	}
}

CMarketData *CMarketDataFactory::internalAdd(CWriteableMarketData *pMarketData, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForMarketData++;
#endif
	CMarketData *pTarget;	
	beforeAdd(pMarketData);
	pTarget=(CMarketData *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough MarketData in memory database");
		return NULL;
	}
	forceCopy(pTarget, pMarketData, sizeof(CMarketData));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pExchangeIDAndInstrumentIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CMarketData *CMarketDataFactory::add(CWriteableMarketData *pMarketData, CTransaction *pTransaction)
{
	pMarketData->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pMarketData,true);
	}
	else {
		CMarketData *pNewMarketData;
		pNewMarketData = internalAdd(pMarketData,false);
		pTransaction->addResource(CMarketDataResource::alloc(CREATE_ACTION,this,pNewMarketData,NULL));
		return pNewMarketData;
	}
}

void CMarketDataFactory::internalUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForMarketData++;
	}
	else {
		updateWithoutIndexActionForMarketData++;
	}
#endif
	CWriteableMarketData theOldMarketData;
	beforeUpdate(pMarketData,pNewMarketData);
	if (bNoTransaction) {
		forceCopy(&theOldMarketData,pMarketData,sizeof(CMarketData));
	}
	if (updateIndex) {
	}

	forceCopy(pMarketData,pNewMarketData,sizeof(CMarketData));
	pMem->updateObject(pMarketData);
	if (updateIndex) {
	}
	afterUpdate(pMarketData);
	if (bNoTransaction) {
		commitUpdate(pMarketData,&theOldMarketData);
	}
}

void CMarketDataFactory::update(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction, bool updateIndex)
{
	pNewMarketData->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pMarketData,pNewMarketData,updateIndex,true);
	}
	else {
		pTransaction->addResource(CMarketDataResource::alloc(UPDATE_ACTION,this,pMarketData,pNewMarketData,updateIndex));
		internalUpdate(pMarketData,pNewMarketData,updateIndex,false);
	}
}

void CMarketDataFactory::internalRemove(CMarketData *pMarketData, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForMarketData++;
#endif
	CWriteableMarketData theOldMarketData;
	beforeRemove(pMarketData);
	if (bNoTransaction) {
		forceCopy(&theOldMarketData,pMarketData,sizeof(CMarketData));
	}
	if (runLevel>=0) {
		pExchangeIDAndInstrumentIDIndex->removeObject(pMarketData);
	}
	pMem->free(pMarketData);
	if(bNoTransaction) {
		commitRemove(&theOldMarketData);
	}
}

void CMarketDataFactory::remove(CMarketData *pMarketData, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pMarketData,true);
	}
	else {
		pTransaction->addResource(CMarketDataResource::alloc(DELETE_ACTION,this,pMarketData,NULL));
		internalRemove(pMarketData,false);		
	}
}

CMarketData* CMarketDataFactory::addOrUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData, CTransaction *pTransaction, bool updateIndex)
{
	if(pMarketData == NULL) {
		return add(pNewMarketData,pTransaction);
	}
	else {
		update(pMarketData,pNewMarketData,pTransaction,updateIndex);
		return pMarketData;
	}
}

void CMarketDataFactory::retrieve(CMarketData *pMarketData, CWriteableMarketData *pTargetMarketData)
{
	forceCopy(pTargetMarketData, pMarketData, sizeof(CMarketData));
}
	
int CMarketDataFactory::addActionTrigger(CMarketDataActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CMarketDataFactory::removeActionTrigger(CMarketDataActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CMarketDataFactory::addCommitTrigger(CMarketDataCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CMarketDataFactory::removeCommitTrigger(CMarketDataCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CMarketData *CMarketDataFactory::getFirst(void)
{
	CMarketData *pResult=(CMarketData *)(pMem->getFirst());
	return pResult;
}
	
CMarketData *CMarketDataFactory::getNext(void)
{
	CMarketData *pResult=(CMarketData *)(pMem->getNext());
	return pResult;
}
	
void CMarketDataFactory::endGet(void)
{
	pMem->endGet();
}

void CMarketDataFactory::beforeAdd(CWriteableMarketData *pMarketData)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pMarketData);
	}
}
	
void CMarketDataFactory::afterAdd(CMarketData *pMarketData)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pMarketData);
	}
}

void CMarketDataFactory::beforeUpdate(CMarketData *pMarketData, CWriteableMarketData *pNewMarketData)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pMarketData,pNewMarketData);
	}
}
	
void CMarketDataFactory::afterUpdate(CMarketData *pMarketData)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pMarketData);
	}
}
	
void CMarketDataFactory::beforeRemove(CMarketData *pMarketData)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pMarketData);
	}
}

void CMarketDataFactory::commitAdd(CMarketData *pMarketData)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForMarketData++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pMarketData);
	}
}

void CMarketDataFactory::commitUpdate(CMarketData *pMarketData, CWriteableMarketData *pOldMarketData)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForMarketData++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pMarketData,pOldMarketData);
	}
}
	
void CMarketDataFactory::commitRemove(CWriteableMarketData *pMarketData)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForMarketData++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pMarketData);
	}
}

void CMarketDataFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

#ifdef COUNT_OPERATION
int addActionForOrderDelay=0;
int updateWithIndexActionForOrderDelay=0;
int updateWithoutIndexActionForOrderDelay=0;
int removeActionForOrderDelay=0;
int addCommitForOrderDelay=0;
int updateCommitForOrderDelay=0;
int removeCommitForOrderDelay=0;
#endif
void COrderDelayFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	pActionTriggers=new vector<COrderDelayActionTrigger *>;
	pCommitTriggers=new vector<COrderDelayCommitTrigger *>;
	m_activeCommitTrigger=true;
}

COrderDelayFactory::COrderDelayFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderDelay),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

COrderDelayFactory::COrderDelayFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(COrderDelay),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

COrderDelayFactory::~COrderDelayFactory(void)
{
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void COrderDelayFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"COrderDelayFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
}

int COrderDelayFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableOrderDelay thisOrderDelay;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisOrderDelay.readCSV(input,pNames))
		add(&thisOrderDelay);
	fclose(input);
	delete pNames;
	return 1;
}

int COrderDelayFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "OrderDelay.csv");
	return readCSV(szFileName);
}

int COrderDelayFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableOrderDelay *pOrderDelay;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableOrderDelay::writeCSVHead(output);
	pOrderDelay=(CWriteableOrderDelay *)(pMem->getFirst());
	while (pOrderDelay!=NULL) {
		if (!pOrderDelay->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pOrderDelay=(CWriteableOrderDelay *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int COrderDelayFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "OrderDelay.csv");
	return writeCSV(szFileName);
}

void COrderDelayFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void COrderDelayFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableOrderDelay *pOrderDelay;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"COrderDelayFactory={       Total Count=%d\n", pMem->getCount());
	pOrderDelay=(CWriteableOrderDelay *)(pMem->getFirst());
	while (pOrderDelay!=NULL) {
		pOrderDelay->dump(fp,index++);
		pOrderDelay=(CWriteableOrderDelay *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void COrderDelayFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
}

COrderDelay *COrderDelayFactory::internalAdd(CWriteableOrderDelay *pOrderDelay, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForOrderDelay++;
#endif
	COrderDelay *pTarget;	
	beforeAdd(pOrderDelay);
	pTarget=(COrderDelay *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough OrderDelay in memory database");
		return NULL;
	}
	forceCopy(pTarget, pOrderDelay, sizeof(COrderDelay));
	pMem->updateObject(pTarget);
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

COrderDelay *COrderDelayFactory::add(CWriteableOrderDelay *pOrderDelay, CTransaction *pTransaction)
{
	pOrderDelay->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pOrderDelay,true);
	}
	else {
		COrderDelay *pNewOrderDelay;
		pNewOrderDelay = internalAdd(pOrderDelay,false);
		pTransaction->addResource(COrderDelayResource::alloc(CREATE_ACTION,this,pNewOrderDelay,NULL));
		return pNewOrderDelay;
	}
}

void COrderDelayFactory::internalUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForOrderDelay++;
	}
	else {
		updateWithoutIndexActionForOrderDelay++;
	}
#endif
	CWriteableOrderDelay theOldOrderDelay;
	beforeUpdate(pOrderDelay,pNewOrderDelay);
	if (bNoTransaction) {
		forceCopy(&theOldOrderDelay,pOrderDelay,sizeof(COrderDelay));
	}
	if (updateIndex) {
	}

	forceCopy(pOrderDelay,pNewOrderDelay,sizeof(COrderDelay));
	pMem->updateObject(pOrderDelay);
	if (updateIndex) {
	}
	afterUpdate(pOrderDelay);
	if (bNoTransaction) {
		commitUpdate(pOrderDelay,&theOldOrderDelay);
	}
}

void COrderDelayFactory::update(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction, bool updateIndex)
{
	pNewOrderDelay->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pOrderDelay,pNewOrderDelay,updateIndex,true);
	}
	else {
		pTransaction->addResource(COrderDelayResource::alloc(UPDATE_ACTION,this,pOrderDelay,pNewOrderDelay,updateIndex));
		internalUpdate(pOrderDelay,pNewOrderDelay,updateIndex,false);
	}
}

void COrderDelayFactory::internalRemove(COrderDelay *pOrderDelay, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForOrderDelay++;
#endif
	CWriteableOrderDelay theOldOrderDelay;
	beforeRemove(pOrderDelay);
	if (bNoTransaction) {
		forceCopy(&theOldOrderDelay,pOrderDelay,sizeof(COrderDelay));
	}
	pMem->free(pOrderDelay);
	if(bNoTransaction) {
		commitRemove(&theOldOrderDelay);
	}
}

void COrderDelayFactory::remove(COrderDelay *pOrderDelay, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pOrderDelay,true);
	}
	else {
		pTransaction->addResource(COrderDelayResource::alloc(DELETE_ACTION,this,pOrderDelay,NULL));
		internalRemove(pOrderDelay,false);		
	}
}

COrderDelay* COrderDelayFactory::addOrUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay, CTransaction *pTransaction, bool updateIndex)
{
	if(pOrderDelay == NULL) {
		return add(pNewOrderDelay,pTransaction);
	}
	else {
		update(pOrderDelay,pNewOrderDelay,pTransaction,updateIndex);
		return pOrderDelay;
	}
}

void COrderDelayFactory::retrieve(COrderDelay *pOrderDelay, CWriteableOrderDelay *pTargetOrderDelay)
{
	forceCopy(pTargetOrderDelay, pOrderDelay, sizeof(COrderDelay));
}
	
int COrderDelayFactory::addActionTrigger(COrderDelayActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int COrderDelayFactory::removeActionTrigger(COrderDelayActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int COrderDelayFactory::addCommitTrigger(COrderDelayCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int COrderDelayFactory::removeCommitTrigger(COrderDelayCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

COrderDelay *COrderDelayFactory::getFirst(void)
{
	COrderDelay *pResult=(COrderDelay *)(pMem->getFirst());
	return pResult;
}
	
COrderDelay *COrderDelayFactory::getNext(void)
{
	COrderDelay *pResult=(COrderDelay *)(pMem->getNext());
	return pResult;
}
	
void COrderDelayFactory::endGet(void)
{
	pMem->endGet();
}

void COrderDelayFactory::beforeAdd(CWriteableOrderDelay *pOrderDelay)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pOrderDelay);
	}
}
	
void COrderDelayFactory::afterAdd(COrderDelay *pOrderDelay)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pOrderDelay);
	}
}

void COrderDelayFactory::beforeUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pNewOrderDelay)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pOrderDelay,pNewOrderDelay);
	}
}
	
void COrderDelayFactory::afterUpdate(COrderDelay *pOrderDelay)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pOrderDelay);
	}
}
	
void COrderDelayFactory::beforeRemove(COrderDelay *pOrderDelay)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pOrderDelay);
	}
}

void COrderDelayFactory::commitAdd(COrderDelay *pOrderDelay)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForOrderDelay++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pOrderDelay);
	}
}

void COrderDelayFactory::commitUpdate(COrderDelay *pOrderDelay, CWriteableOrderDelay *pOldOrderDelay)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForOrderDelay++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pOrderDelay,pOldOrderDelay);
	}
}
	
void COrderDelayFactory::commitRemove(CWriteableOrderDelay *pOrderDelay)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForOrderDelay++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pOrderDelay);
	}
}

void COrderDelayFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

extern int compareForSystemIDIndexinSystemInfo(const void *pV1, const void *pV2);
#ifdef COUNT_OPERATION
int addActionForSystemInfo=0;
int updateWithIndexActionForSystemInfo=0;
int updateWithoutIndexActionForSystemInfo=0;
int removeActionForSystemInfo=0;
int addCommitForSystemInfo=0;
int updateCommitForSystemInfo=0;
int removeCommitForSystemInfo=0;
#endif
void CSystemInfoFactory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	if (runLevel>=0) {
		if(!reuse) {
			pSystemIDIndex=new CAVLTree(maxUnit,compareForSystemIDIndexinSystemInfo,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("SystemInfo_SystemIDIndex",pSystemIDIndex->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("SystemInfo_SystemIDIndex");
			if(it != pIndexMap->end()) {
				pSystemIDIndex=new CAVLTree(maxUnit,compareForSystemIDIndexinSystemInfo,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (pSystemIDIndex==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	pActionTriggers=new vector<CSystemInfoActionTrigger *>;
	pCommitTriggers=new vector<CSystemInfoCommitTrigger *>;
	m_activeCommitTrigger=true;
}

CSystemInfoFactory::CSystemInfoFactory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSystemInfo),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

CSystemInfoFactory::CSystemInfoFactory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(CSystemInfo),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

CSystemInfoFactory::~CSystemInfoFactory(void)
{
	if (runLevel>=0) {
		if (pSystemIDIndex!=NULL)
			delete pSystemIDIndex;
	}
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void CSystemInfoFactory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"CSystemInfoFactory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	if (runLevel>=0) {
		pSystemIDIndex->output(pLogger,indent+1);
	}
}

int CSystemInfoFactory::readCSV(char *filename)
{
	FILE *input;
	CWriteableSystemInfo thisSystemInfo;
	char buffer[1025];
	vector<char *> *pNames;
	char *token;
	input=mfopen(filename,"rt");
	if (input==NULL)
		return 0;
	pNames=new vector<char *>;
	fgets(buffer,1024,input);
	token=getNextToken(buffer);
	while (token!=NULL) {
		pNames->push_back(token);
		token=getNextToken(NULL);
	}
	while (thisSystemInfo.readCSV(input,pNames))
		add(&thisSystemInfo);
	fclose(input);
	delete pNames;
	return 1;
}

int CSystemInfoFactory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "SystemInfo.csv");
	return readCSV(szFileName);
}

int CSystemInfoFactory::writeCSV(char *filename)
{
	FILE *output;
	CWriteableSystemInfo *pSystemInfo;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteableSystemInfo::writeCSVHead(output);
	pSystemInfo=(CWriteableSystemInfo *)(pMem->getFirst());
	while (pSystemInfo!=NULL) {
		if (!pSystemInfo->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		pSystemInfo=(CWriteableSystemInfo *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int CSystemInfoFactory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "SystemInfo.csv");
	return writeCSV(szFileName);
}

void CSystemInfoFactory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void CSystemInfoFactory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteableSystemInfo *pSystemInfo;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"CSystemInfoFactory={       Total Count=%d\n", pMem->getCount());
	pSystemInfo=(CWriteableSystemInfo *)(pMem->getFirst());
	while (pSystemInfo!=NULL) {
		pSystemInfo->dump(fp,index++);
		pSystemInfo=(CWriteableSystemInfo *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void CSystemInfoFactory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	if (runLevel>=0) {
		pSystemIDIndex->removeAll();
	}
}

CSystemInfo *CSystemInfoFactory::internalAdd(CWriteableSystemInfo *pSystemInfo, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionForSystemInfo++;
#endif
	CSystemInfo *pTarget;	
	beforeAdd(pSystemInfo);
	pTarget=(CSystemInfo *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough SystemInfo in memory database");
		return NULL;
	}
	forceCopy(pTarget, pSystemInfo, sizeof(CSystemInfo));
	pMem->updateObject(pTarget);
	if (runLevel>=0) {
		pSystemIDIndex->addObject(pTarget);
	}
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

CSystemInfo *CSystemInfoFactory::add(CWriteableSystemInfo *pSystemInfo, CTransaction *pTransaction)
{
	pSystemInfo->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(pSystemInfo,true);
	}
	else {
		CSystemInfo *pNewSystemInfo;
		pNewSystemInfo = internalAdd(pSystemInfo,false);
		pTransaction->addResource(CSystemInfoResource::alloc(CREATE_ACTION,this,pNewSystemInfo,NULL));
		return pNewSystemInfo;
	}
}

void CSystemInfoFactory::internalUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionForSystemInfo++;
	}
	else {
		updateWithoutIndexActionForSystemInfo++;
	}
#endif
	CWriteableSystemInfo theOldSystemInfo;
	beforeUpdate(pSystemInfo,pNewSystemInfo);
	if (bNoTransaction) {
		forceCopy(&theOldSystemInfo,pSystemInfo,sizeof(CSystemInfo));
	}
	if (updateIndex) {
	}

	forceCopy(pSystemInfo,pNewSystemInfo,sizeof(CSystemInfo));
	pMem->updateObject(pSystemInfo);
	if (updateIndex) {
	}
	afterUpdate(pSystemInfo);
	if (bNoTransaction) {
		commitUpdate(pSystemInfo,&theOldSystemInfo);
	}
}

void CSystemInfoFactory::update(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction, bool updateIndex)
{
	pNewSystemInfo->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(pSystemInfo,pNewSystemInfo,updateIndex,true);
	}
	else {
		pTransaction->addResource(CSystemInfoResource::alloc(UPDATE_ACTION,this,pSystemInfo,pNewSystemInfo,updateIndex));
		internalUpdate(pSystemInfo,pNewSystemInfo,updateIndex,false);
	}
}

void CSystemInfoFactory::internalRemove(CSystemInfo *pSystemInfo, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionForSystemInfo++;
#endif
	CWriteableSystemInfo theOldSystemInfo;
	beforeRemove(pSystemInfo);
	if (bNoTransaction) {
		forceCopy(&theOldSystemInfo,pSystemInfo,sizeof(CSystemInfo));
	}
	if (runLevel>=0) {
		pSystemIDIndex->removeObject(pSystemInfo);
	}
	pMem->free(pSystemInfo);
	if(bNoTransaction) {
		commitRemove(&theOldSystemInfo);
	}
}

void CSystemInfoFactory::remove(CSystemInfo *pSystemInfo, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(pSystemInfo,true);
	}
	else {
		pTransaction->addResource(CSystemInfoResource::alloc(DELETE_ACTION,this,pSystemInfo,NULL));
		internalRemove(pSystemInfo,false);		
	}
}

CSystemInfo* CSystemInfoFactory::addOrUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo, CTransaction *pTransaction, bool updateIndex)
{
	if(pSystemInfo == NULL) {
		return add(pNewSystemInfo,pTransaction);
	}
	else {
		update(pSystemInfo,pNewSystemInfo,pTransaction,updateIndex);
		return pSystemInfo;
	}
}

void CSystemInfoFactory::retrieve(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pTargetSystemInfo)
{
	forceCopy(pTargetSystemInfo, pSystemInfo, sizeof(CSystemInfo));
}
	
int CSystemInfoFactory::addActionTrigger(CSystemInfoActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int CSystemInfoFactory::removeActionTrigger(CSystemInfoActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int CSystemInfoFactory::addCommitTrigger(CSystemInfoCommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int CSystemInfoFactory::removeCommitTrigger(CSystemInfoCommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

CSystemInfo *CSystemInfoFactory::getFirst(void)
{
	CSystemInfo *pResult=(CSystemInfo *)(pMem->getFirst());
	return pResult;
}
	
CSystemInfo *CSystemInfoFactory::getNext(void)
{
	CSystemInfo *pResult=(CSystemInfo *)(pMem->getNext());
	return pResult;
}
	
void CSystemInfoFactory::endGet(void)
{
	pMem->endGet();
}

void CSystemInfoFactory::beforeAdd(CWriteableSystemInfo *pSystemInfo)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(pSystemInfo);
	}
}
	
void CSystemInfoFactory::afterAdd(CSystemInfo *pSystemInfo)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(pSystemInfo);
	}
}

void CSystemInfoFactory::beforeUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pNewSystemInfo)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(pSystemInfo,pNewSystemInfo);
	}
}
	
void CSystemInfoFactory::afterUpdate(CSystemInfo *pSystemInfo)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(pSystemInfo);
	}
}
	
void CSystemInfoFactory::beforeRemove(CSystemInfo *pSystemInfo)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(pSystemInfo);
	}
}

void CSystemInfoFactory::commitAdd(CSystemInfo *pSystemInfo)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitForSystemInfo++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(pSystemInfo);
	}
}

void CSystemInfoFactory::commitUpdate(CSystemInfo *pSystemInfo, CWriteableSystemInfo *pOldSystemInfo)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitForSystemInfo++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(pSystemInfo,pOldSystemInfo);
	}
}
	
void CSystemInfoFactory::commitRemove(CWriteableSystemInfo *pSystemInfo)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitForSystemInfo++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(pSystemInfo);
	}
}

void CSystemInfoFactory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}


#ifdef COUNT_OPERATION

#define clearCount(name)						\
	addActionFor ## name =0;					\
	updateWithIndexActionFor ## name =0;		\
	updateWithoutIndexActionFor ## name =0;		\
	removeActionFor ## name =0;					\
	addCommitFor ## name=0;						\
	updateCommitFor ## name =0;					\
	removeCommitFor ## name =0;

void initAllOperationCount(void)
{
	clearCount(DataSyncStatus);
	clearCount(SystemStatus);
	clearCount(OrderAction);
	clearCount(Order);
	clearCount(Trade);
	clearCount(PreOrder);
	clearCount(IndexPreOrder);
	clearCount(InvestorPosition);
	clearCount(InvestorAccount);
	clearCount(InvestorAccountDeposit);
	clearCount(Exchange);
	clearCount(Seat);
	clearCount(Instrument);
	clearCount(CmbInstrumentDetail);
	clearCount(ClientTradingID);
	clearCount(Investor);
	clearCount(InvestorMargin);
	clearCount(InvestorFee);
	clearCount(User);
	clearCount(UserInvestor);
	clearCount(OrderInsertFailed);
	clearCount(UserTradingRight);
	clearCount(CurrentTime);
	clearCount(UserSession);
	clearCount(MaxLocalID);
	clearCount(BrkUserIDLocalID);
	clearCount(PartClientInsGroupPosition);
	clearCount(ClientMarginCombType);
	clearCount(InstrumentGroup);
	clearCount(SGEDeferRate);
	clearCount(InvestorTradingRight);
	clearCount(UserIP);
	clearCount(InvestorOptionFee);
	clearCount(MarketData);
	clearCount(OrderDelay);
	clearCount(SystemInfo);
}

#define display(id)						\
	if (id!=0)							\
	{									\
		printf("\t" #id ":%d\n", id);	\
	}

#define displayAll(name)							\
	display(addActionFor ## name);					\
	display(updateWithIndexActionFor ## name);		\
	display(updateWithoutIndexActionFor ## name);	\
	display(removeActionFor ## name);				\
	display(addCommitFor ## name);					\
	display(updateCommitFor ## name);				\
	display(removeCommitFor ## name);

void showAllOperationCount(void)
{
	displayAll(DataSyncStatus);
	displayAll(SystemStatus);
	displayAll(OrderAction);
	displayAll(Order);
	displayAll(Trade);
	displayAll(PreOrder);
	displayAll(IndexPreOrder);
	displayAll(InvestorPosition);
	displayAll(InvestorAccount);
	displayAll(InvestorAccountDeposit);
	displayAll(Exchange);
	displayAll(Seat);
	displayAll(Instrument);
	displayAll(CmbInstrumentDetail);
	displayAll(ClientTradingID);
	displayAll(Investor);
	displayAll(InvestorMargin);
	displayAll(InvestorFee);
	displayAll(User);
	displayAll(UserInvestor);
	displayAll(OrderInsertFailed);
	displayAll(UserTradingRight);
	displayAll(CurrentTime);
	displayAll(UserSession);
	displayAll(MaxLocalID);
	displayAll(BrkUserIDLocalID);
	displayAll(PartClientInsGroupPosition);
	displayAll(ClientMarginCombType);
	displayAll(InstrumentGroup);
	displayAll(SGEDeferRate);
	displayAll(InvestorTradingRight);
	displayAll(UserIP);
	displayAll(InvestorOptionFee);
	displayAll(MarketData);
	displayAll(OrderDelay);
	displayAll(SystemInfo);
}
#endif

