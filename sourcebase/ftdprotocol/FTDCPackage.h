// FTDCPackage.h: interface for the CFTDCPackage class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTDCPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_)
#define AFX_FTDCPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FieldSet.h"
#include "Package.h"

#define FTDC_PACKAGE_MAX_SIZE	4000

const BYTE FTDC_CHAIN_CONTINUE	= 'C';		//报文链的中间FTDC报文。
const BYTE FTDC_CHAIN_LAST		= 'L';		//报文链的最后一个FTDC报文。

/**FTDC报文头结构
*/
struct	TFTDCHeader
{
	BYTE	Version;			/**< 版本号	1	二进制无符号整数。目前版本为1*/
	BYTE	Chain;				/**< 报文链	1	ASCII码字符。*/
	WORD	SequenceSeries;		/**< 序列类别号	2	二进制无符号短整数。*/
	DWORD	TransactionId;		/**<（TID）	FTD信息正文类型	4	二进制无符号整数。*/
	DWORD	SequenceNumber;		/**<（SeqNo）	序列号	4	二进制无符号整数。*/
	WORD	FieldCount;			/**< 数据域数量	2	二进制无符号短整数。*/
	WORD	FTDCContentLength;	/**< FTDC信息正文长度	2	二进制无符号短整数。以字节为单位。*/
	DWORD	RequestId;			/**< 请求编号(由发送请求者维护，应答中会带回)  4 二进制无符号整数。*/
	
	inline void Init();
	inline void ChangeEndian();
	inline void ToStream(char *pStream);
	inline void FromStream(char *pStream);
};

inline void TFTDCHeader::Init()
{
	memset(this, 0 ,sizeof(TFTDCHeader));
}

inline void TFTDCHeader::ChangeEndian()
{
	CHANGE_ENDIAN(SequenceSeries);
	CHANGE_ENDIAN(TransactionId);
	CHANGE_ENDIAN(SequenceNumber);
	CHANGE_ENDIAN(FieldCount);
	CHANGE_ENDIAN(FTDCContentLength);
	CHANGE_ENDIAN(RequestId);
}

inline void TFTDCHeader::ToStream(char *pStream)
{
	memcpy(pStream, this, sizeof(TFTDCHeader));
	((TFTDCHeader *)pStream)->ChangeEndian();
}

inline void TFTDCHeader::FromStream(char *pStream)
{
	memcpy(this, pStream, sizeof(TFTDCHeader));
	ChangeEndian();
}

const int  FTDCHLEN	= sizeof(TFTDCHeader);

/**定义了FTDCProtocol协议层所识别的Package
*/
class  CFTDCPackage : public CFieldSet
{
public:
	/**构造函数。出始化成员变量。
	*/
	CFTDCPackage();
		
	/**析构函数
	*/
	virtual ~CFTDCPackage();
	
	/**获得包的上层协议ID，用来路由
	* @return 返回包的上层协议ID
	*/
	virtual DWORD GetActiveID();
	
	/**解析出XMP报头，检查是否FTDC报文，并解析每个域的偏移量
	* @return PROTERR_FTDC_BADPACKAGAE 一个坏的FTDC包文
	* @return >0 完整的FTDC包
	*/
	virtual int ValidPackage();
	
	virtual int MakePackage();

	inline TFTDCHeader *GetFTDCHeader();
		
	inline DWORD GetTID();

	inline void SetChain(BYTE chain);

	inline BYTE GetChain();
	
	inline void SetRequestId(DWORD requestId);

	inline DWORD GetRequestId();
	
	inline BYTE GetVersion();
	
	void PreparePackage(DWORD tid, BYTE chain, BYTE version);

	void PrepareResponse(CFTDCPackage *pRequest, DWORD tid, BYTE chain, BYTE version);

	void OutputHeader(CLogger *pLogger);

	/**创建一个FTDC包，并分配空间。空间大小为保留空间＋FTDC最大报文件长度
	* @param nReserve package保留空间大小
	* @retrun 创建出的FTDC包
	*/
	static CFTDCPackage *CreatePackage(int nHeaderReserve);

protected:
	TFTDCHeader m_FTDCHeader;	  /**< FTDC报头*/
};

inline TFTDCHeader *CFTDCPackage::GetFTDCHeader()
{ 
	return &m_FTDCHeader;
}

inline DWORD CFTDCPackage::GetTID()
{
	return m_FTDCHeader.TransactionId;
}

inline void CFTDCPackage::SetChain(BYTE chain)
{
	m_FTDCHeader.Chain = chain;
}

inline BYTE CFTDCPackage::GetChain()
{
	return m_FTDCHeader.Chain;
}

inline void CFTDCPackage::SetRequestId(DWORD requestId)
{
	m_FTDCHeader.RequestId =requestId;
}

inline DWORD CFTDCPackage::GetRequestId()
{
	return m_FTDCHeader.RequestId;
}

inline BYTE CFTDCPackage::GetVersion()
{
	return m_FTDCHeader.Version;
}

#define FTDC_GET_SINGLE_FIELD(pPackage, pField)	((pPackage)->GetSingleField(&((pField)->m_Describe), (pField)))
#define FTDC_ADD_FIELD(pPackage, pField) ((pPackage)->AddField(&((pField)->m_Describe), (pField)))

#ifndef DEBUG_NOT_LOG
#define FTDC_HEADER_DEBUG(pPackage)											\
	{ if (UseNetPackageLog) (pPackage)->OutputHeader(CLogger::GetInstance()); }
#define FTDC_PACKAGE_DEBUG(pPackage)										\
{																			\
	if (UseNetPackageLog)													\
	{																		\
		(pPackage)->OutputHeader(CLogger::GetInstance());						\
		FTDC_DEBUG_BODY((pPackage)->GetTID(), pPackage, CLogger::GetInstance());\
	}																		\
}
#else
#define FTDC_HEADER_DEBUG(pPackage)
#define FTDC_PACKAGE_DEBUG(pPackage)
#endif

#endif // !defined(AFX_FTDCPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_)
