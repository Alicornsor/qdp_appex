!!let exchangeid=""!!
!!let functionid=""!!
!!let macroid=""!!
!!let fileid=""!!
!!enter exchangeinfo!!
!!travel self!!
!!if @pumpid==0!!
!!let exchangeid=@name!!
!!elseif @pumpid==1!!
!!let functionid=@name!!
!!elseif @pumpid==2!!
!!let macroid=@name!!
!!elseif @pumpid==3!!
!!let fileid=@name!!
!!endif!!
!!next!!
!!leave!!
!!function!!
#include <set>
using namespace std;

struct ltstr
{
	bool operator()(const char* s1, const char* s2) const
	{
		return strcmp(s1, s2) < 0;
	}
};

typedef set<char *, ltstr> CTypeSet;
CTypeSet g_setUsedType;

bool InUse(char *name)
{
	char buf[100] = "C";
	strcpy(buf+1, name);
	strcat(buf,"Type");
	return (g_setUsedType.find(buf)!=g_setUsedType.end());
}

!!endfunction!!
!!enter FTD!!
!!enter fields!!
!!travel self!!
!!travel self!!
!!command g_setUsedType.insert(@type);!!
!!next!!
!!next!!
!!leave!!
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company QuantDo
///@file !!@fileid!!FtdcUserApiDataType.h
///@brief 定义了客户端接口使用的业务数据类型
///@history 
///
/////////////////////////////////////////////////////////////////////////

#ifndef !!@macroid!!_FTDCDATATYPE_H
#define !!@macroid!!_FTDCDATATYPE_H

enum !!@macroid!!_TE_RESUME_TYPE
{
	!!@macroid!!_TERT_RESTART = 0,
	!!@macroid!!_TERT_RESUME,
	!!@macroid!!_TERT_QUICK
};

/////////////////////////////////////////////////////////////////////////
///定义交易通道类型类别
/////////////////////////////////////////////////////////////////////////
//连接中金所
#define QDP_EI_CFFEX "CFFEX"
//连接上期所
#define QDP_EI_SHFE "SHFE"
//连接大商所
#define QDP_EI_DCE "DCE"
//连接郑商所
#define QDP_EI_ZCE "CZCE"
//连接上证所
#define QDP_EI_SSE "SSE"
//连接深交所
#define QDP_EI_SZSE "SZSE"
//连接黄金交易所
#define QDP_EI_SGE "SGE"
//连接芝加哥商品期货交易所
#define QDP_EI_CME "CME"
//连接伦敦金属交易所
#define QDP_EI_LME "LME"
//连接国泰君安的通道
#define QDP_EI_GTJA "GTJA"
//连接上海国际能源中心的通道
#define QDP_EI_INE "INE"

!!travel flows!!
const int !!@macroid!!_TSS_!!@name!! = !!@seqseries!!;		//!!@comment!!
!!next!!

!!enter types!!
!!travel self!!
!!if InUse(@typename)!!
/////////////////////////////////////////////////////////////////////////
///TFtdc!!@typename!!Type是一个!!@label!!类型
/////////////////////////////////////////////////////////////////////////
!!if !strcmp(@name,"RangeInt")!!
typedef int T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"RangeChar")!!
typedef char T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"String")!!
typedef char T!!@functionid!!Ftdc!!@typename!!Type[!!show_value(atoi(@length)+1)!!];

!!elseif !strcmp(@name,"VString")!!
typedef char T!!@functionid!!Ftdc!!@typename!!Type[!!show_value(atoi(@length)+1)!!];

!!elseif !strcmp(@name,"Array")!!
typedef char T!!@functionid!!Ftdc!!@typename!!Type[!!show_value(atoi(@length)+1)!!];

!!elseif !strcmp(@name,"Int")!!
typedef int T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"Long")!!
typedef int T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"Word")!!
typedef short T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"Char")!!
typedef char T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"EnumChar")!!
!!travel self!!
///!!@label!!
#define !!@macroid!!_FTDC_!!@prefix!!_!!@name!! '!!@value!!'
!!next!!

typedef char T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"Float")!!
typedef double T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"FixNumber")!!
typedef double T!!@functionid!!Ftdc!!@typename!!Type;

!!elseif !strcmp(@name,"Pointer")!!
typedef char *T!!@functionid!!Ftdc!!@typename!!Type;

!!else!!
	!!error printf("unknown type %s in %s\n",@name,@typename);!!
!!endif!!
!!endif!!
!!next!!
!!leave!!
#endif
!!leave!!