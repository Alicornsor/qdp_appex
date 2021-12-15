#chktime: 检查当前时间是否允许启动程序
#	  检查的方式是直接判定当前时间
#	  是否为07:40:00 到08:10:00,如果
#	  启动时间不在此范围之内，则要求
#	  确认输入。

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

#检查操作时间是否在合理的时间段
#start: 07:40:00 至 08:10:00
#stop:  15:20 后

#starttime1=070000
#starttime2=080000
#stoptime=152000

#获取当前时间
#curtime_org=`date | awk '{print $4}'`
#curtime=`echo $curtime_org|awk -F: '{print $1$2$3}'`
#检查时间段是否合理
#timeok=0

#if [ $curtime -ge $starttime1 ]
#then
#	if [ $curtime -le $starttime2 ]
#	then
#		timeok=1
#	else
#		printf "启动时间(当前:$curtime_org)应当 07:00:00 至 08:00:00!\n"
#		timeok=0
#	fi
#else
#	printf "启动时间(当前:$curtime_org)应当 07:00:00 至 08:00:00!\n"
#	timeok=0
#fi
