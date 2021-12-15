!!enter UFDataTypes!!
/////////////////////////////////////////////////////////////////////////
///@system 执行引擎系统
///@company 上海量投网络科技有限公司
///@file customDataType.h
///@brief定义了交易所内部数据的底层支持类
///@history 
///20050324	xuzh		创建该文件
/////////////////////////////////////////////////////////////////////////

#ifndef CUSTOMDATATYPE_H
#define CUSTOMDATATYPE_H

#include "UFDataType.h"

!!travel self!!
/////////////////////////////////////////////////////////////////////////
///C!!@name!!Type是一个!!@label!!类
/////////////////////////////////////////////////////////////////////////
!!if !strcmp(@name,"RangeInt")!!
typedef CUFRangeIntType<!!@from!!,!!@to!!> C!!@typename!!Type;
typedef const CUFRangeIntType<!!@from!!,!!@to!!> CReadOnly!!@typename!!Type;
	
!!elseif !strcmp(@name,"String")!!
typedef CUFStringType<!!@length!!> C!!@typename!!Type;
typedef const CUFStringType<!!@length!!> CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"VString")!!
typedef CUFStringType<!!@length!!> C!!@typename!!Type;
typedef const CUFStringType<!!@length!!> CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"Array")!!
typedef CUFStringType<!!@length!!> C!!@typename!!Type;
typedef const CUFStringType<!!@length!!> CReadOnly!!@typename!!Type;
	
!!elseif !strcmp(@name,"Int")!!
typedef CUFIntType C!!@typename!!Type;
typedef CReadOnlyUFIntType CReadOnly!!@typename!!Type;
	
!!elseif !strcmp(@name,"Long")!!
typedef CUFLongType C!!@typename!!Type;
typedef CReadOnlyUFLongType CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"Word")!!
typedef CUFWordType C!!@typename!!Type;
typedef CReadOnlyUFWordType CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"Char")!!
typedef CUFCharType C!!@typename!!Type;
typedef CReadOnlyUFCharType CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"EnumChar")!!
!!travel self!!
///!!@label!!
#define !!@prefix!!_!!@name!! '!!@value!!'
!!next!!

class C!!@typename!!Type : public CUFCharType					
{														
public:													
	C!!@typename!!Type(void)									
	{													
	}													
	C!!@typename!!Type(const C!!@typename!!Type &v)				
	{													
		setValue(v.getValue());							
	}													
	C!!@typename!!Type(const char v)							
	{													
		setValue(v);									
	}													
	C!!@typename!!Type(const CUFCharType &v)					
	{													
		setValue(v.getValue());							
	}													
	C!!@typename!!Type& operator=(const C!!@typename!!Type &c)	
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	C!!@typename!!Type& operator=(const CUFCharType &c)		
	{													
		setValue(c.getValue());							
		return *this;									
	}													
	const char operator =(const char c)					
	{													
		setValue(c);									
		return c;										
	}													
	const char * operator =(const char *v)				
	{													
		setValue(*v);									
		return v;										
	}													
	void clear(void)									
	{													
		setValue("!!travel self!!!!@value!!!!next!!"[0]);						
	}													
	void setValue(const char v)							
	{													
		value=v;										
	} 													
	bool isNull(void) const								
	{													
		return value==EnumNull;							
	}													
	bool isValid(void) const							
	{													
		if (value=='\0')								
			return false;								
		if (strchr("!!travel self!!!!@value!!!!next!!",value))					
			return true;								
		else											
			return false;								
	} 													
	static bool isValid(const char ch)					
	{													
		if (strchr("!!travel self!!!!@value!!!!next!!",ch))						
			return true;								
		else											
			return false;								
	}													
};														
typedef const C!!@typename!!Type CReadOnly!!@typename!!Type;		


!!elseif !strcmp(@name,"Float")!!
typedef CUFFloatType<!!@length!!,!!@precision!!> C!!@typename!!Type;
typedef const CUFFloatType<!!@length!!,!!@precision!!> CReadOnly!!@typename!!Type;
	
!!elseif !strcmp(@name,"FixNumber")!!
//DefineFixNumberType(!!@length!!,!!@precision!!,!!@typename!!Type)
typedef CUFFloatType<!!@length!!,!!@precision!!> C!!@typename!!Type;
typedef const CUFFloatType<!!@length!!,!!@precision!!> CReadOnly!!@typename!!Type;

!!elseif !strcmp(@name,"Pointer")!!
typedef CUFPointerType C!!@typename!!Type;
typedef CReadOnlyUFPointerType CReadOnly!!@typename!!Type;

!!else!!
	!!error printf("unknown type %s in %s\n",@name,@typename);!!
!!endif!!
!!next!!
#endif
!!leave!!