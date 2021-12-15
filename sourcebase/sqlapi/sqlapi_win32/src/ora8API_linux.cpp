// ora8API_linux.cpp
//
//////////////////////////////////////////////////////////////////////

#include <SQLAPI.h>
#include <oraAPI.h>

#include <assert.h>

#include "samisc.h"
#include "errmsg.h"

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

static const char *g_sORA8DLLName = "libclntsh.so";
//static void *g_hORA8DLL = NULL;
void * g_hORA8DLL;
long g_nORA8DLLVersionLoaded = 0;
static long g_nORA8DLLRefs = 0;

// API definitions
ora8API g_ora8API;

ora8API::ora8API()
{
	// 8.0.x calls
	OCIInitialize	= NULL;
	OCIHandleAlloc	= NULL;
	OCIHandleFree	= NULL;
	OCIDescriptorAlloc	= NULL;
	OCIDescriptorFree	= NULL;
	OCIEnvInit	= NULL;
	OCIServerAttach	= NULL;
	OCIServerDetach	= NULL;
	OCISessionBegin	= NULL;
	OCISessionEnd	= NULL;
	OCILogon	= NULL;
	OCILogoff	= NULL;
	OCIPasswordChange	= NULL;
	OCIStmtPrepare	= NULL;
	OCIBindByPos	= NULL;
	OCIBindByName	= NULL;
	OCIBindObject	= NULL;
	OCIBindDynamic	= NULL;
	OCIBindArrayOfStruct	= NULL;
	OCIStmtGetPieceInfo	= NULL;
	OCIStmtSetPieceInfo	= NULL;
	OCIStmtExecute	= NULL;
	OCIDefineByPos	= NULL;
	OCIDefineObject	= NULL;
	OCIDefineDynamic	= NULL;
	OCIDefineArrayOfStruct	= NULL;
	OCIStmtFetch	= NULL;
	OCIStmtGetBindInfo	= NULL;
	OCIDescribeAny	= NULL;
	OCIParamGet	= NULL;
	OCIParamSet	= NULL;
	OCITransStart	= NULL;
	OCITransDetach	= NULL;
	OCITransCommit	= NULL;
	OCITransRollback	= NULL;
	OCITransPrepare	= NULL;
	OCITransForget	= NULL;
	OCIErrorGet	= NULL;
	OCILobAppend	= NULL;
	OCILobAssign	= NULL;
	OCILobCharSetForm	= NULL;
	OCILobCharSetId	= NULL;
	OCILobCopy	= NULL;
	OCILobDisableBuffering	= NULL;
	OCILobEnableBuffering	= NULL;
	OCILobErase	= NULL;
	OCILobFileClose	= NULL;
	OCILobFileCloseAll	= NULL;
	OCILobFileExists	= NULL;
	OCILobFileGetName	= NULL;
	OCILobFileIsOpen	= NULL;
	OCILobFileOpen	= NULL;
	OCILobFileSetName	= NULL;
	OCILobFlushBuffer	= NULL;
	OCILobGetLength	= NULL;
	OCILobIsEqual	= NULL;
	OCILobLoadFromFile	= NULL;
	OCILobLocatorIsInit	= NULL;
	OCILobRead	= NULL;
	OCILobTrim	= NULL;
	OCILobWrite	= NULL;
	OCIBreak	= NULL;
	OCIReset	= NULL;
	OCIServerVersion	= NULL;
	OCIAttrGet	= NULL;
	OCIAttrSet	= NULL;
	OCISvcCtxToLda	= NULL;
	OCILdaToSvcCtx	= NULL;
	OCIResultSetToStmt	= NULL;

	// 8.1.x (8i) calls
	OCIEnvCreate	= NULL;
	OCIDurationBegin	= NULL;
	OCIDurationEnd	= NULL;
	OCILobCreateTemporary	= NULL;
	OCILobFreeTemporary	= NULL;
	OCILobIsTemporary	= NULL;
};

ora8ConnectionHandles::ora8ConnectionHandles()
{
	m_pOCIEnv		= NULL;
	m_pOCIError		= NULL;
	m_pOCISvcCtx	= NULL;
	m_pOCIServer	= NULL;
	m_pOCISession	= NULL;
}

ora8CommandHandles::ora8CommandHandles()
{
	m_pOCIStmt		= NULL;
	m_pOCIError		= NULL;
}

// detects if OCI8 is available
bool CanBeLoadedOCI8()
{
	if(g_hORA8DLL)
		return true;	// already loaded

	return true;

/*	
	try
	{
		long nVersion) = ::SAGetFileVersionFromString(g_sORA8DLLName);
		return HIWORD(nVersion) >= 8;
	}
	catch(SAException &)
	{
	}

	return false;
*/
}

static void LoadAPI()
{
	
	*(void **)(&g_ora8API.OCIInitialize) = dlsym(g_hORA8DLL, "OCIInitialize");
	assert(g_ora8API.OCIInitialize != NULL);
	
	*(void **)(&g_ora8API.OCIHandleAlloc) = dlsym(g_hORA8DLL, "OCIHandleAlloc");
	assert(g_ora8API.OCIHandleAlloc != NULL);
	
	*(void **)(&g_ora8API.OCIHandleFree) = dlsym(g_hORA8DLL, "OCIHandleFree");
	assert(g_ora8API.OCIHandleFree != NULL);
	*(void **)(&g_ora8API.OCIDescriptorAlloc) = dlsym(g_hORA8DLL, "OCIDescriptorAlloc");
	assert(g_ora8API.OCIDescriptorAlloc != NULL);
	*(void **)(&g_ora8API.OCIDescriptorFree) = dlsym(g_hORA8DLL, "OCIDescriptorFree");
	assert(g_ora8API.OCIDescriptorFree != NULL);
	*(void **)(&g_ora8API.OCIEnvInit) = dlsym(g_hORA8DLL, "OCIEnvInit");
	assert(g_ora8API.OCIEnvInit != NULL);
	
	*(void **)(&g_ora8API.OCIServerAttach) = dlsym(g_hORA8DLL, "OCIServerAttach");
	assert(g_ora8API.OCIServerAttach != NULL);
	*(void **)(&g_ora8API.OCIServerDetach) = dlsym(g_hORA8DLL, "OCIServerDetach");
	assert(g_ora8API.OCIServerDetach != NULL);
	*(void **)(&g_ora8API.OCISessionBegin) = dlsym(g_hORA8DLL, "OCISessionBegin");
	assert(g_ora8API.OCISessionBegin != NULL);
	*(void **)(&g_ora8API.OCISessionEnd) = dlsym(g_hORA8DLL, "OCISessionEnd");
	assert(g_ora8API.OCISessionEnd != NULL);
	*(void **)(&g_ora8API.OCILogon) = dlsym(g_hORA8DLL, "OCILogon");
	assert(g_ora8API.OCILogon != NULL);
	*(void **)(&g_ora8API.OCILogoff) = dlsym(g_hORA8DLL, "OCILogoff");
	assert(g_ora8API.OCILogoff != NULL);
	
	*(void **)(&g_ora8API.OCIPasswordChange) = dlsym(g_hORA8DLL, "OCIPasswordChange");
	assert(g_ora8API.OCIPasswordChange != NULL);
	*(void **)(&g_ora8API.OCIStmtPrepare) = dlsym(g_hORA8DLL, "OCIStmtPrepare");
	assert(g_ora8API.OCIStmtPrepare != NULL);
	*(void **)(&g_ora8API.OCIBindByPos) = dlsym(g_hORA8DLL, "OCIBindByPos");
	assert(g_ora8API.OCIBindByPos != NULL);
	*(void **)(&g_ora8API.OCIBindByName) = dlsym(g_hORA8DLL, "OCIBindByName");
	assert(g_ora8API.OCIBindByName != NULL);
	*(void **)(&g_ora8API.OCIBindObject) = dlsym(g_hORA8DLL, "OCIBindObject");
	assert(g_ora8API.OCIBindObject != NULL);
	*(void **)(&g_ora8API.OCIBindDynamic) = dlsym(g_hORA8DLL, "OCIBindDynamic");
	assert(g_ora8API.OCIBindDynamic != NULL);
	*(void **)(&g_ora8API.OCIBindArrayOfStruct) = dlsym(g_hORA8DLL, "OCIBindArrayOfStruct");
	assert(g_ora8API.OCIBindArrayOfStruct != NULL);
	*(void **)(&g_ora8API.OCIStmtGetPieceInfo) = dlsym(g_hORA8DLL, "OCIStmtGetPieceInfo");
	assert(g_ora8API.OCIStmtGetPieceInfo != NULL);
	*(void **)(&g_ora8API.OCIStmtSetPieceInfo) = dlsym(g_hORA8DLL, "OCIStmtSetPieceInfo");
	assert(g_ora8API.OCIStmtSetPieceInfo != NULL);
	*(void **)(&g_ora8API.OCIStmtExecute) = dlsym(g_hORA8DLL, "OCIStmtExecute");
	assert(g_ora8API.OCIStmtExecute != NULL);
	*(void **)(&g_ora8API.OCIDefineByPos) = dlsym(g_hORA8DLL, "OCIDefineByPos");
	assert(g_ora8API.OCIDefineByPos != NULL);
	*(void **)(&g_ora8API.OCIDefineObject) = dlsym(g_hORA8DLL, "OCIDefineObject");
	assert(g_ora8API.OCIDefineObject != NULL);
	
	*(void **)(&g_ora8API.OCIDefineDynamic) = dlsym(g_hORA8DLL, "OCIDefineDynamic");
	assert(g_ora8API.OCIDefineDynamic != NULL);
	*(void **)(&g_ora8API.OCIDefineArrayOfStruct) = dlsym(g_hORA8DLL, "OCIDefineArrayOfStruct");
	assert(g_ora8API.OCIDefineArrayOfStruct != NULL);
	*(void **)(&g_ora8API.OCIStmtFetch) = dlsym(g_hORA8DLL, "OCIStmtFetch");
	assert(g_ora8API.OCIStmtFetch != NULL);
	*(void **)(&g_ora8API.OCIStmtGetBindInfo) = dlsym(g_hORA8DLL, "OCIStmtGetBindInfo");
	assert(g_ora8API.OCIStmtGetBindInfo != NULL);
	*(void **)(&g_ora8API.OCIDescribeAny) = dlsym(g_hORA8DLL, "OCIDescribeAny");
	assert(g_ora8API.OCIDescribeAny != NULL);
	*(void **)(&g_ora8API.OCIParamGet) = dlsym(g_hORA8DLL, "OCIParamGet");	
	assert(g_ora8API.OCIParamGet != NULL);
	
	*(void **)(&g_ora8API.OCIParamSet) = dlsym(g_hORA8DLL, "OCIParamSet");
	assert(g_ora8API.OCIParamSet != NULL);
	*(void **)(&g_ora8API.OCITransStart) = dlsym(g_hORA8DLL, "OCITransStart");
	assert(g_ora8API.OCITransStart != NULL);
	*(void **)(&g_ora8API.OCITransDetach) = dlsym(g_hORA8DLL, "OCITransDetach");
	assert(g_ora8API.OCITransDetach != NULL);
	*(void **)(&g_ora8API.OCITransCommit) = dlsym(g_hORA8DLL, "OCITransCommit");
	assert(g_ora8API.OCITransCommit != NULL);
	*(void **)(&g_ora8API.OCITransRollback) = dlsym(g_hORA8DLL, "OCITransRollback");
	assert(g_ora8API.OCITransRollback != NULL);
	*(void **)(&g_ora8API.OCITransPrepare) = dlsym(g_hORA8DLL, "OCITransPrepare");	
	assert(g_ora8API.OCITransPrepare != NULL);
	
	*(void **)(&g_ora8API.OCIParamSet) = dlsym(g_hORA8DLL, "OCIParamSet");
	assert(g_ora8API.OCIParamSet != NULL);
	*(void **)(&g_ora8API.OCITransStart) = dlsym(g_hORA8DLL, "OCITransStart");
	assert(g_ora8API.OCITransStart != NULL);
	*(void **)(&g_ora8API.OCITransDetach) = dlsym(g_hORA8DLL, "OCITransDetach");
	assert(g_ora8API.OCITransDetach != NULL);
	*(void **)(&g_ora8API.OCITransCommit) = dlsym(g_hORA8DLL, "OCITransCommit");
	assert(g_ora8API.OCITransCommit != NULL);
	*(void **)(&g_ora8API.OCITransRollback) = dlsym(g_hORA8DLL, "OCITransRollback");
	assert(g_ora8API.OCITransRollback != NULL);
	*(void **)(&g_ora8API.OCITransPrepare) = dlsym(g_hORA8DLL, "OCITransPrepare");	
	assert(g_ora8API.OCITransPrepare != NULL);
	
	*(void **)(&g_ora8API.OCITransForget) = dlsym(g_hORA8DLL, "OCITransForget");
	assert(g_ora8API.OCITransForget != NULL);
	*(void **)(&g_ora8API.OCIErrorGet) = dlsym(g_hORA8DLL, "OCIErrorGet");
	assert(g_ora8API.OCIErrorGet != NULL);
	*(void **)(&g_ora8API.OCILobAppend) = dlsym(g_hORA8DLL, "OCILobAppend");
	assert(g_ora8API.OCILobAppend != NULL);
	*(void **)(&g_ora8API.OCILobAssign) = dlsym(g_hORA8DLL, "OCILobAssign");
	assert(g_ora8API.OCILobAssign != NULL);
	*(void **)(&g_ora8API.OCILobCharSetForm) = dlsym(g_hORA8DLL, "OCILobCharSetForm");
	assert(g_ora8API.OCILobCharSetForm != NULL);
	*(void **)(&g_ora8API.OCILobCharSetId) = dlsym(g_hORA8DLL, "OCILobCharSetId");	
	assert(g_ora8API.OCILobCharSetId != NULL);
	
	*(void **)(&g_ora8API.OCILobCopy) = dlsym(g_hORA8DLL, "OCILobCopy");
	assert(g_ora8API.OCILobCopy != NULL);
	*(void **)(&g_ora8API.OCILobDisableBuffering) = dlsym(g_hORA8DLL, "OCILobDisableBuffering");
	assert(g_ora8API.OCILobDisableBuffering != NULL);
	*(void **)(&g_ora8API.OCILobEnableBuffering) = dlsym(g_hORA8DLL, "OCILobEnableBuffering");
	assert(g_ora8API.OCILobEnableBuffering != NULL);
	*(void **)(&g_ora8API.OCILobErase) = dlsym(g_hORA8DLL, "OCILobErase");
	assert(g_ora8API.OCILobErase != NULL);
	*(void **)(&g_ora8API.OCILobFileClose) = dlsym(g_hORA8DLL, "OCILobFileClose");
	assert(g_ora8API.OCILobFileClose != NULL);
	*(void **)(&g_ora8API.OCILobFileCloseAll) = dlsym(g_hORA8DLL, "OCILobFileCloseAll");
	assert(g_ora8API.OCILobFileCloseAll != NULL);
	
	*(void **)(&g_ora8API.OCILobFileExists) = dlsym(g_hORA8DLL, "OCILobFileExists");
	assert(g_ora8API.OCILobFileExists != NULL);
	*(void **)(&g_ora8API.OCILobFileGetName) = dlsym(g_hORA8DLL, "OCILobFileGetName");
	assert(g_ora8API.OCILobFileGetName != NULL);
	*(void **)(&g_ora8API.OCILobFileIsOpen) = dlsym(g_hORA8DLL, "OCILobFileIsOpen");
	assert(g_ora8API.OCILobFileIsOpen != NULL);
	*(void **)(&g_ora8API.OCILobFileOpen) = dlsym(g_hORA8DLL, "OCILobFileOpen");
	assert(g_ora8API.OCILobFileOpen != NULL);
	*(void **)(&g_ora8API.OCILobFileSetName) = dlsym(g_hORA8DLL, "OCILobFileSetName");
	assert(g_ora8API.OCILobFileSetName != NULL);
	*(void **)(&g_ora8API.OCILobFlushBuffer) = dlsym(g_hORA8DLL, "OCILobFlushBuffer");	
	assert(g_ora8API.OCILobFlushBuffer != NULL);
	
	*(void **)(&g_ora8API.OCILobGetLength) = dlsym(g_hORA8DLL, "OCILobGetLength");
	assert(g_ora8API.OCILobGetLength != NULL);
	*(void **)(&g_ora8API.OCILobIsEqual) = dlsym(g_hORA8DLL, "OCILobIsEqual");
	assert(g_ora8API.OCILobIsEqual != NULL);
	*(void **)(&g_ora8API.OCILobLoadFromFile) = dlsym(g_hORA8DLL, "OCILobLoadFromFile");
	assert(g_ora8API.OCILobLoadFromFile != NULL);
	*(void **)(&g_ora8API.OCILobLocatorIsInit) = dlsym(g_hORA8DLL, "OCILobLocatorIsInit");
	assert(g_ora8API.OCILobLocatorIsInit != NULL);
	*(void **)(&g_ora8API.OCILobRead) = dlsym(g_hORA8DLL, "OCILobRead");
	assert(g_ora8API.OCILobRead != NULL);
	*(void **)(&g_ora8API.OCILobTrim) = dlsym(g_hORA8DLL, "OCILobTrim");	
	assert(g_ora8API.OCILobTrim != NULL);
	
	*(void **)(&g_ora8API.OCILobWrite) = dlsym(g_hORA8DLL, "OCILobWrite");
	assert(g_ora8API.OCILobWrite != NULL);
	*(void **)(&g_ora8API.OCIBreak) = dlsym(g_hORA8DLL, "OCIBreak");
	assert(g_ora8API.OCIBreak != NULL);
	*(void **)(&g_ora8API.OCIReset) = dlsym(g_hORA8DLL, "OCIReset");
	assert(g_ora8API.OCIReset != NULL);
	*(void **)(&g_ora8API.OCIServerVersion) = dlsym(g_hORA8DLL, "OCIServerVersion");
	assert(g_ora8API.OCIServerVersion != NULL);
	*(void **)(&g_ora8API.OCIAttrGet) = dlsym(g_hORA8DLL, "OCIAttrGet");
	assert(g_ora8API.OCIAttrGet != NULL);
	*(void **)(&g_ora8API.OCIAttrSet) = dlsym(g_hORA8DLL, "OCIAttrSet");	
	assert(g_ora8API.OCIAttrSet != NULL);
	
	*(void **)(&g_ora8API.OCILobWrite) = dlsym(g_hORA8DLL, "OCILobWrite");
	assert(g_ora8API.OCILobWrite != NULL);
	*(void **)(&g_ora8API.OCIBreak) = dlsym(g_hORA8DLL, "OCIBreak");
	assert(g_ora8API.OCIBreak != NULL);
	*(void **)(&g_ora8API.OCIReset) = dlsym(g_hORA8DLL, "OCIReset");
	assert(g_ora8API.OCIReset != NULL);
	*(void **)(&g_ora8API.OCIServerVersion) = dlsym(g_hORA8DLL, "OCIServerVersion");
	assert(g_ora8API.OCIServerVersion != NULL);
	*(void **)(&g_ora8API.OCIAttrGet) = dlsym(g_hORA8DLL, "OCIAttrGet");
	assert(g_ora8API.OCIAttrGet != NULL);
	*(void **)(&g_ora8API.OCIAttrSet) = dlsym(g_hORA8DLL, "OCIAttrSet");	
	assert(g_ora8API.OCIAttrSet != NULL);
	
	
	*(void **)(&g_ora8API.OCISvcCtxToLda) = dlsym(g_hORA8DLL, "OCISvcCtxToLda");
	assert(g_ora8API.OCISvcCtxToLda != NULL);
	*(void **)(&g_ora8API.OCILdaToSvcCtx) = dlsym(g_hORA8DLL, "OCILdaToSvcCtx");
	assert(g_ora8API.OCILdaToSvcCtx != NULL);
	*(void **)(&g_ora8API.OCIResultSetToStmt) = dlsym(g_hORA8DLL, "OCIResultSetToStmt");
	assert(g_ora8API.OCIResultSetToStmt != NULL);
	*(void **)(&g_ora8API.OCIEnvCreate) = dlsym(g_hORA8DLL, "OCIEnvCreate");
	assert(g_ora8API.OCIEnvCreate != NULL);
	*(void **)(&g_ora8API.OCIDurationBegin) = dlsym(g_hORA8DLL, "OCIDurationBegin");
	assert(g_ora8API.OCIDurationBegin != NULL);
	*(void **)(&g_ora8API.OCIDurationEnd) = dlsym(g_hORA8DLL, "OCIDurationEnd " );	
	assert(g_ora8API.OCIDurationEnd != NULL);
	
	*(void **)(&g_ora8API.OCILobCreateTemporary) = dlsym(g_hORA8DLL, "OCILobCreateTemporary");
	assert(g_ora8API.OCILobCreateTemporary != NULL);
	*(void **)(&g_ora8API.OCILobFreeTemporary) = dlsym(g_hORA8DLL, "OCILobFreeTemporary");
	assert(g_ora8API.OCILobFreeTemporary != NULL);
	*(void **)(&g_ora8API.OCILobIsTemporary) = dlsym(g_hORA8DLL, "OCILobIsTemporary " );	
	assert(g_ora8API.OCILobIsTemporary != NULL);
}



static void ResetAPI()
{
	// 8.0.x calls
	g_ora8API.OCIInitialize	= NULL;
	g_ora8API.OCIHandleAlloc	= NULL;
	g_ora8API.OCIHandleFree	= NULL;
	g_ora8API.OCIDescriptorAlloc	= NULL;
	g_ora8API.OCIDescriptorFree	= NULL;
	g_ora8API.OCIEnvInit	= NULL;
	g_ora8API.OCIServerAttach	= NULL;
	g_ora8API.OCIServerDetach	= NULL;
	g_ora8API.OCISessionBegin	= NULL;
	g_ora8API.OCISessionEnd	= NULL;
	g_ora8API.OCILogon	= NULL;
	g_ora8API.OCILogoff	= NULL;
	g_ora8API.OCIPasswordChange	= NULL;
	g_ora8API.OCIStmtPrepare	= NULL;
	g_ora8API.OCIBindByPos	= NULL;
	g_ora8API.OCIBindByName	= NULL;
	g_ora8API.OCIBindObject	= NULL;
	g_ora8API.OCIBindDynamic	= NULL;
	g_ora8API.OCIBindArrayOfStruct	= NULL;
	g_ora8API.OCIStmtGetPieceInfo	= NULL;
	g_ora8API.OCIStmtSetPieceInfo	= NULL;
	g_ora8API.OCIStmtExecute	= NULL;
	g_ora8API.OCIDefineByPos	= NULL;
	g_ora8API.OCIDefineObject	= NULL;
	g_ora8API.OCIDefineDynamic	= NULL;
	g_ora8API.OCIDefineArrayOfStruct	= NULL;
	g_ora8API.OCIStmtFetch	= NULL;
	g_ora8API.OCIStmtGetBindInfo	= NULL;
	g_ora8API.OCIDescribeAny	= NULL;
	g_ora8API.OCIParamGet	= NULL;
	g_ora8API.OCIParamSet	= NULL;
	g_ora8API.OCITransStart	= NULL;
	g_ora8API.OCITransDetach	= NULL;
	g_ora8API.OCITransCommit	= NULL;
	g_ora8API.OCITransRollback	= NULL;
	g_ora8API.OCITransPrepare	= NULL;
	g_ora8API.OCITransForget	= NULL;
	g_ora8API.OCIErrorGet	= NULL;
	g_ora8API.OCILobAppend	= NULL;
	g_ora8API.OCILobAssign	= NULL;
	g_ora8API.OCILobCharSetForm	= NULL;
	g_ora8API.OCILobCharSetId	= NULL;
	g_ora8API.OCILobCopy	= NULL;
	g_ora8API.OCILobDisableBuffering	= NULL;
	g_ora8API.OCILobEnableBuffering	= NULL;
	g_ora8API.OCILobErase	= NULL;
	g_ora8API.OCILobFileClose	= NULL;
	g_ora8API.OCILobFileCloseAll	= NULL;
	g_ora8API.OCILobFileExists	= NULL;
	g_ora8API.OCILobFileGetName	= NULL;
	g_ora8API.OCILobFileIsOpen	= NULL;
	g_ora8API.OCILobFileOpen	= NULL;
	g_ora8API.OCILobFileSetName	= NULL;
	g_ora8API.OCILobFlushBuffer	= NULL;
	g_ora8API.OCILobGetLength	= NULL;
	g_ora8API.OCILobIsEqual	= NULL;
	g_ora8API.OCILobLoadFromFile	= NULL;
	g_ora8API.OCILobLocatorIsInit	= NULL;
	g_ora8API.OCILobRead	= NULL;
	g_ora8API.OCILobTrim	= NULL;
	g_ora8API.OCILobWrite	= NULL;
	g_ora8API.OCIBreak	= NULL;
	g_ora8API.OCIReset	= NULL;
	g_ora8API.OCIServerVersion	= NULL;
	g_ora8API.OCIAttrGet	= NULL;
	g_ora8API.OCIAttrSet	= NULL;
	g_ora8API.OCISvcCtxToLda	= NULL;
	g_ora8API.OCILdaToSvcCtx	= NULL;
	g_ora8API.OCIResultSetToStmt	= NULL;

	// 8.1.x (8i) calls
	g_ora8API.OCIEnvCreate	= NULL;
	g_ora8API.OCIDurationBegin	= NULL;
	g_ora8API.OCIDurationEnd	= NULL;
	g_ora8API.OCILobCreateTemporary	= NULL;
	g_ora8API.OCILobFreeTemporary	= NULL;
	g_ora8API.OCILobIsTemporary	= NULL;
}

void AddORA8Support()
{
	if(!g_hORA8DLL)
	{
		// load Oracle OCI8 API library
		char strpath[267];
		//sprintf(strpath, "%s/%s", getenv("OCI_PATH"), g_sORA8DLLName);
		sprintf(strpath, "%s", g_sORA8DLLName);
		printf("strpath=%s\n",strpath);
		g_hORA8DLL = dlopen(strpath, RTLD_NOW);
		if(!g_hORA8DLL)
			throw SAException(SA_Library_Error, -1, -1, IDS_LOAD_LIBRARY_FAILS, ::dlerror(), g_sORA8DLLName);

		LoadAPI();

		if(g_ora8API.OCIEnvCreate == NULL)	// use 8.0.x method of initialization
			g_ora8API.OCIInitialize(OCI_THREADED | OCI_OBJECT, NULL, NULL, NULL, NULL);
	}

	g_nORA8DLLRefs++;
}

void ReleaseORA8Support()
{
	assert(g_nORA8DLLRefs > 0);
	g_nORA8DLLRefs--;
	if(!g_nORA8DLLRefs)
	{
		ResetAPI();

//		dlclose(g_hORA8DLL);
		g_hORA8DLL = NULL;
	}
}

