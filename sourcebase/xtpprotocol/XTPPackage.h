// XTPPackage.h: interface for the CXTPPackage class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_)
#define AFX_XTPPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FieldSet.h"
#include "Package.h"

#define XTP_PACKAGE_MAX_SIZE	2561
#define XTP_FIELDTYPE_SIZE		10

const BYTE CHAIN_CONTINUE	= 'C';		//还有后续的XTP报文
const BYTE CHAIN_LAST		= 'L';		//最后一个XTP报文

const BYTE XTP_REQUEST		= 'R';		//请求
const BYTE XTP_RESPONSE		= 'O';		//应答
const BYTE XTP_PUBLISH		= 'P';		//发布

/**XTP报文头结构
*/
struct	TXTPHeader
{
	BYTE	Type;				/**< 包类型（'P'发布，'R'请求，'O'应答） */
	BYTE	Chain;				/**< XTP报文的连续标志 */
	WORD	ContentLength;		/**< 除报头之外，各field长度和 */
	DWORD	SubjectID;			/**< 主题 */
	DWORD	Tid;				/**< XTP报文的id	*/
	DWORD	CommPhaseNo;		/**< 通讯阶段序号,每次更换序号，SequenceNo都从1重新开始 */
	DWORD	SequenceNo;			/**< XTP报文的序号 */
	DWORD	RequestID;			/**< 请求ID*/
	DWORD	SessionID;			/**< 请求发起者在前置的会话ID*/
	DWORD	FrontID;			/**< 交易前置的标识 */
	DWORD	GroupID;			/**< 订阅组标识*/
	DWORD   APIID;        
	bool    NoReplayFlag;		//是否是反演报文的表示，NoReplayFlag是true表示是不反演

	/**将成员变量的内容清0
	*/
	inline void Init();
	
	/**改变成员变量的字节序
	*/
	inline void ChangeEndian();

	/**将本对象的内容放入pStream，并改变字节序
	*@param pStream 存贮改变字节序后数据的缓冲区
	*/
	inline void ToStream(char *pStream);

	/**将pStream的数据放入本对象，并改变字节序
	*@param pStream 存贮改变字节序前数据的缓冲区
	*/
	inline void FromStream(char *pStream);
};

inline void TXTPHeader::Init()
{
	memset(this, 0 ,sizeof(TXTPHeader));
}

inline void TXTPHeader::ChangeEndian()
{
	CHANGE_ENDIAN(ContentLength);
	CHANGE_ENDIAN(SubjectID);
	CHANGE_ENDIAN(Tid);
	CHANGE_ENDIAN(CommPhaseNo);
	CHANGE_ENDIAN(SequenceNo);
	CHANGE_ENDIAN(RequestID);
	CHANGE_ENDIAN(SessionID);
	CHANGE_ENDIAN(FrontID);
	CHANGE_ENDIAN(GroupID);
	CHANGE_ENDIAN(APIID);
}

inline void TXTPHeader::ToStream(char *pStream)
{
	memcpy(pStream, this, sizeof(TXTPHeader));
	((TXTPHeader *)pStream)->ChangeEndian();
}

inline void TXTPHeader::FromStream(char *pStream)
{
	memcpy(this, pStream, sizeof(TXTPHeader));
	this->ChangeEndian();
}

const int  XTPHLEN	= sizeof(TXTPHeader);

/**定义了XTPProtocol协议层所识别的Package
*/
class  CXTPPackage : public CFieldSet
{
public:
	/**构造函数。出始化成员变量。
	*/
	CXTPPackage();
		
	/**析构函数
	*/
	virtual ~CXTPPackage();
	
	/**获得包的上层协议ID，用来路由
	* @return 返回包的上层协议ID
	*/
	virtual DWORD GetActiveID();
	
	/**解析出XTP报头，检查是否XTP报文，并解析每个域的偏移量
	* @return PROTERR_XTP_BADPACKAGAE 一个坏的XTP包文
	* @return >0 完整的XTP包
	*/
	virtual int ValidPackage();
	
	/**组装数据包
	* @return 0 组装成功
	* @return <0 组装失败
	*/
	virtual int MakePackage();
	//20150604 huwp 添加该函数
	/**组装没有自己buf的数据包
	* @return 0 组装成功
	* @return <0 组装失败
	*/
	int MakeNoBufPackage();
	/**获取XTP报文头指针
	*@return XTP报文头指针
	*/
	inline TXTPHeader *GetXTPHeader();
	
	/**复制一个新的XTP包
	* @return 复制出的新XTP包
	*/
	CXTPPackage *Clone();
	
	/**初始化成请求报文
	*@param tid XTP报文的id
	*@param chain XTP报文的连续标志
	*@remark 调用该方法后，即可向包中增加Field
	*/
	void PrepareRequest(DWORD tid, BYTE chain = CHAIN_LAST);
	
	/**根据请求报文初始化成应答报文
	*@param pRequest 请求XTP包
	*@param tid XTP报文的id
	*@param chain XTP报文的连续标志
	*@remark 调用该方法后，即可向包中增加Field
	*/
	void PrepareResponse(CXTPPackage *pRequest, DWORD tid, BYTE chain = CHAIN_LAST);
	
	/**初始化成发布报文
	*@param tid XTP报文的id
	*@param chain XTP报文的连续标志
	*@remark 调用该方法后，即可向包中增加Field
	*/
	void PreparePublish(DWORD tid, BYTE chain = CHAIN_LAST);

	/**获取XTP报文的id
	*@return XTP报文的id
	*/
	inline DWORD GetTid();

	/**设置XTP报文的id
	*@param tid 要设置的XTP报文的id
	*/
	inline void SetTid(DWORD tid);

	/**获取XTP报文的连续标志
	*@return XTP报文的连续标志
	*/
	inline BYTE GetChain();

	/**设置XTP报文的连续标志
	*@param chain XTP报文的连续标志
	*/
	inline void SetChain(BYTE chain);

	/**获取XTP报文的序号
	*@return XTP报文的序号
	*/
	inline DWORD GetSequenceNo();
	
	/**设置XTP报文的序号
	*@param SequenceNo XTP报文的序号
	*/
	inline void SetSequenceNo(DWORD SequenceNo);

	/**获取XTP报文的主题
	*@return XTP报文的主题
	*/
	inline DWORD GetSubjectID();

	/**设置XTP报文的主题
	*@param SequenceNo XTP报文的主题
	*/
	inline void SetSubjectID(DWORD SubjectID);
	
	/**获取XTP报文的请求ID
	*@return XTP报文的请求ID
	*/
	inline DWORD GetRequestID();
	inline void SetRequestID(DWORD RequestID);

	/**获取XTP报文的会话ID
	*@return XTP报文的会话ID
	*/
	inline DWORD GetSessionID();

	/**设置XTP报文的会话ID
	*@param SequenceNo XTP报文的会话ID
	*/
	inline void SetSessionID(DWORD SessionID);

	/**获取XTP报文的前置ID
	*@return XTP报文的前置ID
	*/
	inline DWORD GetFrontID();

	/**设置XTP报文的前置ID
	*@param SequenceNo XTP报文的前置ID
	*/
	inline void SetFrontID(DWORD FrontID);

	/**获取XTP报文的组标识
	*@return XTP报文的组标识
	*/
	inline DWORD GetGroupID();

	/**设置XTP报文的组标识
	*@param SequenceNo XTP报文的组标识
	*/
	inline void SetGroupID(DWORD GroupID);

	inline DWORD GetAPIID();

	inline void SetAPIID(DWORD ExchangeID);

	inline void SetNoReplayFlag(bool bReplay);
	inline bool GetNoReplayFlag();

	/**调试输出报文头
	*/
	void OutputHeader(CLogger *pLogger);

	/**创建一个XTP包，并分配空间。空间大小为保留空间＋XTP最大报文件长度
	* @param nReserve package保留空间大小
	* @retrun 创建出的XTP包
	*/
	static CXTPPackage *CreatePackage(int nHeaderReserve);

protected:
	TXTPHeader m_XTPHeader;	  /**< XTP报头*/
};

inline TXTPHeader *CXTPPackage::GetXTPHeader()
{ 
	return &m_XTPHeader;
}

inline DWORD CXTPPackage::GetTid()
{
	return m_XTPHeader.Tid;
}

inline void CXTPPackage::SetTid(DWORD tid)
{
	m_XTPHeader.Tid = tid;
}

inline BYTE CXTPPackage::GetChain()
{
	return m_XTPHeader.Chain;
}

inline void CXTPPackage::SetChain(BYTE chain)
{
	m_XTPHeader.Chain = chain;
}

inline DWORD CXTPPackage::GetSequenceNo()
{
	return m_XTPHeader.SequenceNo;
}

inline void CXTPPackage::SetSequenceNo(DWORD SequenceNo)
{
	m_XTPHeader.SequenceNo = SequenceNo;
}

inline DWORD CXTPPackage::GetSubjectID()
{
	return m_XTPHeader.SubjectID;
}

inline void CXTPPackage::SetSubjectID(DWORD SubjectID)
{
	m_XTPHeader.SubjectID = SubjectID;
}

inline DWORD CXTPPackage::GetRequestID()
{
	return m_XTPHeader.RequestID;
}

inline void CXTPPackage::SetRequestID(DWORD RequestID)
{
	m_XTPHeader.RequestID = RequestID;
}

inline DWORD CXTPPackage::GetSessionID()
{
	return m_XTPHeader.SessionID;
}

inline void CXTPPackage::SetSessionID(DWORD SessionID)
{
	m_XTPHeader.SessionID = SessionID;
}

inline DWORD CXTPPackage::GetFrontID()
{
	return m_XTPHeader.FrontID;
}

inline void CXTPPackage::SetFrontID(DWORD FrontID)
{
	m_XTPHeader.FrontID = FrontID;
}

inline DWORD CXTPPackage::GetGroupID()
{
	return m_XTPHeader.GroupID;
}

inline void CXTPPackage::SetGroupID(DWORD GroupID)
{
	m_XTPHeader.GroupID = GroupID;
}
inline DWORD CXTPPackage::GetAPIID()
{
	return m_XTPHeader.APIID;
}
inline void CXTPPackage::SetAPIID(DWORD ExchangeID)
{
	m_XTPHeader.APIID = ExchangeID;
}
inline void CXTPPackage::SetNoReplayFlag(bool bNoReplay)
{
	m_XTPHeader.NoReplayFlag = bNoReplay;
}
inline bool CXTPPackage::GetNoReplayFlag()
{
	return m_XTPHeader.NoReplayFlag;
}

#define XTP_GET_SINGLE_FIELD(pPackage, pField)	((pPackage)->GetSingleField(&((pField)->m_Describe), (pField)))
#define XTP_ADD_FIELD(pPackage, pField) ((pPackage)->AddField(&((pField)->m_Describe), (pField)))

#ifndef DEBUG_NOT_LOG
#define XTP_HEADER_DEBUG(pPackage)											\
	{ if (UseNetPackageLog)	(pPackage)->OutputHeader(CLogger::GetInstance()); }
#define XTP_PACKAGE_DEBUG(pPackage)											\
{																			\
	if (UseNetPackageLog)													\
	{																		\
		(pPackage)->OutputHeader(CLogger::GetInstance());						\
		XTP_DEBUG_BODY((pPackage)->GetTid(), pPackage, CLogger::GetInstance());	\
	}																		\
}
#else
#define XTP_HEADER_DEBUG(pPackage)
#define XTP_PACKAGE_DEBUG(pPackage)
#endif
#endif // !defined(AFX_XTPPACKAGE_H__266F38F0_E245_4E93_89AB_65BC7D438E18__INCLUDED_)
