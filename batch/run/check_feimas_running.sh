#!/bin/bash
# ������ϵͳ���׳����Ƿ�������
# longqy 2013-12-06

# �������ֶ���
KERNEL=uskernel
QUERY=usquery
TINIT=ustinit
TMDB=ustmdb

# ����ģ�����������
MDCFFEX=mscffex
MDTINIT=mstinit

# ��������ĸ����׳����Ƿ�ɹ�����
# ���� 1 ��ʾ����ʧ�ܣ� ���� 0 ��ʾ�����ɹ�
is_FEMAS_TR_runing()
{
	username=`whoami`
	kernel_id=`ps -fu $username | grep $KERNEL | grep -v grep | awk '{print $2}'`
	if [ -z "$kernel_id" ]
	then
#	uskernel û�������ɹ�
		return 1
	fi

	query_id=`ps -fu $username | grep $QUERY | grep -v grep | awk '{print $2}'`
	if [ -z "$query_id" ]
	then
		return 1
	fi

	tinit_id=`ps -fu $username | grep $TINIT | grep -v grep | awk '{print $2}'`
	if [ -z "$tinit_id" ]
	then
		return 1
	fi

	tmdb_id=`ps -fu $username | grep $TMDB | grep -v grep | awk '{print $2}'`
	if [ -z "$tinit_id" ]
	then
		return 1
	fi

#	�ĸ�����ȫ�������ɹ�
		return 0
}

# �����������������Ƿ�ɹ�����
# ���� 1 ��ʾ����ʧ�ܣ� ���� 0 ��ʾ�����ɹ�
is_FEMAS_MD_runing()
{
	username=`whoami`
	mscffex_id=`ps -fu $username | grep $MDCFFEX | grep -v grep | awk '{print $2}'`
	if [ -z "$mscffex_id" ]
	then
#	mscffex û�������ɹ�
		return 1
	fi

	mstinit_id=`ps -fu $username | grep $MDTINIT | grep -v grep | awk '{print $2}'`
	if [ -z "$mstinit_id" ]
	then
		return 1
	fi

#	��������ȫ�������ɹ�
		return 0
}

# ��������ĸ����׳����Ƿ���ֹͣ״̬
# ���� 1 ��ʾ�����н��������У� ���� 0 ��ʾȫ�������׳���ֹͣ
is_FEMAS_TR_stopped()
{
	username=`whoami`
	kernel_id=`ps -fu $username | grep $KERNEL | grep -v grep | awk '{print $2}'`
	if [ -n "$kernel_id" ]
	then
#	uskernel ����������
		return 1
	fi

	query_id=`ps -fu $username | grep $QUERY | grep -v grep | awk '{print $2}'`
	if [ -n "$query_id" ]
	then
		return 1
	fi

	tinit_id=`ps -fu $username | grep $TINIT | grep -v grep | awk '{print $2}'`
	if [ -n "$tinit_id" ]
	then
		return 1
	fi

	tmdb_id=`ps -fu $username | grep $TMDB | grep -v grep | awk '{print $2}'`
	if [ -n "$tinit_id" ]
	then
		return 1
	fi

#	�ĸ�����ȫ��ֹͣ
		return 0
}

# �����������������Ƿ�ֹͣ״̬
# ���� 1 ��ʾ�г��������У� ���� 0 ��ʾȫ���������������ֹͣ״̬
is_FEMAS_MD_stopped()
{
	username=`whoami`
	mscffex_id=`ps -fu $username | grep $MDCFFEX | grep -v grep | awk '{print $2}'`
	if [ -n "$mscffex_id" ]
	then
#	mscffex û�������ɹ�
		return 1
	fi

	mstinit_id=`ps -fu $username | grep $MDTINIT | grep -v grep | awk '{print $2}'`
	if [ -n "$mstinit_id" ]
	then
		return 1
	fi

#	��������ȫ��ֹͣ״̬
		return 0
}

is_FEMAS_TR_runing
if [ $? -eq 0 ]
then
	echo "FEMAS Trading start up success !"
else
	echo "FEMAS Trading start up failed !"
fi

is_FEMAS_MD_runing
if [ $? -eq 0 ]
then
	echo "FEMAS MarketDate start up success !"
else
	echo "FEMAS MarketDate start up failed !"
fi

is_FEMAS_TR_stopped
if [ $? -eq 0 ]
then
	echo "FEMAS Trading all stopped !"
else
	echo "FEMAS Trading stop failed !"
fi

is_FEMAS_MD_stopped
if [ $? -eq 0 ]
then
	echo "FEMAS MarketDate all stopped !"
else
	echo "FEMAS MarketDate stop failed !"
fi
