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

@TITLE|   量投网络 QDAM 系统运维界面 V1.0    |1

㈠环境检查  |1|0|0|0
㈡程序启动  |2|0|0|0
㈢盘中巡检  |3|0|0|0
㈣盘后处理  |4|0|0|0
㈤应急处理  |5|0|0|0

⑴检查磁盘信息|11|1|0|0
⑵检查主机时间|12|1|0|0
⑶检查端口情况|13|1|0|0
⑷检查进程情况|14|1|0|0
⑸检查系统状态|15|1|0|0
⑹检查上场数据|16|1|0|0
⑺检查盘前数据|17|1|0|0
⑻检查盘中数据|18|1|0|0

⑴启动之前准备|55|2|0|0
⑵启动系统程序|21|2|0|0
⑶检查进程情况|22|2|0|0
⑷错误记录检查|23|2|0|0
⑸连接数目检查|42|2|0|0
⑹检查上层连接|48|2|0|0
⑺生成ctp行情|24|2|0|0
⑻生成es行情|25|2|0|0
⑼查看CTP行情合约|26|2|0|0
⑽查看ES行情合约|27|2|0|0
⑾拷贝CTP行情合约|28|2|0|0
⑿拷贝ES行情合约|29|2|0|0
                  
⑴进程健康检查|41|3|0|0
⑵连接数目检查|42|3|0|0
⑶登录次数检查|43|3|0|0
⑷报单数目检查|44|3|0|0
⑸成交数目检查|45|3|0|0
⑹检查系统状态|46|3|0|0
⑺检查资金状态|47|3|0|0
⑻检查上层连接|48|3|0|0

⑴检查进程情况|41|4|0|0
⑵停止系统进程|51|4|0|0
⑶备份系统流水|52|4|0|0
⑷清理系统流水|53|4|0|0
⑸备全部数据库|54|4|0|0
⑹清下场数据库|55|4|0|0

⑴停止系统进程|51|5|0|0
⑵备份系统流水|52|5|0|0
⑶清理系统流水|53|5|0|0
⑷备全部数据库|54|5|0|0
⑸清下场数据库|55|5|0|0
⑹重启系统进程|61|5|0|0
⑺启动系统进程|21|5|0|0
⑻用户修改密码|1002|5|0|0


#菜单功能配置
#格式:@CMD|菜单功能号|激活登陆标志(0:不激活 1:防失误确认 2:激活双用户)|时间段编号|外部程序或Shell
#环境检查
@CMD|11|0|0|cd ../../bin; ./mcall dispdisk;
@CMD|12|0|0|cd ../../bin; ./mcall showtime;
@CMD|13|0|0|cd ../../bin; ./portfuns port
@CMD|14|0|0|cd ../../bin; ./mcall show
@CMD|15|0|0|cd ../../bin; ./dball chksystemstatus
@CMD|16|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase1 ../list/list.user
@CMD|17|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase2 ../list/list.user
@CMD|18|0|0|cd ../../bin; ./calluser mc_batch qdamcheckphase3 ../list/list.user

#程序启动
@CMD|21|1|0|cd ../../bin; ./calluser mc_batch restart
@CMD|22|0|0|cd ../../bin; ./calluser mc_batch show
@CMD|23|0|0|cd ../../bin; ./mcall show
@CMD|24|0|0|cd ../../bin; ./calluser dbaction.sh insctp ../list/list.db
@CMD|25|0|0|cd ../../bin; ./calluser dbaction.sh inses ../list/list.db
@CMD|26|0|0|cd ../../bin; ./showinsctp.sh
@CMD|27|0|0|cd ../../bin; ./showinses.sh
@CMD|28|0|0|cd ../../bin; ./calluser mc_batch copyins
@CMD|29|0|0|cd ../../bin; ./calluser mc_batch copyes

#盘中巡检
@CMD|41|0|0|cd ../../bin; ./mcall show
@CMD|42|0|0|cd ../../bin; ./portfuns link
@CMD|43|0|0|cd ../../bin; ./dball chksession
@CMD|44|0|0|cd ../../bin; ./dball chkorder
@CMD|45|0|0|cd ../../bin; ./dball chktrade
@CMD|46|0|0|cd ../../bin; ./dball chksystemstatus
@CMD|47|0|0|cd ../../bin; ./dball chkaccount
@CMD|48|0|0|cd ../../bin; ./portfuns up

#盘后处理
@CMD|51|2|0|cd ../../bin; ./calluser mc_batch stop
@CMD|52|1|0|cd ../../bin; ./calluser mc_batch backlog
@CMD|53|2|0|cd ../../bin; ./calluser mc_batch clearlog
@CMD|54|1|0|cd ../../bin; ./calluser mc_batch backupdb ../list/list.db.user
@CMD|55|1|0|cd ../../bin; ./callone dbaction.sh clearone ../list/list.db

#应急处理
@CMD|61|2|0|cd ../../bin; ./calluser mc_batch restart
@CMD|1002|0|0|(内部)修改密码

#@cmd|1:in 0:out|time id|begin time|end time 
@TIME_CTRL|1|1|07:00:00|09:10:00
@TIME_CTRL|0|2|15:15:00|19:40:00
@TIME_CTRL|0|3|09:05:00|15:18:00
