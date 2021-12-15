#'#' 表示注释 菜单系统忽略此行
#功能：显示文本 格式：@TEXT|起始行|起始列|文本内容|显示属性 0 正常 1 反向
#功能：画框 格式：@BOX|起始行|起始列|末尾行|末尾列
#功能：画线 格式：@LINE|行|列|长度|横竖标志 - 表示横线 | 表示竖线
#功能：定义菜单单元 格式:菜单项|菜单项标识|父菜单标识|行(屏幕位置)|列(屏幕位置) 

##㈠㈡㈢㈣㈤㈥㈦
##⑴⑵⑶⑷⑸⑹⑺⑻⑼⑽⑾⑿⒀⒁⒂⒃⒄⒅⒆⒇

#目录配置
#日志目录配置
@CFG|../log

#主框
@BBOX|0|1|43|125
#菜单框
@MBOX|
#一般方框
#@BOX|2|3|5|125

@TITLE|   QDP System Control V1.0    |1

㈠环境检查  |1|0|0|0
㈡启  动    |2|0|0|0
㈢启动后检查|3|0|0|0
㈣巡  检    |4|0|0|0
㈤盘后处理  |5|0|0|0
㈥应急处理  |6|0|0|0

⑴检查磁盘信息  |11|1|0|0
⑵检查主机时间  |12|1|0|0
⑶检查配置文件  |13|1|0|0
⑷检查端口情况  |14|1|0|0
⑸检查进程情况  |15|1|0|0
⑹检查系统状态  |16|1|0|0

⑴启动交易进程|21|2|0|0
⑵检查交易进程|22|2|0|0
⑶启动行情进程|23|2|0|0
⑷检查行情进程|24|2|0|0

⑴检查交易进程|31|3|0|0
⑵错误记录检查|32|3|0|0
⑶检查系统状态|33|3|0|0
⑷检查行情进程|34|3|0|0

⑴健康检查    |41|4|0|0
⑵连接数检查  |42|4|0|0
⑶登录次数检查|43|4|0|0
⑷报单数目检查|44|4|0|0
⑸成交数目检查|45|4|0|0
⑹检查系统状态|46|4|0|0
⑺检查资金状态|47|4|0|0
⑷检查交易所端口|48|4|0|0

⑴检查进程情况|50|5|0|0
⑵停止所有进程|51|5|0|0
⑶备份所有流水|52|5|0|0
⑷清理所有流水|53|5|0|0
⑺应急上场文件|56|5|0|0
⑼延时统计|58|5|0|0
⑸停止行情进程|54|5|0|0
⑹清理行情流|55|5|0|0

⑴停止单一QDP|60|6|0|0
⑵清理单一数据库|61|6|0|0
⑶启动单一QDP|62|6|0|0
⑷重启单一QDP|63|6|0|0
⑸重启所有QDP|64|6|0|0

#菜单功能配置
#格式:@CMD|菜单功能号|激活登陆标志(0:不激活 1:防失误确认 2:激活双用户)|时间段编号|外部程序或Shell
#启动前
@CMD|11|0|0|cd ../../bin; ./mcall dispdisk
@CMD|12|0|0|cd ../../bin; ./mcall showtime
@CMD|13|0|0|cd ../script; ./chkconfig.sh
@CMD|14|0|0|cd ../../bin; ./callfuns CheckAllPort
@CMD|15|0|0|cd ../../bin; ./showall
@CMD|16|0|0|cd ../script; ./checkdb.sh chksystemstatus

#启动
@CMD|21|2|0|cd ../../bin; ./startall
@CMD|22|0|0|cd ../../bin; ./showall
@CMD|23|2|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./startall"
@CMD|24|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./showall"

#启动后 
@CMD|31|0|0|cd ../../bin; ./showall;
@CMD|32|0|0|cd ../../bin; ./mcall chktxt
@CMD|33|0|0|cd ../script; ./checkdb.sh chksystemstatus
@CMD|34|0|0|cd ../../binmd; ./showall

#巡检
@CMD|41|0|0|cd ../../bin; ./showall;ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./showall"
@CMD|42|0|0|cd ../../bin; ./callfuns checklink;
@CMD|43|0|0|cd ../script; ./checkdb.sh chksession
@CMD|44|0|0|cd ../script; ./checkdb.sh chkorder
@CMD|45|0|0|cd ../script; ./checkdb.sh chktrade
@CMD|46|0|0|cd ../script; ./checkdb.sh chksystemstatus
@CMD|47|0|0|cd ../script; ./checkdb.sh chkaccount
@CMD|48|0|0|cd ../../bin; ./callfuns CheckUpPort

#盘后处理
@CMD|50|0|0|cd ../../bin; ./showall
@CMD|51|2|0|cd ../../bin; ./stopall
@CMD|52|2|0|cd ../../bin; ./mcall backlog
@CMD|53|2|0|cd ../../bin; ./mcall clearlog
@CMD|56|2|0|cd ../../bin; ./mcall dumptinit
@CMD|58|1|0|cd ../../bin; ./mcall looptime
@CMD|54|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;cd bin; ./stopall"
@CMD|55|0|0|ssh -n qmarket@172.16.102.66  "export PATH=$PATH:~/bin;./clearlog.sh"

@CMD|60|2|0|cd ../../bin; ./stopone
@CMD|61|2|0|cd ../script; ./checkdb.sh clear
@CMD|62|2|0|cd ../../bin; ./startone
@CMD|63|2|0|cd ../../bin; ./restartone
@CMD|64|2|0|cd ../../bin; ./restartall


#@cmd|1:in 0:out|time id|begin time|end time 
@TIME_CTRL|1|1|07:00:00|09:10:00
@TIME_CTRL|0|2|15:15:00|19:40:00
@TIME_CTRL|0|3|09:05:00|15:18:00
