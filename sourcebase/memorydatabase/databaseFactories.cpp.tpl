!!include function.tpl!!
!!enter system!!
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

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!command resetEntityMap();!!
!!travel fields!!
!!command addEntity(@name,@type)!!
!!next!!
!!let tableName=@name!!
!!travel index!!
extern int compareFor!!@name!!in!!@tableName!!(const void *pV1, const void *pV2);
!!next!!
#ifdef COUNT_OPERATION
int addActionFor!!@tableName!!=0;
int updateWithIndexActionFor!!@tableName!!=0;
int updateWithoutIndexActionFor!!@tableName!!=0;
int removeActionFor!!@tableName!!=0;
int addCommitFor!!@tableName!!=0;
int updateCommitFor!!@tableName!!=0;
int removeCommitFor!!@tableName!!=0;
#endif
void C!!@name!!Factory::init(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly)
{
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		if(!reuse) {
			p!!@name!!=new CAVLTree(maxUnit,compareFor!!@name!!in!!@tableName!!,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("!!@tableName!!_!!@name!!",p!!@name!!->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("!!@tableName!!_!!@name!!");
			if(it != pIndexMap->end()) {
				p!!@name!!=new CAVLTree(maxUnit,compareFor!!@name!!in!!@tableName!!,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (p!!@name!!==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	!!next!!
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	if (runLevel>=!!@runLevel!!) {
		int hashKeySize=!!@hashKeySize!!;
		if (m_pConfig!=NULL) {
			int newSize=atoi(m_pConfig->getConfig("!!@tableName!!.size"));
			if (newSize>0) {
				hashKeySize=newSize;
			}
		}
		if(!reuse) {
			p!!@name!!=new CHashIndex(hashKeySize,pAllocator,reuse,reuseID,readOnly);
			if(pIndexMap != NULL)
				pIndexMap->insert(map<string,int>::value_type("!!@tableName!!_!!@name!!",p!!@name!!->getReuseID()));
		}
		else {
			map<string,int>::iterator it = pIndexMap->find("!!@tableName!!_!!@name!!");
			if(it != pIndexMap->end()) {
				p!!@name!!=new CHashIndex(hashKeySize,pAllocator,reuse,it->second,readOnly);
			}
		}
		if (p!!@name!!==NULL)
			RAISE_RUNTIME_ERROR("Insufficient memory space");
	}
	!!next!!
	!!endif!!
	!!travel search!!
	!!if (strcmp(@searchUnique,"yes"))!!
	pLastFoundInSearch!!@name!!=NULL;
	!!endif!!
	!!next!!
!!++!!if (reuse&&!readOnly)
	{
		C!!@name!! *p!!@name!!;
		p!!@name!!=(C!!@name!! *)(pMem->getFirst());
		while (p!!@name!!!=NULL)
		{
			!!let tableName=@name!!
			!!travel index!!
			if (runLevel>=!!@runLevel!!)
			{
				p!!@name!!->addObject(p!!@tableName!!);
			}
			!!next!!
			p!!@name!!=(C!!@name!! *)(pMem->getNext());
		}
		pMem->endGet();
	}!!--!!
	pActionTriggers=new vector<C!!@name!!ActionTrigger *>;
	pCommitTriggers=new vector<C!!@name!!CommitTrigger *>;
	m_activeCommitTrigger=true;
}

C!!@name!!Factory::C!!@name!!Factory(int maxUnit,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(C!!@name!!),maxUnit,pAllocator,reuse,reuseID, readOnly)
{
	m_pConfig=NULL;
	init(maxUnit,pAllocator,pIndexMap,reuse,reuseID,readOnly);
}

C!!@name!!Factory::C!!@name!!Factory(CConfig *pConfig,IMemoryAllocator *pAllocator,map<string,int>* pIndexMap,bool reuse,int reuseID,int readOnly) :
	CDatabaseDataFactory(sizeof(C!!@name!!),MDB_DEFAULT_BLOCK_SIZE,pAllocator,reuse,reuseID,readOnly)
{
	m_pConfig=pConfig;
	init(MDB_DEFAULT_BLOCK_SIZE,pAllocator,pIndexMap,reuse,reuseID,readOnly);		
}

C!!@name!!Factory::~C!!@name!!Factory(void)
{
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		if (p!!@name!!!=NULL)
			delete p!!@name!!;
	}
	!!next!!
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	if (runLevel>=!!@runLevel!!) {
		if (p!!@name!!!=NULL)
			delete p!!@name!!;
	}
	!!next!!
	!!endif!!
	if (pActionTriggers!=NULL)
		delete pActionTriggers;
	if (pCommitTriggers!=NULL)
		delete pCommitTriggers;
}

void C!!@name!!Factory::output(CLogger *pLogger,int indent)
{
	pLogger->output(indent,0,"C!!@name!!Factory");
	CDatabaseDataFactory::output(pLogger,indent+1);
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->output(pLogger,indent+1);
	}
	!!next!!
}

int C!!@name!!Factory::readCSV(char *filename)
{
	FILE *input;
	CWriteable!!@name!! this!!@name!!;
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
	while (this!!@name!!.readCSV(input,pNames))
		add(&this!!@name!!);
	fclose(input);
	delete pNames;
	return 1;
}

int C!!@name!!Factory::readCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVReadPath"));
	strcat(szFileName, "!!@name!!.csv");
	return readCSV(szFileName);
}

int C!!@name!!Factory::writeCSV(char *filename)
{
	FILE *output;
	CWriteable!!@name!! *p!!@name!!;
	output=mfopen(filename,"wt");
	if (output==NULL)
		return 0;
	CWriteable!!@name!!::writeCSVHead(output);
	p!!@name!!=(CWriteable!!@name!! *)(pMem->getFirst());
	while (p!!@name!!!=NULL) {
		if (!p!!@name!!->writeCSV(output)) {
			pMem->endGet();
			fclose(output);
			return 0;
		}
		p!!@name!!=(CWriteable!!@name!! *)(pMem->getNext());
	}
	pMem->endGet();
	fclose(output);
	return 1;
}

int C!!@name!!Factory::writeCSV(CConfig *pConfig)
{
	char szFileName[300];
	strcpy(szFileName, pConfig->getConfig("CSVWritePath"));
	strcat(szFileName, "!!@name!!.csv");
	return writeCSV(szFileName);
}

void C!!@name!!Factory::dump(char *filename)
{
	FILE *fp;
	fp = mfopen(filename,"w+b");
	dump(fp);
	if (fp!=NULL) fclose(fp);
}	

void C!!@name!!Factory::dump(FILE *fp)
{
	int index=0; ///下标
	CWriteable!!@name!! *p!!@name!!;
	if(fp==NULL) fp=stdout;
	pMem->dump(fp);
	fprintf(fp,"C!!@name!!Factory={       Total Count=%d\n", pMem->getCount());
	p!!@name!!=(CWriteable!!@name!! *)(pMem->getFirst());
	while (p!!@name!!!=NULL) {
		p!!@name!!->dump(fp,index++);
		p!!@name!!=(CWriteable!!@name!! *)(pMem->getNext());
	}
	fprintf(fp,"}\n");
	pMem->endGet();
}

void C!!@name!!Factory::clearAll(void)
{
	CDatabaseDataFactory::clearAll();
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->removeAll();
	}
	!!next!!
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->removeAll();
	}
	!!next!!
	!!endif!!
}

C!!@name!! *C!!@name!!Factory::internalAdd(CWriteable!!@name!! *p!!@name!!, bool bNoTransaction)
{	
#ifdef COUNT_OPERATION
	addActionFor!!@tableName!!++;
#endif
	C!!@name!! *pTarget;	
	beforeAdd(p!!@name!!);
	pTarget=(C!!@name!! *)createObject();
	if (pTarget==NULL) {
		RAISE_DESIGN_ERROR("Can not alloc enough !!@name!! in memory database");
		return NULL;
	}
	forceCopy(pTarget, p!!@name!!, sizeof(C!!@name!!));
	pMem->updateObject(pTarget);
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->addObject(pTarget);
	}
	!!next!!
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->addObject(pTarget,pTarget->Hash!!@hashKey!!);
	}
	!!next!!
	!!endif!!
	afterAdd(pTarget);
	if (bNoTransaction) {
		commitAdd(pTarget);
	}
	return pTarget;
}

C!!@name!! *C!!@name!!Factory::add(CWriteable!!@name!! *p!!@name!!, CTransaction *pTransaction)
{
	p!!@name!!->calAllHash();
	if (pTransaction==NULL) {
		return internalAdd(p!!@name!!,true);
	}
	else {
		C!!@name!! *pNew!!@name!!;
		pNew!!@name!! = internalAdd(p!!@name!!,false);
		pTransaction->addResource(C!!@name!!Resource::alloc(CREATE_ACTION,this,pNew!!@name!!,NULL));
		return pNew!!@name!!;
	}
}

void C!!@name!!Factory::internalUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, bool updateIndex,bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	if (updateIndex) {
		updateWithIndexActionFor!!@tableName!!++;
	}
	else {
		updateWithoutIndexActionFor!!@tableName!!++;
	}
#endif
	CWriteable!!@name!! theOld!!@name!!;
	beforeUpdate(p!!@name!!,pNew!!@name!!);
	if (bNoTransaction) {
		forceCopy(&theOld!!@name!!,p!!@name!!,sizeof(C!!@name!!));
	}
	!!let tableName=@name!!
	!!travel index!!
	!!if !strcmp(@stableIndex,"no")!!
	CAVLNode *p!!@name!!Node=NULL;
	!!endif!!
	!!next!!
	if (updateIndex) {
		!!travel index!!
		!!if !strcmp(@stableIndex,"no")!!
		if (runLevel>=!!@runLevel!!) {
			p!!@name!!Node=p!!@name!!->findObject(p!!@tableName!!);
		}
		!!endif!!
		!!next!!
		!!if valid_name("hashindex")!!
		!!travel hashindex!!
		!!if !strcmp(@stableIndex,"no")!!
		if (runLevel>=!!@runLevel!!) {
			p!!@name!!->removeObject(p!!@tableName!!,p!!@tableName!!->Hash!!@hashKey!!);
		}
		!!endif!!
		!!next!!
		!!endif!!
	}

	forceCopy(p!!@name!!,pNew!!@name!!,sizeof(C!!@name!!));
	pMem->updateObject(p!!@name!!);
	if (updateIndex) {
		!!travel index!!
		!!if !strcmp(@stableIndex,"no")!!
		if (runLevel>=!!@runLevel!!) {
			p!!@name!!->updateNode(p!!@name!!Node);
		}
		!!endif!!
		!!next!!
		!!if valid_name("hashindex")!!
		!!travel hashindex!!
		!!if !strcmp(@stableIndex,"no")!!
		if (runLevel>=!!@runLevel!!) {
			p!!@name!!->addObject(p!!@tableName!!,p!!@tableName!!->Hash!!@hashKey!!);
		}
		!!endif!!
		!!next!!
		!!endif!!
	}
	afterUpdate(p!!@name!!);
	if (bNoTransaction) {
		commitUpdate(p!!@name!!,&theOld!!@name!!);
	}
}

void C!!@name!!Factory::update(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, CTransaction *pTransaction, bool updateIndex)
{
	pNew!!@name!!->updateAllHash();
	if (pTransaction==NULL) {
		internalUpdate(p!!@name!!,pNew!!@name!!,updateIndex,true);
	}
	else {
		pTransaction->addResource(C!!@name!!Resource::alloc(UPDATE_ACTION,this,p!!@name!!,pNew!!@name!!,updateIndex));
		internalUpdate(p!!@name!!,pNew!!@name!!,updateIndex,false);
	}
}

void C!!@name!!Factory::internalRemove(C!!@name!! *p!!@name!!, bool bNoTransaction)
{
#ifdef COUNT_OPERATION
	removeActionFor!!@tableName!!++;
#endif
	CWriteable!!@name!! theOld!!@name!!;
	beforeRemove(p!!@name!!);
	if (bNoTransaction) {
		forceCopy(&theOld!!@name!!,p!!@name!!,sizeof(C!!@name!!));
	}
	!!travel index!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->removeObject(p!!@tableName!!);
	}
	!!next!!
	!!if valid_name("hashindex")!!
	!!travel hashindex!!
	if (runLevel>=!!@runLevel!!) {
		p!!@name!!->removeObject(p!!@tableName!!,p!!@tableName!!->Hash!!@hashKey!!);
	}	
	!!next!!
	!!endif!!
	pMem->free(p!!@name!!);
	if(bNoTransaction) {
		commitRemove(&theOld!!@name!!);
	}
}

void C!!@name!!Factory::remove(C!!@name!! *p!!@name!!, CTransaction *pTransaction)
{
	if (pTransaction==NULL) {
		internalRemove(p!!@name!!,true);
	}
	else {
		pTransaction->addResource(C!!@name!!Resource::alloc(DELETE_ACTION,this,p!!@name!!,NULL));
		internalRemove(p!!@name!!,false);		
	}
}

C!!@name!!* C!!@name!!Factory::addOrUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!, CTransaction *pTransaction, bool updateIndex)
{
	if(p!!@name!! == NULL) {
		return add(pNew!!@name!!,pTransaction);
	}
	else {
		update(p!!@name!!,pNew!!@name!!,pTransaction,updateIndex);
		return p!!@name!!;
	}
}

void C!!@name!!Factory::retrieve(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pTarget!!@name!!)
{
	forceCopy(pTarget!!@name!!, p!!@name!!, sizeof(C!!@name!!));
}
	
int C!!@name!!Factory::addActionTrigger(C!!@name!!ActionTrigger *pActionTrigger)
{
	pActionTrigger->setFactory(this);
	pActionTriggers->push_back(pActionTrigger);
	return 1;
}

int C!!@name!!Factory::removeActionTrigger(C!!@name!!ActionTrigger *pActionTrigger)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		if (pActionTriggers->at(i)==pActionTrigger) {
			pActionTriggers->erase(pActionTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

int C!!@name!!Factory::addCommitTrigger(C!!@name!!CommitTrigger *pCommitTrigger)
{
	pCommitTrigger->setFactory(this);
	pCommitTriggers->push_back(pCommitTrigger);
	return 1;
}

int C!!@name!!Factory::removeCommitTrigger(C!!@name!!CommitTrigger *pCommitTrigger)
{
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		if (pCommitTriggers->at(i)==pCommitTrigger) {
			pCommitTriggers->erase(pCommitTriggers->begin()+i);
			return 1;
		}
	}
	return 0;
}

C!!@name!! *C!!@name!!Factory::getFirst(void)
{
	C!!@name!! *pResult=(C!!@name!! *)(pMem->getFirst());
	return pResult;
}
	
C!!@name!! *C!!@name!!Factory::getNext(void)
{
	C!!@name!! *pResult=(C!!@name!! *)(pMem->getNext());
	return pResult;
}
	
void C!!@name!!Factory::endGet(void)
{
	pMem->endGet();
}

void C!!@name!!Factory::beforeAdd(CWriteable!!@name!! *p!!@name!!)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeAdd(p!!@name!!);
	}
}
	
void C!!@name!!Factory::afterAdd(C!!@name!! *p!!@name!!)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterAdd(p!!@name!!);
	}
}

void C!!@name!!Factory::beforeUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pNew!!@name!!)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeUpdate(p!!@name!!,pNew!!@name!!);
	}
}
	
void C!!@name!!Factory::afterUpdate(C!!@name!! *p!!@name!!)
{
	for (int i=0;i<(int)pActionTriggers->size();i++) {
		pActionTriggers->at(i)->afterUpdate(p!!@name!!);
	}
}
	
void C!!@name!!Factory::beforeRemove(C!!@name!! *p!!@name!!)
{
	for (int i=pActionTriggers->size()-1;i>=0;i--) {
		pActionTriggers->at(i)->beforeRemove(p!!@name!!);
	}
}

void C!!@name!!Factory::commitAdd(C!!@name!! *p!!@name!!)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	addCommitFor!!@tableName!!++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitAdd(p!!@name!!);
	}
}

void C!!@name!!Factory::commitUpdate(C!!@name!! *p!!@name!!, CWriteable!!@name!! *pOld!!@name!!)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	updateCommitFor!!@tableName!!++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitUpdate(p!!@name!!,pOld!!@name!!);
	}
}
	
void C!!@name!!Factory::commitRemove(CWriteable!!@name!! *p!!@name!!)
{
	if (!m_activeCommitTrigger) return;
#ifdef COUNT_OPERATION
	removeCommitFor!!@tableName!!++;
#endif
	for (int i=0;i<(int)pCommitTriggers->size();i++) {
		pCommitTriggers->at(i)->commitRemove(p!!@name!!);
	}
}

void C!!@name!!Factory::activeCommitTrigger(bool activation)
{
	m_activeCommitTrigger=activation;
}

!!travel foreigns!!
void C!!@tableName!!Factory::linkAll!!@name!!(C!!@factory!!Factory *pFactory)
{
	C!!@tableName!! *p!!@tableName!!;
	p!!@tableName!!=getFirst();
	while (p!!@tableName!! != NULL) {
		p!!@tableName!!->link!!@name!!(pFactory);
		p!!@tableName!!=getNext();
	}
	endGet();
}

!!next!!
!!++!!void C!!@name!!Factory::checkAddress(C!!@name!! *p!!@name!!)
{
	if (!pMem->checkAddress(p!!@name!!)) {
		RAISE_DESIGN_ERROR("Invalid C!!@name!!");
	}
}!!--!!
!!endif!!
!!next!!

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
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
	clearCount(!!@name!!);
!!endif!!
!!next!!
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
!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
	displayAll(!!@name!!);
!!endif!!
!!next!!
}
#endif

!!leave!!
