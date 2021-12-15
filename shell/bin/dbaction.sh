#!/bin/bash
cmdmysql=mysql
SQLPATH=$HOME/sql
port=3306

action()
{
	${cmdmysql} -h$2 -P$6 -u$3 -p$4 -D$5< $SQLPATH/$1.sql
}

#select data
SelectDbCenter()
{

    ${cmdmysql} -N -h$2 -P$6 -u$3 -p$4 -D$5< $SQLPATH/selectcenter.sql > ./tmpcenter.ini
	
    cntexpr=`wc -l ./tmpcenter.ini | awk '{print $1}'`
    cntall=`expr $cntexpr`
    echo "$cntall"
    i=0
    while [ $i -lt $cntall ]
    do
	i=`expr $i + 1 `
	read s1 s2 s3 
	printf "%s %s %s\n" $s1 $s2 $s3
    done < ./tmpcenter.ini

    echo "a: 选择全部执行请输入 a "
    echo "请选择:"
    read  number

    if [ "$number" = "" ]
    then
	
	echo "没有选择，退出!"
	exit
    fi
    if [ "$number" = "a" ]
    then

        echo "全部执行！！"
	action clear $2 $3 $4 $5 $6
        exit
    fi

    i=0
    deleteflag=0
    while [ $i -lt $cntall ]
    do
        i=`expr $i + 1 `
        read a1 a2 a3 
	if [ "$a1" =  "$number" ]
	then
             deleteflag=1 
	fi
    done < ./tmpcenter.ini

    if [ $deleteflag = 1 ]
    then
	clearOneDB $number $2 $3 $4 $5 $6    
    else
	echo "没有该系统号！！！"
    fi

}


clearOneDB()
{
    SQLFILENAME="$SQLPATH/clearonecenter.sql"
    #读文件
    #${cmdmysql} -N -h$2 -P${port} -u$3 -p$4 -D$5 <<EOF
    cp $SQLFILENAME tmp.sql
    sed -i "s/systemid=/systemid=$1;/g" tmp.sql
    ${cmdmysql} -N -h$2 -P$6 -u$3 -p$4 -D$5 < tmp.sql 
    #while read line 
    #do
        #echo $line
    #    sql=$line$1
    #    echo $sql >> tmp.sql
    #done  < $SQLFILENAME 

}

inses()
{
	${cmdmysql} -N -h$1 -P${port} -u$2 -p$3 -D$4< $SQLPATH/inses.sql > ./symbol.csv
	echo  "LME_CAD_3M" >> ./symbol.csv
	echo  "" >> ./symbol.csv
	${cmdmysql} -N -h$1 -P${port} -u$2 -p$3 -D$4< $SQLPATH/inses.sql > ./symbol1.csv
	echo  "LME_CAD_3M" >> ./symbol1.csv
	echo  "" >> ./symbol1.csv		
	${cmdmysql} -N -h$1 -P${port} -u$2 -p$3 -D$4< $SQLPATH/inses2.sql > ./symbol2.csv
        echo  "" >> ./symbol2.csv
	echo "success"
}

insctp()
{
	${cmdmysql} -N -h$1 -P${port} -u$2 -p$3 -D$4< $SQLPATH/insctp.sql > ./CtpInstrumentfile.ini
	echo  "" >> ./CtpInstrumentfile.ini
	echo "success"
}

ecall()
{
		
	if [ $# -eq 0 ]
	then
		echo "Usage: $0 esins|ctpins|chkorder|chktrade|chksessioni|clear|chksystemstatus|clearone"
	else

		if [ "$1" = "inses" -o "$1" = "insctp" ]
		then
			echo $*
			$*
		elif [ "$1" = "clearone"  ] 
	        then
			#echo "SelectDbCenter"
			SelectDbCenter $*
		else
			echo action $*
			action $*
		fi
	fi
}
ecall $*
