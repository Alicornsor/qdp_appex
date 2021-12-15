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

#ifndef TRADINGQUERYPREDICTS_H
#define TRADINGQUERYPREDICTS_H

#include "databaseIteratorRepository.h"

!!travel tables!!
!!if !strcmp(@hasTable,"yes")!!
!!let tableName=@name!!
!!travel fields!!
!!if needQuery(@name)!!
!!let fieldName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!!!@fieldName!!Predict是判断一个!!@usage!!是否满足!!@comment!!条件的谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!!!@fieldName!!Predict: public C!!@tableName!!Predict
{
private:
	!!@type!! *m_p!!@fieldName!!Start;
	!!@type!! *m_p!!@fieldName!!End;
public:
	///构造方法
	///@param	p!!@fieldName!!Start	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	p!!@fieldName!!End	必须小于等于的值。如果为NULL，则忽略此条件
	C!!@tableName!!!!@fieldName!!Predict(!!@type!! *p!!@fieldName!!Start, !!@type!! *p!!@fieldName!!End)
	{
		m_p!!@fieldName!!Start=p!!@fieldName!!Start;
		m_p!!@fieldName!!End=p!!@fieldName!!End;
	}

	virtual ~C!!@tableName!!!!@fieldName!!Predict()
	{
	}	
	
	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!);
};

!!elseif needQueryStartWith(@name)!!
!!let fieldName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!!!@fieldName!!StartPredict是判断一个!!@usage!!是否满足开始的!!@comment!!条件的谓词
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!!!@fieldName!!StartPredict: public C!!@tableName!!Predict
{
private:
	!!@type!! *m_p!!@fieldName!!Start;
	!!@type!! *m_p!!@fieldName!!End;
public:
	///构造方法
	///@param	p!!@fieldName!!Start	必须大于等于的值。如果为NULL，则忽略此条件
	///@param	p!!@fieldName!!End	必须小于等于的值，或者起始值等于的值。如果为NULL，则忽略此条件
	C!!@tableName!!!!@fieldName!!StartPredict(!!@type!! *p!!@fieldName!!Start, !!@type!! *p!!@fieldName!!End)
	{
		m_p!!@fieldName!!Start=p!!@fieldName!!Start;
		m_p!!@fieldName!!End=p!!@fieldName!!End;
	}

	virtual ~C!!@tableName!!!!@fieldName!!StartPredict()
	{
	}	
	
	///判断是否合法
	///@param	p!!@tableName!!	要被判断的!!@usage!!
	///@return	true表示合法，false表示不合法
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!);
};

!!endif!!
!!next!!
!!endif!!
!!next!!
#endif
!!leave!!
