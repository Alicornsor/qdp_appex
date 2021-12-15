#ifndef __PERSISTENTSTATE_H_
#define __PERSISTENTSTATE_H_

/**这个类实现了将一个对象序列化到一个文件上，是一个模板类 
*/
template<class  TState>
class CPersistentState
{
public:
	
	/**构造函数
	* @param state 对象的应用
	*/
	CPersistentState(TState &state)
	{
		m_fp = NULL;
		m_State = state;
	}
	
	/**构造函数，初始化存贮对象
	*/
	CPersistentState()
	{
		m_fp = NULL;
		memset(&m_State, 0, sizeof(TState));
	}

	/**析构函数，关闭文件
	*/
	~CPersistentState()
	{
		Close();
	}

	/**打开这个文件，或读取文件的内容
	* @param filename 文件名
	* @return true 成功
	* @return true 失败
	*/
	bool Open(char *pszFilename)
	{
		m_fp = mfopen(pszFilename,"r+b");
		if(m_fp == NULL)
		{
			m_fp = mfopen(pszFilename, "wb");
			if(m_fp == NULL)
			{
				return false;
			}
			return Write();
		}
		else
		{
			return Read();
		}
		return true;
	}

	/**关闭文件
	*/
	void Close()
	{
		if(m_fp != NULL)
		{
			fclose(m_fp);
			m_fp = NULL;
		}
	}

	/**更新在文件中的对象
	* @param pState 这个对象的指针
	* @return true 成功
	* @return true 失败
	*/
	bool UpdateState(TState *pState)
	{
		m_State = *pState;
		return Write();
	}

	/**获得这个对象
	* @return 返回这个对象的指针
	*/
	inline  TState *GetState()
	{
		return &m_State;
	}

protected:

	/**从文件中读取对象
	* @return true 成功
	* @return true 失败
	*/	
	bool Read()
	{
		if(m_fp==NULL)
		{
			return false;
		}
		
		if(fread(&m_State, sizeof(TState), 1, m_fp) != 1)
		{
			return false;
		}
		return true;
	}

	/**把对象写入文件中
	* @return true 成功
	* @return true 失败
	*/
	bool Write()
	{
		if(m_fp==NULL)
		{
			return false;
		}
		
		fseek(m_fp, 0, SEEK_SET);
		if(fwrite(&m_State, sizeof(TState), 1, m_fp) != 1)
		{
			return false;
		}
		fflush(m_fp);
		
		return true;
	}
	
protected:
	FILE * m_fp;	/**< 这个文件的指针 */
	TState m_State;	/**< 要写入文件的对象 */
};
#endif
