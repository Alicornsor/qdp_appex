#!/bin/bash
# ��� �ܹ�����������Ϣ���û��ĸ����� ����ű���Ҫ���� trade �û���Ŀ¼��������
# longqy 2013-12-09
LOGFILEPATH=~/backup/log/
LOGFILENAME=mdusercount_

today=`date "+%Y%m%d"`
echo "Market data users: " > $LOGFILEPATH$LOGFILENAME$today.txt
ssh -n mscffex@sqfm-knl1 "wc -l mstinit/dump/t_Sync_User.csv" >> $LOGFILEPATH$LOGFILENAME$today.txt

