!!function!!
#include <vector>
#include <stdarg.h>

using namespace std;

typedef struct
{
	char *definetypename;
	char *usage;
}	TTypeUsage;

vector<TTypeUsage> typeUsage;

void addUsage(char *definetypename,char *format,...)
{
	char usageBuffer[4096];
	va_list v;
	
	va_start(v,format);
	vsprintf(usageBuffer,format,v);
	va_end(v);
	TTypeUsage thisUsage;
	thisUsage.definetypename=strdup(definetypename);
	thisUsage.usage=strdup(usageBuffer);
	typeUsage.push_back(thisUsage);
}

char *getUsage(char *type)
{
	char originalType[100];
	strcpy(originalType,type+1);
	originalType[strlen(originalType)-4]='\0';
	vector<TTypeUsage>::iterator it;
	for (it=typeUsage.begin();it<typeUsage.end();it++)
	{
		if (!strcmp(it->definetypename,originalType))
		{
			return it->usage;
		}
	}
	exit(0);
	return "不明类型";
}
!!endfunction!!
!!travel UFDataTypes!!
	!!if !strcmp(@name,"Char")!!
		!!command addUsage(@typename,"字符")!!
	!!elseif !strcmp(@name,"String")||!strcmp(@name,"VString")!!
		!!command addUsage(@typename,"字符串(长度%s)",@length)!!
	!!elseif !strcmp(@name,"Int")||!strcmp(@name,"Word")!!
		!!command addUsage(@typename,"整数")!!
	!!elseif !strcmp(@name,"Float")||!strcmp(@name,"FixNumber")!!
		!!command addUsage(@typename,"浮点数")!!
	!!elseif !strcmp(@name,"RangeInt")!!
		!!command addUsage(@typename,"整数(%s-%s)",@from,@to)!!
	!!elseif !strcmp(@name,"EnumChar")!!
		!!let enumUsage=""!!
		!!travel self!!
			!!if @pumpid!=0!!
				!!let enumUsage=addstring(@enumUsage,",")!!
			!!endif!!
			!!let enumUsage=multiaddstring(4,@enumUsage,@value,":",@label)!!
		!!next!!
		!!command addUsage(@typename,"枚举值(%s)",@enumUsage)!!
	!!endif!!
!!next!!
!!enter XTP!!
!!travel packages!!
!!if !strcmp(@usage,"dbmt")!!
!!@name!! !!@comment!!
!!travel self!!
	!!let fieldName=@name!!
	!!enter XTP!!
	!!travel fields!!
	!!if !strcmp(@name,@fieldName)!!
	!!travel self!!
	!!@name!! !!@description!! !!@type!! !!show_string getUsage(@type)!!
	!!next!!
	!!endif!!
	!!next!!
	!!leave!!
!!next!!
!!endif!!
!!next!!
!!leave!!
