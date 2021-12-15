#femas remote shell ecall 飞马远程运行脚本
#Editor: 徐忠华
#date  : 2013-03-18
#####################################################
#define area  定义区域
CP=scp
SH="ssh -n"
SH_ARG=""
#PATH setup 路径设置
BASEPATH=$HOME
OBJPATH=$BASEPATH/run
CFGPATH=$BASEPATH/config
RunListFile=list.run
UserListFile=list.user
BACKUPPATH=$HOME/backup/

#####################################################
#impl area 功能函数区
#用户可以根据实际需要增加 可以通过ecall function来调用function中实现的功能
#ecall会为功能函数传入两个参数 $1:远程机器名  $2:远程服务名 远程机器名=远程服务名+编号 远程机器名定义在/etc/hosts中


clearlog()
{
	$SH $1@$2 $SH_ARG ./clearlog.sh
}

dumptinit()
{
	$SH $1@$2 $SH_ARG ./dump.sh
	$SH $1@$2 $SH_ARG "cd ./ustinit/dump;more t_Sync_User.csv" >> mstinitdumptmp.csv 
}

chktxt()
{
	$SH $1@$2 $SH_ARG more ./uskernel1/dump/check.txt
}

chksys()
{
	$SH $1@$2 $SH_ARG "grep SysNumber ./ustmdb/bin/ustmdb.ini"
	$SH $1@$2 $SH_ARG "grep SysNumber ./ustinit/bin/ustinit.ini"
}

chkconfig()
{
	$SH $1@$2 $SH_ARG "grep ms ./config/DeployConfig.xml | grep -v Topic | grep -v Database"
	$SH $1@$2 $SH_ARG "grep msudp ./config/DeployConfig.xml"
}

backlog()
{
	curdate=`date "+%Y%m%d"`
	$SH $1@$2 $SH_ARG ./backmdlog.sh $1_$2_$curdate
	$CP $1@$2:./$1_$2_$curdate.tar.gz $BACKUPPATH
	$SH $1@$2 $SH_ARG rm -r	$1_$2_$curdate.tar.gz
	ls -l $BACKUPPATH$1_$2_$curdate.tar.gz
}

chkbase()
{
	callfuns CheckAllPort
	callfuns checklink
}

dispdisk()
{
	HomeBdf=`ssh -n  $1@$2 df -k | grep -w '/home'|grep -v '/home/' | awk ' { print $4 } '`
	CffexBdf=`ssh -n  $1@$2 df -k | grep -w '/cffex'|grep -v '/cffex/' | awk ' { print $4 } '`
	printf "%-24s /home:%-10s /cffex:%-12s\n"  "$1@$2"      $HomeBdf        $CffexBdf
}

showtime()
{
	xxt=`$SH $1@$2 date`
	echo $xxt;
}

callhost()
{
	rm -r .$UserListFile
	case $# in
	1) ##如果没有参数，全部启动
		cat $UserListFile > .$UserListFile;;
	3) ##如果有3个参数，视为对user的过滤
		grep $2 $UserListFile | grep $3 > .$UserListFile;;
	esac

	##循环每个用户，启动进程
	cntexpr=`wc -l .$UserListFile | awk '{print $1}'`
	cnt=`expr $cntexpr`
	i=0
	while [ $i -lt $cnt ]
	do
		i=`expr $i + 1 `
		read user host
		##每个user里面启动所有的进程
		printf "%2d %s %s \n" $i $user $host
		$1 $user $host
	done < .$UserListFile
}

callall()
{
	rm -r .$UserListFile .$RunListFile
	case $# in
	1) ##如果没有参数，全部启动
		cat $UserListFile > .$UserListFile
		cat $RunListFile > .$RunListFile;;
	3) ##如果有3个参数，视为对user的过滤
		grep $2 $UserListFile | grep $3 > .$UserListFile
		cat $RunListFile > .$RunListFile;;
	4) ##如果4个参数，视为对user和进程的过滤
		grep $2 $UserListFile | grep $3 > .$UserListFile
		grep $4 $RunListFile > .$RunListFile;;
	5) ##如果5个参数，视为对user和进程的过滤
		grep $2 $UserListFile | grep $3 > .$UserListFile
		grep $4 $RunListFile | grep $5 > .$RunListFile;;		
	esac

	##循环每个用户，启动进程
	cntexpr=`wc -l .$UserListFile | awk '{print $1}'`
	cnt=`expr $cntexpr`	
	i=0
	while [ $i -lt $cnt ]
	do
		i=`expr $i + 1 `
		read user host
		##每个user里面启动所有的进程
		echo $i: $user @ $host
		cntexpr2=`wc -l .$RunListFile | awk '{print $1}'`
		cnt2=`expr $cntexpr2`		
		i2=0
		while [ $i2 -lt $cnt2 ]
		do
			i2=`expr $i2 + 1 `
			read srv no
			callImpl $i2 $1 $user $host $srv $no
		done < .$RunListFile
	done < .$UserListFile	
}

#ecall主调用入口
ecall()
{
	echo "#################################################"
	echo "##    begin to run batch                      ###"
	echo "#################################################"

	if [ $# -eq 0 ]
	then
		echo "Usage: $0 [clearlog|backclear|chkbase] [user host [module no]] [all]"
	else
		 if [ "$1" = "other" -o "$1" = "other2" ]
		 then
				callall $*
		 else
			if [ "$1" = "clearlog" -o "$1" = "backlog" -o "$1" = "dispdisk" -o "$1" = "showtime" -o "$1" = "chktxt" -o "$1" = "chksys" -o "$1" = "chkconfig" -o "$1" =  "dumptinit" ]
			then
				callhost $*
			else
				if [ "$1" = "chkbase"  ]
				then
					$1
				else
					echo "输入参数错误!!!"
				fi
			fi
		 fi
	fi
}
ecall $*
