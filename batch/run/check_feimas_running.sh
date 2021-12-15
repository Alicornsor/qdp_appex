#!/bin/bash
# 检查飞马系统交易程序是否在运行
# longqy 2013-12-06

# 程序名字定义
KERNEL=uskernel
QUERY=usquery
TINIT=ustinit
TMDB=ustmdb

# 行情模块的两个程序
MDCFFEX=mscffex
MDTINIT=mstinit

# 检查飞马的四个交易程序是否成功启动
# 返回 1 表示启动失败， 返回 0 表示启动成功
is_FEMAS_TR_runing()
{
	username=`whoami`
	kernel_id=`ps -fu $username | grep $KERNEL | grep -v grep | awk '{print $2}'`
	if [ -z "$kernel_id" ]
	then
#	uskernel 没有启动成功
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

#	四个程序全部启动成功
		return 0
}

# 检查飞马二个行情程序是否成功启动
# 返回 1 表示启动失败， 返回 0 表示启动成功
is_FEMAS_MD_runing()
{
	username=`whoami`
	mscffex_id=`ps -fu $username | grep $MDCFFEX | grep -v grep | awk '{print $2}'`
	if [ -z "$mscffex_id" ]
	then
#	mscffex 没有启动成功
		return 1
	fi

	mstinit_id=`ps -fu $username | grep $MDTINIT | grep -v grep | awk '{print $2}'`
	if [ -z "$mstinit_id" ]
	then
		return 1
	fi

#	二个程序全部启动成功
		return 0
}

# 检查飞马的四个交易程序是否是停止状态
# 返回 1 表示飞马有进程在运行， 返回 0 表示全部飞马交易程序停止
is_FEMAS_TR_stopped()
{
	username=`whoami`
	kernel_id=`ps -fu $username | grep $KERNEL | grep -v grep | awk '{print $2}'`
	if [ -n "$kernel_id" ]
	then
#	uskernel 进程在运行
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

#	四个程序全部停止
		return 0
}

# 检查飞马二个行情程序是否停止状态
# 返回 1 表示有程序在运行， 返回 0 表示全部飞马行情程序是停止状态
is_FEMAS_MD_stopped()
{
	username=`whoami`
	mscffex_id=`ps -fu $username | grep $MDCFFEX | grep -v grep | awk '{print $2}'`
	if [ -n "$mscffex_id" ]
	then
#	mscffex 没有启动成功
		return 1
	fi

	mstinit_id=`ps -fu $username | grep $MDTINIT | grep -v grep | awk '{print $2}'`
	if [ -n "$mstinit_id" ]
	then
		return 1
	fi

#	二个程序全部停止状态
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
