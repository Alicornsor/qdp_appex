//**********************************************************************
//文件名：CRuntimeError.h
//主要功能:定义了类CRuntimeError
//修改历史：
//**********************************************************************

#ifndef CRUNTIMEERROR_H
#define CRUNTIMEERROR_H

/**CRuntimeError是一个说明运行时错误异常的对象，供程序进行自我检查时抛出。
*/
class  CRuntimeError
{
public:
	/**构造函数，用于创建该异常对象
	* @param	msg	本异常的错误信息，本类不复制此字符串空间
	* @param	file	发生错误的文件名，本类不复制此字符串空间
	* @param	lineno	发生错误的文件行号
	*/
	CRuntimeError(char *pszMsg, char *pszFile, int nLineNo);
	
	/**析构函数，没有实质工作
	*/
	~CRuntimeError();
	
	/**获取错误信息
	* @return	错误信息
	*/
	char *GetMsg(void);
	
	/**获取发生错误的文件名
	* @return	文件名
	*/
	char *GetFile(void);
	
	/**获取发生错误的文件行号
	* @return 文件行号
	*/
	int GetLineNo(void);
private:
	
	char *m_pszMsg;	/**< 用于存储错误信息 */
	
	char *m_pszFile;     /**< 用于存储发生错误的文件名 */

	int m_nLineNo;     /**< 用于存储发生错误的行号 */
};

#endif
