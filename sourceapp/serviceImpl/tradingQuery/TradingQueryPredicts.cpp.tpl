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

#include "TradingQueryPredicts.h"

///-----
///	20121115���޸������жԺ�Լ��ѯ����������Ϊ��������ǰ�εķ�ʽ
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
