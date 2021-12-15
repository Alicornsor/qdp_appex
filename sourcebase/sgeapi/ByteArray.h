#ifndef ByteArray_H
#define ByteArray_H



/**缓冲区为空格一个模板类
*/
template <int length>
class BYTEARRAY
{
public:
	/**构造函数
	*/
	BYTEARRAY(){
		memset(buf,0,length+1);
	}

	/**构造函数，将一个字符串放入缓冲区中
	*/
	BYTEARRAY(char *p)
	{
		strncpy(buf,p,length);
		buf[length]='\0';
	}
	
	friend bool operator < (const BYTEARRAY<length> &l,const BYTEARRAY<length> &r){
		return strcmp(l.buf,r.buf)<0;
	}

	friend bool operator == (const BYTEARRAY<length> &l,const BYTEARRAY<length> &r){
		return strcmp(l.buf,r.buf)==0;
	}

	friend int Compare(const BYTEARRAY<length> &l,const BYTEARRAY<length> &r)
	{
		int ret=strcmp(l.buf,r.buf);
		if(ret<0) return -1;
		if(ret>0) return 1;
		return 0;	
	}

	/**返回缓冲区的长度
	* @return 缓冲区的长度
	*/
	int Length(){
		return length+1;
	}
	
	char *getValue() {
		return buf;
	}
	
	operator char *(){
		return buf;
	}
public:
	char buf[length+1];	/**< 缓冲区 */
};
#endif
