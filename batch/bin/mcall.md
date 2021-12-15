#femas remote shell ecall ����Զ�����нű�
#Editor: ���һ�
#date  : 2013-03-18
#####################################################
#define area  ��������
CP=scp
SH="ssh -n"
SH_ARG=""
#PATH setup ·������
BASEPATH=$HOME
OBJPATH=$BASEPATH/run
CFGPATH=$BASEPATH/config
RunListFile=list.run
UserListFile=list.user
BACKUPPATH=$HOME/backup/

#####################################################
#impl area ���ܺ�����
#�û����Ը���ʵ����Ҫ���� ����ͨ��ecall function������function��ʵ�ֵĹ���
#ecall��Ϊ���ܺ��������������� $1:Զ�̻�����  $2:Զ�̷����� Զ�̻�����=Զ�̷�����+��� Զ�̻�����������/etc/hosts��


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
	1) ##���û�в�����ȫ������
		cat $UserListFile > .$UserListFile;;
	3) ##�����3����������Ϊ��user�Ĺ���
		grep $2 $UserListFile | grep $3 > .$UserListFile;;
	esac

	##ѭ��ÿ���û�����������
	cntexpr=`wc -l .$UserListFile | awk '{print $1}'`
	cnt=`expr $cntexpr`
	i=0
	while [ $i -lt $cnt ]
	do
		i=`expr $i + 1 `
		read user host
		##ÿ��user�����������еĽ���
		printf "%2d %s %s \n" $i $user $host
		$1 $user $host
	done < .$UserListFile
}

callall()
{
	rm -r .$UserListFile .$RunListFile
	case $# in
	1) ##���û�в�����ȫ������
		cat $UserListFile > .$UserListFile
		cat $RunListFile > .$RunListFile;;
	3) ##�����3����������Ϊ��user�Ĺ���
		grep $2 $UserListFile | grep $3 > .$UserListFile
		cat $RunListFile > .$RunListFile;;
	4) ##���4����������Ϊ��user�ͽ��̵Ĺ���
		grep $2 $UserListFile | grep $3 > .$UserListFile
		grep $4 $RunListFile > .$RunListFile;;
	5) ##���5����������Ϊ��user�ͽ��̵Ĺ���
		grep $2 $UserListFile | grep $3 > .$UserListFile
		grep $4 $RunListFile | grep $5 > .$RunListFile;;		
	esac

	##ѭ��ÿ���û�����������
	cntexpr=`wc -l .$UserListFile | awk '{print $1}'`
	cnt=`expr $cntexpr`	
	i=0
	while [ $i -lt $cnt ]
	do
		i=`expr $i + 1 `
		read user host
		##ÿ��user�����������еĽ���
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

#ecall���������
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
					echo "�����������!!!"
				fi
			fi
		 fi
	fi
}
ecall $*
