#!/bin/bash
# 检查 BIP 程序是否在运行。 这个脚本需要放在 BIP 运行用户的机器与目录下面
# longqy 2013-12-06

# 程序名字定义
ARB=arb
COMPOSITOR=compositor
USERVER=u_server
SSERVER=s_server
FRONT=front

# 检查 BIP 的九个程序是否成功启动
# 返回 1 表示启动失败， 返回 0 表示启动成功
is_BIP_runing()
{
	username=`whoami`
	tmpfile=".BIPProcesses"
	ps -fu $username > $tmpfile
	
	arb_id=`cat $tmpfile | grep $ARB | grep -v grep | awk '{print $2}'`
	if [ -z "$arb_id" ]
	then
#	uskernel 没有启动成功
		rm -f $tmpfile
		return 1
	fi

	compositor_id=`cat $tmpfile | grep $COMPOSITOR | grep -v grep | awk '{print $2}'`
	if [ -z "$compositor_id" ]
	then
		rm -f $tmpfile
		return 1
	fi

	u_serverid=`cat $tmpfile | grep $USERVER | grep -v grep | awk '{print $2}'`
	if [ -z "$u_serverid" ]
	then
		rm -f $tmpfile
		return 1
	fi

	s_serverid=`cat $tmpfile | grep $SSERVER | grep -v grep | awk '{print $2}'`
	if [ -z "$s_serverid" ]
	then
		rm -f $tmpfile
		return 1
	fi

	front_id=`cat $tmpfile | grep $FRONT | grep -v grep | awk '{print $2}'`
	if [ -z "$front_id" ]
	then
		rm -f $tmpfile
		return 1
	fi
#	九个程序全部启动成功
		rm -f $tmpfile
		return 0
}

# 检查 BIP 的九个程序是否全部停止
# 返回 1 表示还有程序没有停止， 返回 0 表示全部停止
is_BIP_stopped()
{
	username=`whoami`
	tmpfile=".BIPProcesses2"
	ps -fu $username > $tmpfile
	
	arb_id=`cat $tmpfile | grep $ARB | grep -v grep | awk '{print $2}'`
	if [ -n "$arb_id" ]
	then
#	arb 在运行
		rm -f $tmpfile
		return 1
	fi

	compositor_id=`cat $tmpfile | grep $COMPOSITOR | grep -v grep | awk '{print $2}'`
	if [ -n "$compositor_id" ]
	then
		rm -f $tmpfile
		return 1
	fi

	u_serverid=`cat $tmpfile | grep $USERVER | grep -v grep | awk '{print $2}'`
	if [ -n "$u_serverid" ]
	then
		rm -f $tmpfile
		return 1
	fi

	s_serverid=`cat $tmpfile | grep $SSERVER | grep -v grep | awk '{print $2}'`
	if [ -n "$s_serverid" ]
	then
		rm -f $tmpfile
		return 1
	fi

	front_id=`cat $tmpfile | grep $FRONT | grep -v grep | awk '{print $2}'`
	if [ -n "$front_id" ]
	then
		rm -f $tmpfile
		return 1
	fi
#	九个程序全部停止成功
		rm -f $tmpfile
		return 0
}

is_BIP_runing
if [ $? -eq 0 ]
then
	echo "BIP start up success !"
else
	echo "BIP start up failed !"
fi


is_BIP_stopped
if [ $? -eq 0 ]
then
	echo "BIP all stopped !"
else
	echo "BIP stop failed !"
fi
