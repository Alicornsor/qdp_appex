/////////////////////////////////////////////////////////////////////////
///@system 底层支持
///@company 上海量投网络科技有限公司
///@file cryptUtility.cpp
///@brief	实现了若干常用的加密使用的工具
///@history 
///20080426	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "cryptUtility.h"

void MD5Hex(char *result, const char *string1, const char *string2, const char *string3, const char *string4)
{
	CMD5Handler md5Handler(string1);
	if (string2!=NULL)
	{
		md5Handler.update(string2);
	}
	if (string3!=NULL)
	{
		md5Handler.update(string3);
	}
	if (string4!=NULL)
	{
		md5Handler.update(string4);
	}
	CHexEncoder hexEncoder;
	hexEncoder.encode(result,33,md5Handler.digest(),16);
}
