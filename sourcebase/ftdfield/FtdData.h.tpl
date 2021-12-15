// FtdData.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FTDDATA_H)
#define _FTDDATA_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FieldDescribe.h"
#include "customDataType.h"

!!enter FTD!!
!!travel fields!!
///!!@comment!!
class C!!@head!!!!@name!!Field
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
};
const DWORD !!@head!!_FID_!!@name!!=!!@fid!!;

!!next!!


!!leave!!  

#endif
