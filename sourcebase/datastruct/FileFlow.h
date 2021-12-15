// FileFlow.h: interface for the CFileFlow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEFLOW_H__32B28836_A01C_4923_BBF0_10B313ED400C__INCLUDED_)
#define AFX_FILEFLOW_H__32B28836_A01C_4923_BBF0_10B313ED400C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "platform.h"
#include "Flow.h"

/**CFileFlow是文件流类，它使用两个文件来存贮包。一个文件保存包的偏移量，
* 另一个文件保存包的内容。为了提高速度，每BLOCK_SIZE个包保存一个偏移量。
* 文件名和文件所存贮的目录在构造时指定。
*/
class CFileFlow : public CFlow  
{
public:
	/**构造函数
	* @param pszFlowName 流文件的名称（真正的文件有两个，会自动加上"id"和"con"的扩展名
	* @param pszPath 流文件存贮的目录
	* @param bReuse	是否重用此文件,true重用文件，false原文件（若存在）将被覆盖
	* @异常	CRuntimeError	如果文件名为空或文件读写错误，则抛出此异常
	* @remark 如果重用文件，则构造时将检查文件的合法性。
	*/
	CFileFlow(const char *pszFlowName, const char *pszPath, bool bReuse);
	
	/**构造函数
	* @param nFlowID 数字表示的流文件的名称，nFlowID会按16进制转换成字符串做为文件名
	* @param pszFlowPath 流文件存贮的目录
	* @param bReuse 是否重用流文件
	* @param nMaxObjects 缓存包的最大数量
	* @param nDataBlockSize CacheList使用的数据区块大小，不要小于一个数据包的长度
	*/
	CFileFlow(int nFlowID, const char *pszPath, bool bReuse);
	
	virtual ~CFileFlow();

	/**获取流中已经有的包的个数
	*@return 包的个数
	*/
	virtual int GetCount(void);
	
	/**获取指向该流长度的指针
	*@return	指向该流长度的指针
	*/
	virtual const int *GetCountPtr(void);

	/**获取流的通讯阶段序号
	*@return 流的通讯阶段序号
	*/
	virtual WORD GetCommPhaseNo();

	/**设置流的通讯阶段序号
	*@param nCommPhaseNo 要设置的流的通讯阶段序号
	*/
	virtual void SetCommPhaseNo(WORD nCommPhaseNo);

	/**将流尾部的包截掉
	*@param nCount 保留的包的个数
	*/
	virtual bool Truncate(int nCount); 
	
	/**向流中增加一个对象
	*@param	pObject 要增加的对象
	*@param length 增加数据的长度
	*@return 对象在流中的序号，小于0表示增加失败
	*/
	virtual int Append(void *pObject, int length);

	/**获取指定编号的对象
	*@param	id	对象序号
	*@param pObject 获取对象的缓冲区
	*@param length 缓冲区大小
	*@return 取出对象的长度
	*/
 	virtual int Get(int id, void *pObject, int length);

	/* 将两个文件成员变量的缓冲区数据写入到硬盘中去 */
	virtual void FlushToDisk(void);

protected:	
	/**初始化存贮包的文件
	* @return true 初始化成功  false 初始化失败
	*/
	bool InitFile();
	
	/**获取流中全部包的总长度
	*@return 流中全部包的总长度
	*/
	fpos_t GetContentSize(void);

	/**重新打开流文件
	*@param	szIdFilename	存储地址的文件名
	*@param	szContentFilename	存储内容的文件名
	*@param	bReuse	是否重用此文件
	*@异常	CRuntimeError	如果文件名为空或文件读写错误，则抛出此异常
	*/
	void OpenFile(const char *pszFlowName, const char *pszPath, bool bReuse);

	/**关闭存贮包的文件
	*/
	void CloseFile();

	/**获取序号为id对象在流中的偏移量
	*@param	id	对象序号
	*@return 序号为id对象在流中的偏移量
	*/
	fpos_t GetOffset(int id);
	
private:
	FILE *m_fpIdFile;				/**< 存储偏移量的文件 */
	FILE *m_fpContentFile;			/**< 存储内容的文件 */
	vector<fpos_t> m_BlockOffset;		/**< 对象块的偏移量 */
	int m_nCount;					/**< 已经存在的包个数 */
	fpos_t m_nContentSize;			/**< 所有已有包的内容长度总和 */
	int m_nReadId;					/**< 最近一次读取的包的序号*/
	fpos_t m_nReadOffset;			/**< 最近一次读取的包在文件中的偏移量*/
	WORD m_nCommPhaseNo;			/**< 通讯阶段编号*/

	CRITICAL_VAR m_criticalVar;		/**< 临界区变量 */
	
};

#endif // !defined(AFX_FILEFLOW_H__32B28836_A01C_4923_BBF0_10B313ED400C__INCLUDED_)
