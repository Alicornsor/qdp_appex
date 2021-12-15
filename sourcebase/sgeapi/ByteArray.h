#ifndef ByteArray_H
#define ByteArray_H



/**������Ϊ�ո�һ��ģ����
*/
template <int length>
class BYTEARRAY
{
public:
	/**���캯��
	*/
	BYTEARRAY(){
		memset(buf,0,length+1);
	}

	/**���캯������һ���ַ������뻺������
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

	/**���ػ������ĳ���
	* @return �������ĳ���
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
	char buf[length+1];	/**< ������ */
};
#endif
