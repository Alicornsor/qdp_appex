/////////////////////////////////////////////////////////////////////////
///@system 交易引擎系统
///@company 上海量投网络科技有限公司
///@file version.h
///@brief	管理一个程序的版本号
///@history 
///20020907	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "version.h"
#include "versionValue.h"
#include "monitorIndex.h"

void showVersion(int argc,char *argv[])
{
	if ((argc==2)&&(!strcmp(argv[1],"-v")))
	{
		printf("%s version: %s\n",argv[0],QVERSION);
		exit(0);
	}
	new CStringMonitorIndex("Version",QVERSION,36000);
}
