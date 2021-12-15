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
#include <dl.h>

//static const char *g_sORA8DLLName = "/home/oracle/production/10.1.0.2/lib/libclntsh.so";
static const char *g_sORA8DLLName = "libclntsh.so";
//static void *g_hORA8DLL = NULL;
shl_t g_hORA8DLL;
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
		long nVersion = ::SAGetFileVersionFromString(g_sORA8DLLName);
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
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIInitialize", TYPE_UNDEFINED, &g_ora8API.OCIInitialize);
	assert(g_ora8API.OCIInitialize != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIHandleAlloc", TYPE_UNDEFINED, &g_ora8API.OCIHandleAlloc);
	assert(g_ora8API.OCIHandleAlloc != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIHandleFree", TYPE_UNDEFINED, &g_ora8API.OCIHandleFree);
	assert(g_ora8API.OCIHandleFree != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDescriptorAlloc", TYPE_UNDEFINED, &g_ora8API.OCIDescriptorAlloc);
	assert(g_ora8API.OCIDescriptorAlloc != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDescriptorFree", TYPE_UNDEFINED, &g_ora8API.OCIDescriptorFree);
	assert(g_ora8API.OCIDescriptorFree != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIEnvInit", TYPE_UNDEFINED, &g_ora8API.OCIEnvInit);
	assert(g_ora8API.OCIEnvInit != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIServerAttach", TYPE_UNDEFINED, &g_ora8API.OCIServerAttach);
	assert(g_ora8API.OCIServerAttach != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIServerDetach", TYPE_UNDEFINED, &g_ora8API.OCIServerDetach);
	assert(g_ora8API.OCIServerDetach != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCISessionBegin", TYPE_UNDEFINED, &g_ora8API.OCISessionBegin);
	assert(g_ora8API.OCISessionBegin != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCISessionEnd", TYPE_UNDEFINED, &g_ora8API.OCISessionEnd);
	assert(g_ora8API.OCISessionEnd != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILogon", TYPE_UNDEFINED, &g_ora8API.OCILogon);
	assert(g_ora8API.OCILogon != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILogoff", TYPE_UNDEFINED, &g_ora8API.OCILogoff);
	assert(g_ora8API.OCILogoff != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIPasswordChange", TYPE_UNDEFINED, &g_ora8API.OCIPasswordChange);
	assert(g_ora8API.OCIPasswordChange != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtPrepare", TYPE_UNDEFINED, &g_ora8API.OCIStmtPrepare);
	assert(g_ora8API.OCIStmtPrepare != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBindByPos", TYPE_UNDEFINED, &g_ora8API.OCIBindByPos);
	assert(g_ora8API.OCIBindByPos != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBindByName", TYPE_UNDEFINED, &g_ora8API.OCIBindByName);
	assert(g_ora8API.OCIBindByName != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBindObject", TYPE_UNDEFINED, &g_ora8API.OCIBindObject);
	assert(g_ora8API.OCIBindObject != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBindDynamic", TYPE_UNDEFINED, &g_ora8API.OCIBindDynamic);
	assert(g_ora8API.OCIBindDynamic != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBindArrayOfStruct", TYPE_UNDEFINED, &g_ora8API.OCIBindArrayOfStruct);
	assert(g_ora8API.OCIBindArrayOfStruct != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtGetPieceInfo", TYPE_UNDEFINED, &g_ora8API.OCIStmtGetPieceInfo);
	assert(g_ora8API.OCIStmtGetPieceInfo != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtSetPieceInfo", TYPE_UNDEFINED, &g_ora8API.OCIStmtSetPieceInfo);
	assert(g_ora8API.OCIStmtSetPieceInfo != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtExecute", TYPE_UNDEFINED, &g_ora8API.OCIStmtExecute);
	assert(g_ora8API.OCIStmtExecute != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDefineByPos", TYPE_UNDEFINED, &g_ora8API.OCIDefineByPos);
	assert(g_ora8API.OCIDefineByPos != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDefineObject", TYPE_UNDEFINED, &g_ora8API.OCIDefineObject);
	assert(g_ora8API.OCIDefineObject != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDefineDynamic", TYPE_UNDEFINED, &g_ora8API.OCIDefineDynamic);
	assert(g_ora8API.OCIDefineDynamic != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDefineArrayOfStruct", TYPE_UNDEFINED, &g_ora8API.OCIDefineArrayOfStruct);
	assert(g_ora8API.OCIDefineArrayOfStruct != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtFetch", TYPE_UNDEFINED, &g_ora8API.OCIStmtFetch);
	assert(g_ora8API.OCIStmtFetch != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIStmtGetBindInfo", TYPE_UNDEFINED, &g_ora8API.OCIStmtGetBindInfo);
	assert(g_ora8API.OCIStmtGetBindInfo != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDescribeAny", TYPE_UNDEFINED, &g_ora8API.OCIDescribeAny);
	assert(g_ora8API.OCIDescribeAny != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIParamGet", TYPE_UNDEFINED, &g_ora8API.OCIParamGet);	
	assert(g_ora8API.OCIParamGet != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIParamSet", TYPE_UNDEFINED, &g_ora8API.OCIParamSet);
	assert(g_ora8API.OCIParamSet != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransStart", TYPE_UNDEFINED, &g_ora8API.OCITransStart);
	assert(g_ora8API.OCITransStart != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransDetach", TYPE_UNDEFINED, &g_ora8API.OCITransDetach);
	assert(g_ora8API.OCITransDetach != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransCommit", TYPE_UNDEFINED, &g_ora8API.OCITransCommit);
	assert(g_ora8API.OCITransCommit != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransRollback", TYPE_UNDEFINED, &g_ora8API.OCITransRollback);
	assert(g_ora8API.OCITransRollback != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransPrepare", TYPE_UNDEFINED, &g_ora8API.OCITransPrepare);	
	assert(g_ora8API.OCITransPrepare != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIParamSet", TYPE_UNDEFINED, &g_ora8API.OCIParamSet);
	assert(g_ora8API.OCIParamSet != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransStart", TYPE_UNDEFINED, &g_ora8API.OCITransStart);
	assert(g_ora8API.OCITransStart != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransDetach", TYPE_UNDEFINED, &g_ora8API.OCITransDetach);
	assert(g_ora8API.OCITransDetach != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransCommit", TYPE_UNDEFINED, &g_ora8API.OCITransCommit);
	assert(g_ora8API.OCITransCommit != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransRollback", TYPE_UNDEFINED, &g_ora8API.OCITransRollback);
	assert(g_ora8API.OCITransRollback != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransPrepare", TYPE_UNDEFINED, &g_ora8API.OCITransPrepare);	
	assert(g_ora8API.OCITransPrepare != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCITransForget", TYPE_UNDEFINED, &g_ora8API.OCITransForget);
	assert(g_ora8API.OCITransForget != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIErrorGet", TYPE_UNDEFINED, &g_ora8API.OCIErrorGet);
	assert(g_ora8API.OCIErrorGet != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobAppend", TYPE_UNDEFINED, &g_ora8API.OCILobAppend);
	assert(g_ora8API.OCILobAppend != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobAssign", TYPE_UNDEFINED, &g_ora8API.OCILobAssign);
	assert(g_ora8API.OCILobAssign != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobCharSetForm", TYPE_UNDEFINED, &g_ora8API.OCILobCharSetForm);
	assert(g_ora8API.OCILobCharSetForm != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobCharSetId", TYPE_UNDEFINED, &g_ora8API.OCILobCharSetId);	
	assert(g_ora8API.OCILobCharSetId != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobCopy", TYPE_UNDEFINED, &g_ora8API.OCILobCopy);
	assert(g_ora8API.OCILobCopy != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobDisableBuffering", TYPE_UNDEFINED, &g_ora8API.OCILobDisableBuffering);
	assert(g_ora8API.OCILobDisableBuffering != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobEnableBuffering", TYPE_UNDEFINED, &g_ora8API.OCILobEnableBuffering);
	assert(g_ora8API.OCILobEnableBuffering != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobErase", TYPE_UNDEFINED, &g_ora8API.OCILobErase);
	assert(g_ora8API.OCILobErase != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileClose", TYPE_UNDEFINED, &g_ora8API.OCILobFileClose);
	assert(g_ora8API.OCILobFileClose != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileCloseAll", TYPE_UNDEFINED, &g_ora8API.OCILobFileCloseAll);
	assert(g_ora8API.OCILobFileCloseAll != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileExists", TYPE_UNDEFINED, &g_ora8API.OCILobFileExists);
	assert(g_ora8API.OCILobFileExists != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileGetName", TYPE_UNDEFINED, &g_ora8API.OCILobFileGetName);
	assert(g_ora8API.OCILobFileGetName != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileIsOpen", TYPE_UNDEFINED, &g_ora8API.OCILobFileIsOpen);
	assert(g_ora8API.OCILobFileIsOpen != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileOpen", TYPE_UNDEFINED, &g_ora8API.OCILobFileOpen);
	assert(g_ora8API.OCILobFileOpen != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFileSetName", TYPE_UNDEFINED, &g_ora8API.OCILobFileSetName);
	assert(g_ora8API.OCILobFileSetName != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFlushBuffer", TYPE_UNDEFINED, &g_ora8API.OCILobFlushBuffer);	
	assert(g_ora8API.OCILobFlushBuffer != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobGetLength", TYPE_UNDEFINED, &g_ora8API.OCILobGetLength);
	assert(g_ora8API.OCILobGetLength != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobIsEqual", TYPE_UNDEFINED, &g_ora8API.OCILobIsEqual);
	assert(g_ora8API.OCILobIsEqual != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobLoadFromFile", TYPE_UNDEFINED, &g_ora8API.OCILobLoadFromFile);
	assert(g_ora8API.OCILobLoadFromFile != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobLocatorIsInit", TYPE_UNDEFINED, &g_ora8API.OCILobLocatorIsInit);
	assert(g_ora8API.OCILobLocatorIsInit != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobRead", TYPE_UNDEFINED, &g_ora8API.OCILobRead);
	assert(g_ora8API.OCILobRead != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobTrim", TYPE_UNDEFINED, &g_ora8API.OCILobTrim);	
	assert(g_ora8API.OCILobTrim != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobWrite", TYPE_UNDEFINED, &g_ora8API.OCILobWrite);
	assert(g_ora8API.OCILobWrite != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBreak", TYPE_UNDEFINED, &g_ora8API.OCIBreak);
	assert(g_ora8API.OCIBreak != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIReset", TYPE_UNDEFINED, &g_ora8API.OCIReset);
	assert(g_ora8API.OCIReset != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIServerVersion", TYPE_UNDEFINED, &g_ora8API.OCIServerVersion);
	assert(g_ora8API.OCIServerVersion != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIAttrGet", TYPE_UNDEFINED, &g_ora8API.OCIAttrGet);
	assert(g_ora8API.OCIAttrGet != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIAttrSet", TYPE_UNDEFINED, &g_ora8API.OCIAttrSet);	
	assert(g_ora8API.OCIAttrSet != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobWrite", TYPE_UNDEFINED, &g_ora8API.OCILobWrite);
	assert(g_ora8API.OCILobWrite != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIBreak", TYPE_UNDEFINED, &g_ora8API.OCIBreak);
	assert(g_ora8API.OCIBreak != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIReset", TYPE_UNDEFINED, &g_ora8API.OCIReset);
	assert(g_ora8API.OCIReset != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIServerVersion", TYPE_UNDEFINED, &g_ora8API.OCIServerVersion);
	assert(g_ora8API.OCIServerVersion != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIAttrGet", TYPE_UNDEFINED, &g_ora8API.OCIAttrGet);
	assert(g_ora8API.OCIAttrGet != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIAttrSet", TYPE_UNDEFINED, &g_ora8API.OCIAttrSet);	
	assert(g_ora8API.OCIAttrSet != NULL);
	
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCISvcCtxToLda", TYPE_UNDEFINED, &g_ora8API.OCISvcCtxToLda);
	assert(g_ora8API.OCISvcCtxToLda != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILdaToSvcCtx", TYPE_UNDEFINED, &g_ora8API.OCILdaToSvcCtx);
	assert(g_ora8API.OCILdaToSvcCtx != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIResultSetToStmt", TYPE_UNDEFINED, &g_ora8API.OCIResultSetToStmt);
	assert(g_ora8API.OCIResultSetToStmt != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIEnvCreate", TYPE_UNDEFINED, &g_ora8API.OCIEnvCreate);
	assert(g_ora8API.OCIEnvCreate != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDurationBegin", TYPE_UNDEFINED, &g_ora8API.OCIDurationBegin);
	assert(g_ora8API.OCIDurationBegin != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCIDurationEnd ", TYPE_UNDEFINED, &g_ora8API.OCIDurationEnd );	
	assert(g_ora8API.OCIDurationEnd != NULL);
	
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobCreateTemporary", TYPE_UNDEFINED, &g_ora8API.OCILobCreateTemporary);
	assert(g_ora8API.OCILobCreateTemporary != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobFreeTemporary", TYPE_UNDEFINED, &g_ora8API.OCILobFreeTemporary);
	assert(g_ora8API.OCILobFreeTemporary != NULL);
	shl_findsym((shl_t*) &g_hORA8DLL, "OCILobIsTemporary ", TYPE_UNDEFINED, &g_ora8API.OCILobIsTemporary );	
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
		sprintf(strpath, "%s/%s", getenv("OCI_PATH"), g_sORA8DLLName);

//		sprintf(strpath, "%s%s", "SHLIB_PATH=" ,getenv("SHLIB_PATH"));
//		putenv(strpath);
		//printf("strpath=%s\n",strpath);
		//dld_getenv();
		//g_hORA8DLL = shl_load(g_sORA8DLLName, BIND_IMMEDIATE|DYNAMIC_PATH , 0);
		g_hORA8DLL = shl_load(strpath, BIND_IMMEDIATE|DYNAMIC_PATH , 0);
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

