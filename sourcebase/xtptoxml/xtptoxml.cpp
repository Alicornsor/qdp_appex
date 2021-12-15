#include "public.h"
#include "xtptoxml.h"
#include "CXML.h"
#include "XtpPackageDesc.h"
#include "FileFlow.h"
#include "CachedFlow.h"
#include "FlowReader.h"
#include <string>

typedef map<string, string> StringMap;

void XMLNode2StringMap(CXMLNode * pNode, StringMap *pStringmap)
{
	CXMLPropertyList *pList = pNode->getPropertyList();
	string key, value;
	StringMap hm;
	for(int i=0; i<pList->size(); i++)
	{
		CXMLProperty *  property = pList->at(i);
		key = property->getName();
		value = property->getValue();
		 
		hm[key] = value;
	}
	*pStringmap = hm;
	return;
}

void XTP_FIELD_DEBUG(FILE *fpOutput, char *pData, CFieldDescribe *pFieldDescribe)
{
	fprintf(fpOutput, "	XTP FIELD [%s] START\n", pFieldDescribe->GetFieldName());  
	for (int i=0; i<pFieldDescribe->GetMemberCount(); i++)
	{
		TMemberDesc *pMemberDesc=pFieldDescribe->GetMemberDesc(i);
		fprintf(fpOutput, "		[%s][%d]",pMemberDesc->szName, pMemberDesc->nType&0xFF);
		char *pMember = pData+pMemberDesc->nStructOffset;
		switch(pMemberDesc->nType)
		{
		case FT_WORD:
			fprintf(fpOutput, "[%d]\n", *((WORD *)pMember)&0xFFFF);
			break;
		case FT_DWORD:			
			fprintf(fpOutput, "[%d]\n", *((DWORD *)pMember));
			break;
		case FT_BYTE:
			if (pMemberDesc->nSize == 1)
			{
				fprintf(fpOutput, "[%d]\n", *pMember&0xFF);
			}
			else
			{
				fprintf(fpOutput, "[%s]\n", pMember);
			}
			break;
		case FT_REAL4:
			fprintf(fpOutput, "[%f]\n",*((REAL4 *)pMember));
			break;
		case FT_REAL8:
			fprintf(fpOutput, "[%lf]\n",*((REAL8 *)pMember));
			break;
		}		
	}	
	fprintf(fpOutput, "	XTP FIELD [%s] END\n", pFieldDescribe->GetFieldName());  
}

void _XTP_PACKAGE_DEBUG(CXTPPackage *pPackage, FILE *fpOutput)
{
	TXTPHeader *pHeader = pPackage->GetXTPHeader();
	fprintf(fpOutput, "XTP PACKAGE HEADER\n");
	fprintf(fpOutput, "Type=[0X%02X],Chain=[0X%02X],ContentLength=[%d],SubjectID=[0X%08X],Tid=[0X%08X]\n",
		pHeader->Type&0xFF, pHeader->Chain&0xFF, pHeader->ContentLength&0xFFFF, pHeader->SubjectID, pHeader->Tid);
	fprintf(fpOutput, "CommPhaseNo=[%d],SequenceNo=[%d],RequestID=[%d],SessionID=[%d],FrontID=[%d]\n",
		pHeader->CommPhaseNo, pHeader->SequenceNo, pHeader->RequestID, pHeader->SessionID, pHeader->FrontID);	
	fprintf(fpOutput, "XTP PACKAGE CONTENT START\n");
	
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(pHeader->Tid);
	if(pFind == NULL)
	{
		fprintf(fpOutput, "Can't find package define tid=%08X\n",pHeader->Tid);
		return;
	}
	
	char buf[10000];
	TPackageDefine *pPackageDefine = *pFind;
	
	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();
	while(!itor.IsEnd())
	{
		TFieldHeader fieldHeader;
		itor.RetrieveHeader(fieldHeader);
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;
		for(int i=0; i<pPackageDefine->fieldUseCount; i++)
		{
			if(pFieldUse->fid == fieldHeader.FieldID)
			{
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);
				XTP_FIELD_DEBUG(fpOutput, buf, pFieldUse->pFieldDescribe);
				break;
			}
			pFieldUse++;
		}
		itor.Next();
	}
	fprintf(fpOutput, "XTP PACKAGE CONTENT END\n");
}

void XTPPackage2XMLNode(CXTPPackage *pPackage, CXMLNode *pNode)
{
	char buf[10000];
	//memset(buf, 0, 10000*sizeof(char));
	TXTPHeader *pHeader = pPackage->GetXTPHeader();
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(pHeader->Tid);
	if(pFind == NULL)
	{
		fprintf(stderr, "Can't find package define tid=%08X\n",pHeader->Tid);
		return;
	}

	TPackageDefine *pPackageDefine = *pFind;
	string *pPackageName = new string(pPackageDefine->packageName);
	*pPackageName += "Package";
	pNode->setName((char *)pPackageName->c_str());
	pNode->setNodeType(XMLTag);
	char *pTid = (char *)malloc(11*sizeof(char));
	sprintf(pTid,"0x%08X", pPackageDefine->tid);
	pNode->addProperty("tid", pTid);
	pNode->addProperty("comment", pPackageDefine->comment);
	pNode->addProperty("frontid", pPackage->GetFrontID());
	pNode->addProperty("sessionid", pPackage->GetSessionID());

	CFieldTypeIterator itor = pPackage->GetFieldTypeIterator();
	while(!itor.IsEnd())
	{
		TFieldHeader fieldHeader;
		itor.RetrieveHeader(fieldHeader);
		TFieldUse *pFieldUse = pPackageDefine->fieldUse;
		for(int i=0; i<pPackageDefine->fieldUseCount; i++)
		{
			if(pFieldUse->fid == fieldHeader.FieldID)
			{
				CXMLNode *pFieldNode = new CXMLNode();
				pFieldNode->setNodeType(XMLTag);
				pFieldNode->setName(((char *)pFieldUse->pFieldDescribe->GetFieldName()) + 1);
				char *pFid = (char *)malloc(7*sizeof(char));
				sprintf(pFid,"0x%04X", fieldHeader.FieldID);
				pFieldNode->addProperty("fid", pFid);
				pFieldNode->addProperty("comment", pFieldUse->pFieldDescribe->m_szComment);
				itor.Retrieve(pFieldUse->pFieldDescribe, buf);
				char *szDoubleString;
				for (int i=0; i<pFieldUse->pFieldDescribe->GetMemberCount(); i++)
				{
					TMemberDesc *pMemberDesc = pFieldUse->pFieldDescribe->GetMemberDesc(i);
					union
					{
						char pMember[1024];
						double fvalue;
					};
					char *pMemberSource = buf + pMemberDesc->nStructOffset;
					memcpy(pMember,pMemberSource,pMemberDesc->nSize);
					switch(pMemberDesc->nType)
					{
					case FT_WORD:
						 pFieldNode->addProperty(pMemberDesc->szName, *((WORD *)pMember)&0xFFFF);					     
						 break;
					case FT_DWORD:			
					     pFieldNode->addProperty(pMemberDesc->szName, *((DWORD *)pMember));					     
					     break;
					case FT_BYTE:
					     if (pMemberDesc->nSize == 1)
					     {
							 // FIXME: 有内存泄露
							 char *c = (char *)malloc(2*sizeof(char));
							 c[1] = '\0';
							 *c = (*pMember&0xFF);
							 pFieldNode->addProperty(pMemberDesc->szName, c);					     
					     }
					     else
					     {
							 pFieldNode->addProperty(pMemberDesc->szName, pMember);					     
					     }
					     break;
					case FT_REAL4:
					     szDoubleString = (char *)malloc(100*sizeof(char));
					     if(FLT_MAX == *((REAL8 *)pMember))
						szDoubleString[0] = 0;
					     else
						sprintf(szDoubleString, "%f",*((REAL4 *)pMember));
					     pFieldNode->addProperty(pMemberDesc->szName, szDoubleString);					     
					     break;
					case FT_REAL8:
					     szDoubleString = (char *)malloc(100*sizeof(char));
					     if(DBL_MAX == *((REAL8 *)pMember))
						szDoubleString[0] = 0;
					     else
						sprintf(szDoubleString, "%lf",*((REAL8 *)pMember));
					     pFieldNode->addProperty(pMemberDesc->szName, szDoubleString);
					     break;
					}		
				}
				pNode->addNode(pFieldNode);
			}
			pFieldUse++;
		}
		itor.Next();
	}
	//fprintf(stderr, "XTP PACKAGE CONTENT END\n");
}

class CFieldMap: public CHashMap<DWORD, void *, HashInt>
{};

class CStringMM: public CHashMap<DWORD, StringMap *, HashInt>
{};

CFieldDescribe *FindFieldDescribe(TPackageDefine * pPackageDefine, DWORD fid)
{
	for(int i=0; i<pPackageDefine->fieldUseCount; i++)
	{
		if(fid == pPackageDefine->fieldUse[i].fid)
			return pPackageDefine->fieldUse[i].pFieldDescribe;
	}
	return NULL;
}

void XMLNode2XTPPackage(CXMLNode *pNode, CXTPPackage *pPackage)
{
	DWORD	Tid = strtol(pNode->findProperty("tid"), NULL, 16);
	pPackage->PrepareRequest(Tid);
	pPackage->SetFrontID(atoi(pNode->findProperty("frontid")));
	pPackage->SetSessionID(atoi(pNode->findProperty("sessionid")));
	TPackageDefine **pFind = g_XTPPackageDefineMap.Find(Tid);
	if(pFind == NULL)
	{
		fprintf(stderr, "XMLNode2XTPPackage Can't find package define tid=%s\n",pNode->findProperty("tid"));
		return;
	}
	
	TPackageDefine *pPackageDefine = *pFind;
	CXMLNodeList *pList = pNode->getNodeList();

	if(NULL == pList)
		return;
	int i;
	vector<StringMap *> vecSM;

	for(i=0; i<pList->size(); i++)
	{
		StringMap *pSM = new StringMap();
		XMLNode2StringMap(pList->at(i), pSM);
		vecSM.push_back(pSM);
	}

	
	for(i=0; i<vecSM.size(); i++)
	{
		StringMap * pSM = vecSM[i];
		CFieldDescribe *pFieldDescribe = FindFieldDescribe(pPackageDefine,strtol(((*pSM)["fid"]).c_str(), NULL, 16));
		if(NULL == pFieldDescribe)
		{
			//不应该出现，可能是输入的xml文件和用pump生产代码的xml文件不一致造成。
			RAISE_DESIGN_ERROR("可能是输入的xml文件和用pump生产代码的xml文件不一致造成。");
		}
		char buf[10000];
		for (int j=0; j<pFieldDescribe->GetMemberCount(); j++)
		{
			TMemberDesc *pMemberDesc=pFieldDescribe->GetMemberDesc(j);
			char *pMember = buf+pMemberDesc->nStructOffset;

			switch(pMemberDesc->nType)
			{
			case FT_WORD:
			     *((WORD *)pMember) = atoi((*pSM)[pMemberDesc->szName].c_str());
			     break;
			case FT_DWORD:			
			     *((DWORD *)pMember) = atol((*pSM)[pMemberDesc->szName].c_str());
			     break;
			case FT_BYTE:
			     if (pMemberDesc->nSize == 1)
			     {
				*pMember = (*pSM)[pMemberDesc->szName].c_str()[0];
			     }
			     else
			     {
				strcpy(pMember, (*pSM)[pMemberDesc->szName].c_str());
			     }
			     break;
			case FT_REAL4:
			     if(!strcmp((*pSM)[pMemberDesc->szName].c_str(), ""))
				*((REAL4 *)pMember) = FLT_MAX;
			     else
				*((REAL4 *)pMember) = atof((*pSM)[pMemberDesc->szName].c_str());
			     break;
			case FT_REAL8:
			     if(!strcmp((*pSM)[pMemberDesc->szName].c_str(), ""))
				*((REAL8 *)pMember) = DBL_MAX;
			     else
				*((REAL8 *)pMember) = atof((*pSM)[pMemberDesc->szName].c_str());
			     break;
			}
		}
		pPackage->AddField(pFieldDescribe, buf);
	}

	for(i=0; i<vecSM.size(); i++)
	{
		delete vecSM[i];
	}
	
}

struct meta
{
	int depth;
	CXMLNode *package;
};

void startElement(void *userData, const char *name, CXMLNode *node)
{
	struct meta *p = (struct meta *)userData;
	int *depth = &(p->depth);
	*depth += 1;
	if (*depth == 2) {
		p->package = node;
	} else if (*depth == 3) {
		p->package->addNode(node);
	} else {
		delete node;
	}
}
	
bool endElement(void *userData, const char *name)
{
	struct meta *p = (struct meta *)userData;
	int *depth = &(p->depth);
	*depth -= 1;
	if (*depth == 0 || *depth == 1) {
		return false;
	}
	
	return true;
}

void XML2Flow(FILE *fpXML, char *pszPath)
{
	try
	{
		CFileFlow *m_pTradeSeries = new CFileFlow("", pszPath, false);

		CXMLDoc *pDoc;
		pDoc=new CXMLDoc;

		FILE *m_pf;
		struct meta m_data;
		KEY m_key;

		m_pf = fpXML;
		if (m_pf == NULL) 
		{
			throw new CParseError("Can not open file", 0);
		}
		m_data.depth = 0;
		m_data.package = NULL;
		pDoc->setUserData(&m_data);
		m_key.input = m_pf;
		m_key.start = startElement;
		m_key.end = endElement;
		m_key.ignoreText = 1;
		m_key.depth = 0;
		m_key.shouldEnd = false;

		/*
		pDoc->read(fpXML);
		CXMLNode *pNode = pDoc->getRootNode();
		if(strcmp(pNode->getName(), "XTPPackages"))
		{
			fprintf(stderr, "error XML Format\n");
			return;
		}
		CXMLNodeList *pList = pNode->getNodeList();
		if(NULL == pList)
		{
			fprintf(stderr, "no packages\n");
			return;
		}
		*/
		CXTPPackage *pPackage = CXTPPackage::CreatePackage(XTP_PACKAGE_MAX_SIZE); 	
		//for(int i=0; i<pList->size(); i++)
		int i;
		for (i=0;;i++)
		{
			m_data.package = NULL;
			pDoc->readSax2(&m_key);
			if (m_key.depth == 0)
				break;

			XMLNode2XTPPackage(m_data.package, pPackage);
			//XTP_PACKAGE_DEBUG(pPackage);
			pPackage->MakePackage();
			m_pTradeSeries->Append(pPackage->Address(), pPackage->Length());

			delete m_data.package;
			if (i%1000==0)
			{
				printf("\r%d...",i);
			}
		}
		printf("\r%d...\n",i);
		delete pDoc;
		delete m_pTradeSeries;
	}
	catch (CParseError *pError)
	{
		printf("\n%s at %d\n",pError->getMsg(),pError->getLineNo());
	}
}
void Flow2XML(char *pszPath, FILE *fpXML)
{
	CFileFlow *m_pTradeSeries = new CFileFlow("", pszPath, true);
	//CCachedFlow *m_pPreSeries =  new CCachedFlow(false, 100000, 100000);
	//m_pPreSeries->AttachUnderFlow(m_pTradeSeries);
	//m_pPubFlow = new CTradePubFlow(m_pPreSeries);

	CXTPPackage pubPackage;
	pubPackage.ConstructAllocate(XTP_PACKAGE_MAX_SIZE, XTPHLEN);
	CFlowReader reader;
	//reader.AttachFlow(m_pPreSeries, 0);
	reader.AttachFlow(m_pTradeSeries, 0);

	int totalNode=m_pTradeSeries->GetCount();
	int id=0;

	CXMLDoc *pDoc;
	pDoc=new CXMLDoc;
	pDoc->setEncoding("gb2312");
	pDoc->setVersion("1.0");
	pDoc->setDoctype("..\\..\\datamodel\\envGenerated\\XTPPackage.dtd");
	pDoc->setRoot("XTPPackages");
	pDoc->writeHead(fpXML);

	fprintf(fpXML,"<XTPPackages>\n");

	for (;;)
	{
		if (id%1000==0)
		{
			printf("\r%d of %d...",id,totalNode);
			fflush(stdout);
		}
		pubPackage.Allocate(XTP_PACKAGE_MAX_SIZE+XTPHLEN);
		if (!reader.GetNext(&pubPackage)) 
		{
			break;
		}
		CXMLNode *pNodePackage = new CXMLNode();
		//_XTP_PACKAGE_DEBUG(&pubPackage, stderr);
		XTPPackage2XMLNode(&pubPackage, pNodePackage);
		//pRootNode->addNode(pNodePackage);
		pNodePackage->write(fpXML,1);
		//pNodePackage->destroy(true);
		delete pNodePackage;
		id++;
	}

	fprintf(fpXML,"</XTPPackages>\n");
	printf("\r%d of %d...\n",totalNode,totalNode);

	//pDoc->write(fpXML);

	delete pDoc;
	//delete m_pPreSeries;
	delete m_pTradeSeries;
}
