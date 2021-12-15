/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file version.h
///@brief	管理一个程序的版本号
///@history 
///20020907	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef VERSION_H
#define VERSION_H

#include "platform.h"

extern const char *version;

///根据命令行参数，显示版本号
///@param	argc	参数个数
///@param	argv	参数值
void showVersion(int argc,char *argv[]);

#endif
