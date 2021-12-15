/////////////////////////////////////////////////////////////////////////
///@system ��������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file version.h
///@brief	����һ������İ汾��
///@history 
///20020907	xuzh		�������ļ�
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
