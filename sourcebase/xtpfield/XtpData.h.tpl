// XtpData.h: 
//
///20090118	xuzh		增加了查询的日志（NT-0065）
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_)
#define AFX_XTPDATA_H__EA501ADE_818C_4F9A_8738_AC9CCAF0B941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "customDataType.h"

!!enter XTP!!
!!travel fields!!
///!!@comment!!
class C!!@name!!Field
{
public:
!!travel self!!
	///!!@description!!
	!!@type!!	!!@name!!;
!!next!!
	TYPE_DESCRIPTOR((
	!!travel self!!
		!!if @pumpid!=0!!
		,
		!!endif!!
		TYPE_DESC(!!@name!!)
	!!next!!
	));
	
	///将本field输出到buffer中，buffer长度为len，如果长度不够，将采用尽量输出的原则
	///@param	buffer	要放置结果的缓冲区
	///@param	len	缓冲区的长度
	///@return	true表示全部放成功，false表示没有全部放成功。
	bool dumpLine(char *buffer, int len);
};
const DWORD FID_!!@name!!=!!@fid!!;

!!next!!


!!leave!!  

#endif
