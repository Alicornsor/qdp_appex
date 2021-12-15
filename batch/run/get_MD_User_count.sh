#!/bin/bash
# 检查 能够接收行情信息的用户的个数。 这个脚本需要放在 trade 用户的目录下面运行
# longqy 2013-12-09
LOGFILEPATH=~/backup/log/
LOGFILENAME=mdusercount_

today=`date "+%Y%m%d"`
echo "Market data users: " > $LOGFILEPATH$LOGFILENAME$today.txt
ssh -n mscffex@sqfm-knl1 "wc -l mstinit/dump/t_Sync_User.csv" >> $LOGFILEPATH$LOGFILENAME$today.txt

