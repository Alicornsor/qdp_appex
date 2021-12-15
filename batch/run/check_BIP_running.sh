#!/bin/bash
# ��� BIP �����Ƿ������С� ����ű���Ҫ���� BIP �����û��Ļ�����Ŀ¼����
# longqy 2013-12-06

# �������ֶ���
ARB=arb
COMPOSITOR=compositor
USERVER=u_server
SSERVER=s_server
FRONT=front

# ��� BIP �ľŸ������Ƿ�ɹ�����
# ���� 1 ��ʾ����ʧ�ܣ� ���� 0 ��ʾ�����ɹ�
is_BIP_runing()
{
	username=`whoami`
	tmpfile=".BIPProcesses"
	ps -fu $username > $tmpfile
	
	arb_id=`cat $tmpfile | grep $ARB | grep -v grep | awk '{print $2}'`
	if [ -z "$arb_id" ]
	then
#	uskernel û�������ɹ�
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
#	�Ÿ�����ȫ�������ɹ�
		rm -f $tmpfile
		return 0
}

# ��� BIP �ľŸ������Ƿ�ȫ��ֹͣ
# ���� 1 ��ʾ���г���û��ֹͣ�� ���� 0 ��ʾȫ��ֹͣ
is_BIP_stopped()
{
	username=`whoami`
	tmpfile=".BIPProcesses2"
	ps -fu $username > $tmpfile
	
	arb_id=`cat $tmpfile | grep $ARB | grep -v grep | awk '{print $2}'`
	if [ -n "$arb_id" ]
	then
#	arb ������
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
#	�Ÿ�����ȫ��ֹͣ�ɹ�
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
