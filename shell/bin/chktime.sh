#chktime: ��鵱ǰʱ���Ƿ�������������
#	  ���ķ�ʽ��ֱ���ж���ǰʱ��
#	  �Ƿ�Ϊ07:40:00 ��08:10:00,���
#	  ����ʱ�䲻�ڴ˷�Χ֮�ڣ���Ҫ��
#	  ȷ�����롣

curtime_org=`date | awk '{print $5}'`
curtime=`echo $curtime_org|awk -F: '{print $1$2$3}'`
timeok=0
if [ $curtime -ge 070000 ]
then
	if [ $curtime -le 080000 ]
	then
		timeok=1
	fi
fi
echo $timeok $curtime_org

#������ʱ���Ƿ��ں����ʱ���
#start: 07:40:00 �� 08:10:00
#stop:  15:20 ��

#starttime1=070000
#starttime2=080000
#stoptime=152000

#��ȡ��ǰʱ��
#curtime_org=`date | awk '{print $4}'`
#curtime=`echo $curtime_org|awk -F: '{print $1$2$3}'`
#���ʱ����Ƿ����
#timeok=0

#if [ $curtime -ge $starttime1 ]
#then
#	if [ $curtime -le $starttime2 ]
#	then
#		timeok=1
#	else
#		printf "����ʱ��(��ǰ:$curtime_org)Ӧ�� 07:00:00 �� 08:00:00!\n"
#		timeok=0
#	fi
#else
#	printf "����ʱ��(��ǰ:$curtime_org)Ӧ�� 07:00:00 �� 08:00:00!\n"
#	timeok=0
#fi
