!!include PredictCommon.tpl!!
!!enter system!!
/////////////////////////////////////////////////////////////////////////
///@system ���ٷ��ǰ�� ִ������ϵͳ
///@company �Ϻ���Ͷ����Ƽ����޹�˾
///@file TradingQueryPredicts.h
///@brief	�����˲�ѯ�õĸ��ֻ�����ν��
///@history 
///20121115		�������ļ�
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
///C!!@tableName!!!!@fieldName!!Predict���ж�һ��!!@usage!!�Ƿ�����!!@comment!!������ν��
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!!!@fieldName!!Predict: public C!!@tableName!!Predict
{
private:
	!!@type!! *m_p!!@fieldName!!Start;
	!!@type!! *m_p!!@fieldName!!End;
public:
	///���췽��
	///@param	p!!@fieldName!!Start	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	p!!@fieldName!!End	����С�ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	C!!@tableName!!!!@fieldName!!Predict(!!@type!! *p!!@fieldName!!Start, !!@type!! *p!!@fieldName!!End)
	{
		m_p!!@fieldName!!Start=p!!@fieldName!!Start;
		m_p!!@fieldName!!End=p!!@fieldName!!End;
	}

	virtual ~C!!@tableName!!!!@fieldName!!Predict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	p!!@tableName!!	Ҫ���жϵ�!!@usage!!
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!);
};

!!elseif needQueryStartWith(@name)!!
!!let fieldName=@name!!
/////////////////////////////////////////////////////////////////////////
///C!!@tableName!!!!@fieldName!!StartPredict���ж�һ��!!@usage!!�Ƿ����㿪ʼ��!!@comment!!������ν��
///@author	!!@author!!
///@version	!!@version!!
/////////////////////////////////////////////////////////////////////////
class C!!@tableName!!!!@fieldName!!StartPredict: public C!!@tableName!!Predict
{
private:
	!!@type!! *m_p!!@fieldName!!Start;
	!!@type!! *m_p!!@fieldName!!End;
public:
	///���췽��
	///@param	p!!@fieldName!!Start	������ڵ��ڵ�ֵ�����ΪNULL������Դ�����
	///@param	p!!@fieldName!!End	����С�ڵ��ڵ�ֵ��������ʼֵ���ڵ�ֵ�����ΪNULL������Դ�����
	C!!@tableName!!!!@fieldName!!StartPredict(!!@type!! *p!!@fieldName!!Start, !!@type!! *p!!@fieldName!!End)
	{
		m_p!!@fieldName!!Start=p!!@fieldName!!Start;
		m_p!!@fieldName!!End=p!!@fieldName!!End;
	}

	virtual ~C!!@tableName!!!!@fieldName!!StartPredict()
	{
	}	
	
	///�ж��Ƿ�Ϸ�
	///@param	p!!@tableName!!	Ҫ���жϵ�!!@usage!!
	///@return	true��ʾ�Ϸ���false��ʾ���Ϸ�
	virtual bool isValid(C!!@tableName!! *p!!@tableName!!);
};

!!endif!!
!!next!!
!!endif!!
!!next!!
#endif
!!leave!!
