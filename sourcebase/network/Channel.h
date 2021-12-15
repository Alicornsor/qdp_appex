// Channel.h: interface for the CChannel class .
//
// 2006.10.11	hwp	为支持SSL，增加方法 GetRemoteCommonName 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANNEL_H__3416C3E2_14B2_4E6C_B1C4_694DC2AF1F7D__INCLUDED_)
#define AFX_CHANNEL_H__3416C3E2_14B2_4E6C_B1C4_694DC2AF1F7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义了CChannel的类型
enum TChannelType
{
	CT_STREAM,
	CT_DATAGRAM
};

enum TChannelRecordType
{
	CLRT_CONNECTED,
	CLRT_READ,
	CLRT_WRITE,
	CLRT_READ_ERROR,
	CLRT_WRITE_ERROR,
	CLRT_DISCONNECT,
	CLRT_DISCONNECTED_READ,
	CLRT_DISCONNECTED_WRITE,
};

/**Channel事件在日志中的头
*/
struct TChannelLogHeader 
{
	DWORD dwId;					/**< Channel的句柄*/
	DWORD dwTime;				/**< 事件发生时间 */
	DWORD dwMsTime;					/**< 事件发生微秒  zbz 20111202 调整变量类型到DWORD*/
	WORD wType;					/**< 事件类型 */
	WORD wLength;				/**< 事件内容长度 */

	/**改变字节序
	*/
	void ChangeEndian()
	{
		CHANGE_ENDIAN(dwId);
		CHANGE_ENDIAN(dwTime);
		CHANGE_ENDIAN(dwMsTime);
		CHANGE_ENDIAN(wType);
		CHANGE_ENDIAN(wLength);
	}
};


/**CChannel是一个抽象的网络连接，实现了一个基于有连接通讯的基本功能。不同类型的
网络通讯需要继承这个类，以实其真正功能。
*/
class CFlow;
class  CChannel  
{
public:
	/**构造函数，设置类型和select用的文件号
	* @param type	读写类型，其值可以是READ_ONLY、WRITE_ONLY或者READ_WRITE
	* @param id	select用的文件号。如果本CChannel不能被select，而是只能用
	*		查询方式工作，则应当设为-1
	*/
	CChannel(TChannelType type, int id);
	
	/**析构函数，需要负责断开连接
	*/
	virtual ~CChannel();

	/**从本CChannel中读取，如果读不到，也应当立即返回，不能在此睡眠。本方法将使用
	* ReadImp完成真正的读取操作，在发生错误时，主动断开连接
	* @param	number	要读取的字节数，应当大于0
	* @param	buffer	读取的缓冲器地址
	* @return	读到的字节数。如果没有读到任何内容，则返回0。如果发现网络已经断路，则返回-1
	*/
	int Read(int number, char *buffer);
	
	
	/**从本CChannel中写出，如果无法写出，也应当立即返回，不能在此睡眠。本方法将使用writeImp完成真正的写出操作，在发生错误时，主动断开连接
	* @param	number	要写出的字节数，应当大于0
	* @param	buffer	写出的缓冲器地址
	* @return	完成写出的字节数。如果没有写出任何内容，则返回0。如果发现网络已经断路，则返回-1
	*/
	int Write(int number, char *buffer);
	
	/**判断本CChannel是否有内容可读。即使本方法返回有内容，也不保证read可以得到内容。本方法
	*主要对查询方式工作的CChannel比较有用。本方法将使用availableImp完成真正的检查操作
	*  @return   true表示有内容，false表示无内容
	*/
	bool Available(void);
	
	/**断开本连接。本方法将disconnectImp来完成真正的断开连接操作
	* @return	true表示还有连接，false表示完成断开
	*/
	bool Disconnect();
	
	/**检查连接是否有效。即使本方法返回连接有效，也不保证在进一步的read或者write的操作中不报告
	*网络已经断路。本方法将使用checkConnectionImp来完成真正的检查操作
	* @return true表示连接有效，false表示已经断开
	*/
	bool CheckConnection();
	
	/**获取对方的地址，例如其IP地址等
	* @return	对方的地址
	*/
	virtual char *GetRemoteName(void);
	
    /** 获取本地的地址IP
    * @return   本地地址  
    * lidp 20140716
    */
    virtual char *GetLocalName(void);
	/**获取对方的标识
	* @return	对方的标识
	* @remark   返回NULL表示未知
	*/
	virtual char *GetRemoteCommonName(void);
	
	/**获取select读用的文件号
	* @return	文件号
	*/
	virtual int GetSelectId(void);

	/**获取读写用的文件号
	* @return	文件号
	*/
	inline int GetId(void);

	/**获取Channel类型
	* @return Channel类型
	*/
	inline TChannelType GetType();

	/**设置日志文件指针, 并记录Channnel信息
	*@param fp 日志文件指针, NULL表示不记日志
	*@remark
	*/
	void SetLogFile(FILE *fp);

	/**取日志文件指针
	*@return 日志文件指针, NULL表示不记日志
	*/
	inline FILE * GetLogFile();
	
	//20130827 huwp 修改写slog慢的问题		
	/**设置日志流指针, 并记录Channnel信息
	*@param fp 日志文件指针, NULL表示不记日志
	*@remark
	*/
	void SetLogFlow(CFlow *fp);

	//20130827 huwp 修改写slog慢的问题		
	/**取日志流指针
	*@return 日志文件指针, NULL表示不记日志
	*/
	inline CFlow * GetLogFlow();
protected:
	/**从本CChannel内读取的实现方法，是纯虚函数，继承对象需要实现此方法
	* @param	number	要读取的字节数，应当大于0
	* @param	buffer	读取的缓冲器地址
	* @return	读到的字节数。如果没有读到任何内容，则返回0。如果发现网络已经断路或者有严重错误，则返回-1
	*/
	virtual int ReadImp(int number, char *buffer)=0;
	
	/**从本CChannel中写出的实现方法，是纯虚函数，继承对象需要实现此方法
	* @param	number	要写出的字节数，应当大于0
	* @param	buffer	写出的缓冲器地址
	* @return	完成写出的字节数。如果没有写出任何内容，则返回0。如果发现网络已经断路或者有严重错误，则返回-1
	*/
	virtual int WriteImp(int number, char *buffer)=0;
	
	/**判断本CChannel是否有内容可读的实现函数。即使本方法返回有内容，也不保证readImp可以得到内容。
	*本方法主要对查询方式工作的CChannel比较有用。本函数是纯虚函数，继承对象需要实现此方法
	* @return 1表示有内容，0表示无内容
	*/
	virtual bool AvailableImp(void)=0;
	
	/**断开本连接的实现函数，是纯虚函数，继承对象需要实现此方法
	* @return true表示还有连接，false表示完成断开
	*/
	virtual bool DisconnectImp(void)=0;
	
	/**检查连接是否有效。即使本方法返回连接有效，也不保证在进一步的readImp或者writeImp的操作中不报告
	*网络已经断路，或者有严重错误。本方法是纯虚函数，继承对象需要实现此方法
	* @return	true表示连接有效，false表示已经断开
	*/
	virtual bool CheckConnectionImp(void)=0;

	/**写日志
	*@param wType 日志记录类型
	*@param wDataLength 日志记录数据长度
	*@param pData 日志记录数据内容
	*/
	void WriteLog(WORD wType, WORD wDataLength, const char *pData);
protected:	
	TChannelType m_nType;		/**< 读写类型 */
	bool m_bConnected;			/**< 是否处于连接状态 */
	int m_nID;					/**< select时用的id */
	FILE *m_fpLog;				/**< 日志文件指针 */
	//20130827 huwp 修改写slog慢的问题		
	CFlow *m_pFlowLog;				/**< 日志文件指针 */
};

inline int CChannel::GetId(void)
{
	return m_nID;
}

inline TChannelType CChannel::GetType()
{
	return m_nType;
}

inline FILE * CChannel::GetLogFile()
{
	return m_fpLog;
}

inline CFlow * CChannel::GetLogFlow()
{
	return m_pFlowLog;
}

#endif // !defined(AFX_CHANNEL_H__3416C3E2_14B2_4E6C_B1C4_694DC2AF1F7D__INCLUDED_)
