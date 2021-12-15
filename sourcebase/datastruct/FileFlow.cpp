// FileFlow.cpp: implementation of the CFileFlow class.
//
// 20070828 hwp 修改异常退出的方式
//////////////////////////////////////////////////////////////////////
#include "public.h"
#include "FileFlow.h"

#ifdef LINUX
//这个头文件是为了用函数 sync() 20141031 longqy
#include <unistd.h>
#endif

#define BLOCK_SIZE	100

struct TFlowId
{
	DWORD dwSize;                       //对象长度
	void ChangeEndian()
	{
		CHANGE_ENDIAN(dwSize);
	}
};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFileFlow::CFileFlow(const char *pszFlowName, const char *pszPath, bool bReuse)
{
	m_nCount= 0;
	FPOS_SET(m_nContentSize,0);
	m_fpIdFile=NULL;
	m_fpContentFile=NULL;
	m_nCommPhaseNo = 0;
	
	// 下面两行移动到OpenFile函数的前面，以免可能值没有初始化，就在OpenFile中使用 longqy 2013.1.16
	m_nReadId = -1;
	FPOS_SET(m_nReadOffset,0);

	OpenFile(pszFlowName, pszPath, bReuse);
	INIT_CRITICAL_VAR(m_criticalVar);

}
CFileFlow::CFileFlow(int nFlowID, const char *pszPath, bool bReuse)
{
	char szFlowName[20];
	sprintf(szFlowName, "%08x", nFlowID);
	new (this) CFileFlow(szFlowName, pszPath, bReuse);
}

CFileFlow::~CFileFlow()
{
	DELETE_CRITICAL_VAR(m_criticalVar);
	CloseFile();
}

int CFileFlow::GetCount(void)
{
	return m_nCount;
}

const int *CFileFlow::GetCountPtr(void)
{
	return &m_nCount;
}

fpos_t CFileFlow::GetContentSize(void)
{
	return m_nContentSize;
}

int CFileFlow::Append(void *pObject, int length)
{
	// 2014-07-01 减少临界区，把临界区的边界往下移动
	ENTER_CRITICAL(m_criticalVar);
	TFlowId flowId;
	flowId.dwSize=length;	
	flowId.ChangeEndian();	

	fsetpos(m_fpContentFile, &m_nContentSize);
	
	if (fwrite(&flowId,sizeof(flowId),1,m_fpContentFile)!=1)
		EMERGENCY_EXIT("Can not write content file for CFlow");

	if (fwrite(pObject,1,length,m_fpContentFile) != (size_t)length)
		EMERGENCY_EXIT("Can not write content file for CFlow");
	//2014-06-25 longqy 不flush文件，提高性能
	//20150805 xuzh  如果不fflush,导致落地文件出错，读取时i>=BLOCK_SIZE
	fflush(m_fpContentFile);

	FPOS_SET(m_nContentSize,FPOS_GET(m_nContentSize)+length+sizeof(flowId));
	m_nCount++;

	if(m_nCount%BLOCK_SIZE==0)
	{
		m_BlockOffset.push_back(m_nContentSize);
		fseek(m_fpIdFile,0,SEEK_END);
		//fpos_t dwOffset = m_nContentSize;
		//20120130 begin xuzh 支持各个平台的流文件
		//INT8这个命名在windows下已经有定义了，会产生编译redefinition错误，更名为UF_INT8
		UF_INT8 dwOffset = FPOS_GET(m_nContentSize);
		CHANGE_ENDIAN(dwOffset);
		if (fwrite(&dwOffset,sizeof(dwOffset),1,m_fpIdFile)!=1)
			EMERGENCY_EXIT("Can not write id file for CFlow");
		//20120130 end
		//2014-06-25 longqy 不flush文件，提高性能
		//20150805 xuzh  如果不fflush,导致落地文件出错，读取时i>=BLOCK_SIZE
		fflush(m_fpIdFile);
	}
	LEAVE_CRITICAL(m_criticalVar);
	return m_nCount-1;
}

fpos_t CFileFlow::GetOffset(int id)
{
	fpos_t offset;
	FPOS_SET(offset, 0);
	if (m_nReadId+1 == id)
	{
		offset = m_nReadOffset;
	}
	else
	{
		TFlowId flowId;
		int i=id/BLOCK_SIZE;
		offset=m_BlockOffset[i];
	// 2014-07-01 减少临界区，把临界区的边界往下移动
		ENTER_CRITICAL(m_criticalVar);
		for(i*=BLOCK_SIZE;i<id;i++){
			fsetpos(m_fpContentFile, &offset);
			if(fread(&flowId,sizeof(flowId),1,m_fpContentFile)!=1)
				EMERGENCY_EXIT("Can not read content file for CFlow");
			flowId.ChangeEndian();
			FPOS_SET(offset,FPOS_GET(offset)+flowId.dwSize+sizeof(flowId));
		}
		LEAVE_CRITICAL(m_criticalVar);
	}
	return offset;
}

int CFileFlow::Get(int id, void *pObject, int length)
{
	// 2014-07-01 减少临界区，把临界区的边界往下移动
	fpos_t offset = GetOffset(id); 
	TFlowId flowId;
	ENTER_CRITICAL(m_criticalVar);
	fsetpos(m_fpContentFile, &offset);
	if(fread(&flowId,sizeof(flowId),1,m_fpContentFile)!=1)
		EMERGENCY_EXIT("Can not read content file for CFlow");
	flowId.ChangeEndian();

	if (flowId.dwSize>length)
		EMERGENCY_EXIT("Insufficient buffer length while reading CFlow");

	if (fread(pObject,1,flowId.dwSize,m_fpContentFile)!=(size_t)flowId.dwSize)
		EMERGENCY_EXIT("Can not read content file for CFlow");

	m_nReadId = id;
	FPOS_SET(m_nReadOffset,FPOS_GET(offset) + flowId.dwSize + sizeof(flowId));
	LEAVE_CRITICAL(m_criticalVar);
	
	return flowId.dwSize;
}

void CFileFlow::OpenFile(const char *pszFlowName, const char *pszPath, bool bReuse)
{
	ASSERT(pszPath != NULL);
	
	CloseFile();
	
	char szIdFilename[512];
	char szContentFilename[512];
	sprintf(szIdFilename, "%s%s.id",pszPath, pszFlowName);
	sprintf(szContentFilename, "%s%s.con", pszPath, pszFlowName);

	m_nCount=0;
	FPOS_SET(m_nContentSize,0);

	m_BlockOffset.clear();

	fpos_t firstOffset;
	FPOS_SET(firstOffset, 0);
	m_BlockOffset.push_back(firstOffset);

	m_fpIdFile=mfopen(szIdFilename,"a+b");
	m_fpContentFile=mfopen(szContentFilename,"a+b");
	if ((m_fpIdFile==NULL)||(m_fpContentFile==NULL))
	{
		CloseFile();
		EMERGENCY_EXIT("can not open CFlow file");
	}
	
	if (!bReuse)
	{
		if (!InitFile())
		{
			CloseFile();
			EMERGENCY_EXIT("can not init CFlow file");
		}
		return ;
	}

#ifdef WIN32	
	struct _stati64 statbuf;
	int result = _stati64( szContentFilename, &statbuf );
#else
	struct stat statbuf;
	int result = stat( szContentFilename, &statbuf );
#endif
	if( result != 0 )
		EMERGENCY_EXIT( "Problem getting file information" );

	FPOS_SET(m_nContentSize,statbuf.st_size);
		
	fpos_t size;
	FPOS_SET(size,0);
	fseek(m_fpIdFile,0,SEEK_SET);
	if(fread(&m_nCommPhaseNo, sizeof(m_nCommPhaseNo), 1, m_fpIdFile) != 1)
	{
		if (!InitFile())
		{
			CloseFile();
			EMERGENCY_EXIT("can not init CFlow file");
		}
		return ;
	}
	CHANGE_ENDIAN(m_nCommPhaseNo);
	for(;;)
	{
		//20120130 begin xuzh 支持各个平台的流文件
		UF_INT8 dwOffset = 0;
		if(fread(&dwOffset,sizeof(dwOffset),1,m_fpIdFile)!=1)break;
		CHANGE_ENDIAN(dwOffset);
		fpos_t fpOffset;
		FPOS_SET(fpOffset,dwOffset);
		//20120130 end
		m_BlockOffset.push_back(fpOffset);
		size=fpOffset;
		m_nCount+=BLOCK_SIZE;
	}
	TFlowId flowId;
	int i;
	for(i=0;;i++)
	{
		if(fsetpos(m_fpContentFile, &size)!=0)
		{
			EMERGENCY_EXIT("fsetpos failed");
		}
		if(fread(&flowId,sizeof(flowId),1,m_fpContentFile)!=1)
			break;
		flowId.ChangeEndian();
		FPOS_SET(size,FPOS_GET(size)+flowId.dwSize+sizeof(flowId));
	}
 	if(FPOS_GET(size)!=FPOS_GET(m_nContentSize) || i>=BLOCK_SIZE )
	{
		// EMERGENCY_EXIT("size!=m_nContentSize || i>=BLOCK_SIZE");
		// 在文件大小不匹配的情况下，不强制退出，以便继续反演。 20141029 longqy
		REPORT_EVENT(LOG_EMERGENCY , "Flow file and Id file size not match!",":%s in line %d of file %s\n","size!=m_nContentSize || i>=BLOCK_SIZE",__LINE__,__FILE__);		
	}

	m_nCount+=i;
}

bool CFileFlow::InitFile()
{
	m_nContentSize = GetOffset(m_nCount);
	int nIdCount = m_nCount/BLOCK_SIZE;
	m_BlockOffset.resize(nIdCount+1);

#ifdef WIN32
	if(chsize(fileno(m_fpIdFile), nIdCount) != 0)
	{
		return false;
	}
	if(chsize(fileno(m_fpContentFile), m_nContentSize) != 0)
	{
		return false;
	}
#else
	ftruncate(fileno(m_fpIdFile), nIdCount);
	ftruncate(fileno(m_fpContentFile), FPOS_GET(m_nContentSize));
#endif
	if (fseek(m_fpIdFile, 0, SEEK_SET) != 0)
	{
		return false;
	}
	WORD nCommPhaseNo = m_nCommPhaseNo;
	CHANGE_ENDIAN(nCommPhaseNo);
	if(fwrite(&nCommPhaseNo, sizeof(nCommPhaseNo), 1, m_fpIdFile) != 1)
	{
		return false;
	}
	fflush(m_fpIdFile);
	return true;
}

void CFileFlow::CloseFile()
{
	if(m_fpIdFile != NULL){
		fclose(m_fpIdFile);
		m_fpIdFile = NULL;
	}
	if(m_fpContentFile != NULL){
		fclose(m_fpContentFile);
		m_fpContentFile = NULL;
	}
}

WORD CFileFlow::GetCommPhaseNo()
{
	return m_nCommPhaseNo;
}

void CFileFlow::SetCommPhaseNo(WORD nCommPhaseNo)
{
	if (nCommPhaseNo != m_nCommPhaseNo)
	{
		m_nCommPhaseNo = nCommPhaseNo;
		m_nCount= 0;
		InitFile();
	}
}

bool CFileFlow::Truncate(int nCount)
{
	if (m_nCount <= nCount)
	{
		return true;
	}
	m_nCount= nCount;
	return InitFile();
}

void CFileFlow::FlushToDisk(void)
{
	fflush(m_fpContentFile);
	fflush(m_fpIdFile);
	// 参数NULL 是把所有的文件缓冲信息都写入硬盘
	fflush(NULL);
	
#ifdef LINUX
	sync();	
#endif

}