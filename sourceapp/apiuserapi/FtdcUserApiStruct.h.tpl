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
/////////////////////////////////////////////////////////////////////////
///@system QuantDo Platform
///@company 上海量投网络科技有限公司
///@file !!@fileid!!FtdcUserApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
/////////////////////////////////////////////////////////////////////////

#if !defined(!!@fileid!!_FTDCSTRUCT_H)
#define !!@fileid!!_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "!!@fileid!!FtdcUserApiDataType.h"

!!enter FTD!!
!!travel fields!!
///!!@comment!!
struct C!!@functionid!!Ftdc!!@name!!Field
{
!!travel self!!
	///!!@description!!
	T!!@functionid!!Ftdc!!show_string(@type+1)!!	!!@name!!;
!!next!!
};

!!next!!

!!leave!!  

#endif
