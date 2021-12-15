!!include PredictCommon.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system 极速风控前置 执行引擎系统
///@company 上海量投网络科技有限公司
///@file TradingQueryPredicts.h
///@brief	定义了查询用的各种基础的谓词
///@history 
///20121115		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "TradingQueryPredicts.h"

///-----
///	20121115：修改了所有对合约查询的条件，变为可以输入前段的方式
///-----

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
!!travel fields!!
!!if needQuery(@name)!!
!!let fieldName=@name!!
bool C!!@tableName!!!!@fieldName!!Predict::isValid(C!!@tableName!! *p!!@tableName!!)
{
	if ((m_p!!@fieldName!!Start!=NULL)&&(!m_p!!@fieldName!!Start->isNull()))
	{
		if (p!!@tableName!!->!!@fieldName!!<*m_p!!@fieldName!!Start)
		{
			return false;
		}
	}
	if ((m_p!!@fieldName!!End!=NULL)&&(!m_p!!@fieldName!!End->isNull()))
	{
		if (p!!@tableName!!->!!@fieldName!!>*m_p!!@fieldName!!End)
		{
			return false;
		}
	}
	return true;
}

!!elseif needQueryStartWith(@name)!!
!!let fieldName=@name!!
bool C!!@tableName!!!!@fieldName!!StartPredict::isValid(C!!@tableName!! *p!!@tableName!!)
{
	if ((m_p!!@fieldName!!Start!=NULL)&&(!m_p!!@fieldName!!Start->isNull()))
	{
		if (p!!@tableName!!->!!@fieldName!!<*m_p!!@fieldName!!Start)
		{
			return false;
		}
	}
	if ((m_p!!@fieldName!!End!=NULL)&&(!m_p!!@fieldName!!End->isNull()))
	{
		if (p!!@tableName!!->!!@fieldName!!>*m_p!!@fieldName!!End)
		{
			if (!strncmp(p!!@tableName!!->!!@fieldName!!,*m_p!!@fieldName!!End,strlen(*m_p!!@fieldName!!End)))
			{
				return true;
			}
			return false;
		}
	}
	return true;
}

!!endif!!
!!next!!
!!endif!!
!!next!!
!!leave!!
