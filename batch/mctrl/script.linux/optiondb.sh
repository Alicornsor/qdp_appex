#!/bin/bash

#�ַ������� ����
export LANG="zh_CN.UTF-8"
#��ȡ����·��

dbhost='192.168.1.241'  ##���ݿ��ַ
dbuser='root'   ##�û���
dbpw=''       ##����
dbname='quantdo'  ##���ݿ���
cmdmysql=./mysql ##mysql����


#�ж��Ƿ���ɾ��
if [ "$1" = "clear" ]
then
        echo "are you sure to delete database date (yes or no)  "
        read sure

        if [ "$sure" = "no" ]
        then
		#�˳�
                echo you give up delete !
                exit 0
        fi
fi

#���ݿ�����ʼ
${cmdmysql} -h ${dbhost} -u ${dbuser} -p${dbpw} ${dbname} < $1.sql

exit 0


