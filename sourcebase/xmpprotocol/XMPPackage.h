// XMPPackage.h: interface for the CXMPPackage class .
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMPPACKAGE_H__6238837B_1BF1_4671_A846_646A4E8DADC7__INCLUDED_)
#define AFX_XMPPACKAGE_H__6238837B_1BF1_4671_A846_646A4E8DADC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Package.h"
#include "FieldDescribe.h"

#define XMP_PACKAGE_MAX_SIZE	4096
#define XMP_EXTHEAD_MAX_SIZE	127

#define XMPTagNone				0x00
#define XMPTagDatetime			0x01
#define XMPTagCompressMethod	0x02
#define XMPTagTransactionId		0x03
#define XMPTagSessionState		0x04
#define XMPTagKeepAlive			0x05
#define XMPTagTradedate			0x06
#define XMPTagHeartbeatTimeOut	0x07

/**XMP报头
*/
struct TXMPHeader
{
	BYTE Type;			/**< 标示上层协议的协议ID */	
	BYTE ExtensionLen;	/**< 扩展报文长度 */
	WORD Length;		/**< 包体长度 */
	
	inline void Init();
	inline void ChangeEndian();
	inline void ToStream(char *pStream);
	inline void FromStream(char *pStream);
};

inline void TXMPHeader::Init()
{
	memset(this, 0 ,sizeof(TXMPHeader));
}

inline void TXMPHeader::ChangeEndian()
{
	CHANGE_ENDIAN(Length);
}

inline void TXMPHeader::ToStream(char *pStream)
{
	memcpy(pStream, this, sizeof(TXMPHeader));
	((TXMPHeader *)pStream)->ChangeEndian();
}

inline void TXMPHeader::FromStream(char *pStream)
{
	memcpy(this, pStream, sizeof(TXMPHeader));
	ChangeEndian();
}


/**扩展XMP报头
*/
struct TXMPExtHeader
{
	BYTE Tag;		/**< 状态标示　*/
	BYTE TagLen;	/**< 扩展包的长度 */
	BYTE Data[XMP_EXTHEAD_MAX_SIZE];	/**< 扩展包包体 */
	inline void Init();
};

inline void TXMPExtHeader::Init()
{
	memset(this, 0 ,sizeof(TXMPExtHeader));
}

//#pragma pack(4)

const int XMPHLEN = sizeof(TXMPHeader);
const int XMPEXTHLEN = 2;

/**定义了XMPProtocol协议层所识别的Package
*/
class  CXMPPackage : public CPackage  
{
public:
	/**构造函数
	*/
	CXMPPackage();
	
	/**析构函数
	*/
	virtual ~CXMPPackage();
	
	/**获得包的上层协议ID，用来路由
	* @return 返回包的上层协议ID
	*/
	virtual DWORD GetActiveID();
	
	/**检查是否XMP报文，并解析出XMP报头
	* @return PROTERR_XMP_BADPACKAGE 一个坏的XMP包文
	* @return >0 完整的XMP包
	* @return 0  部分的XMP包
	*/
	virtual int ValidPackage();
	
	/**组装数据包
	* @return 0 组装成功
	* @return <0 组装失败
	*/
	virtual int MakePackage();

	inline TXMPHeader *GetXMPHeader();
	/**获得包体的长度，包括XTP报头
	* @return 包体的长度，包括XTP报头
	*/
	inline int GetBodyLength();
	
	/**获得扩展报头的长度
	* @return 扩展报头的长度
	*/
	inline BYTE GetExtensionLen();
	
	/**获得扩展报头的标示
	* @return 扩展报头的标示
	*/
	inline BYTE GetExtTag();
	
	/**获得扩展报头内容的长度
	* @return 扩展报头内容的长度
	*/
	inline BYTE GetExtTagLen();

	/**获得扩展报头的内容
	*@return 扩展报头的内容
	*/
	inline BYTE *GetExtData();

	/**设置扩展报头内容
	*@param Tag 扩展报头的标示
	*@param TagLen 扩展报头内容的长度
	*@param pData 扩展报头的内容
	*/
	void SetExtHeader(BYTE Tag, BYTE TagLen, BYTE *pData );
protected:
	TXMPHeader m_XMPHeader;		/**< XMP报头 */
	TXMPExtHeader m_ExtHeader;	/**< XMP扩展报头 */
};

inline TXMPHeader *CXMPPackage::GetXMPHeader()
{
	return &m_XMPHeader;
}

inline int CXMPPackage::GetBodyLength()
{
	return m_XMPHeader.Length;
}

inline BYTE CXMPPackage::GetExtensionLen()
{
	return m_XMPHeader.ExtensionLen;
}

inline BYTE CXMPPackage::GetExtTag()
{
	return m_ExtHeader.Tag;
}

inline BYTE CXMPPackage::GetExtTagLen()
{
	return m_ExtHeader.TagLen;
}

inline BYTE *CXMPPackage::GetExtData()
{
	return m_ExtHeader.Data;
}


#endif // !defined(AFX_XMPPACKAGE_H__6238837B_1BF1_4671_A846_646A4E8DADC7__INCLUDED_)
