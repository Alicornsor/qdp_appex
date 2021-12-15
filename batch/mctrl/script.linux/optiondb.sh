#!/bin/bash

#字符集变量 设置
export LANG="zh_CN.UTF-8"
#获取绝对路径

dbhost='192.168.1.241'  ##数据库地址
dbuser='root'   ##用户名
dbpw=''       ##密码
dbname='quantdo'  ##数据库名
cmdmysql=./mysql ##mysql命令


#判断是否是删除
if [ "$1" = "clear" ]
then
        echo "are you sure to delete database date (yes or no)  "
        read sure

        if [ "$sure" = "no" ]
        then
		#退出
                echo you give up delete !
                exit 0
        fi
fi

#数据库请求开始
${cmdmysql} -h ${dbhost} -u ${dbuser} -p${dbpw} ${dbname} < $1.sql

exit 0


