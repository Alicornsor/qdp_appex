概要：
	此脚本集单机部署、多机部署、统一启停、备份等一体，代码模块化程度极高，灵活方便
	7.2版本的mctrl需要重建对应的用户数据
作者：
	徐忠华
目录说明：
	bin: shell脚本，用于控制系统启停和部署系统
	mctrl:运维操作界面
	sql:数据库执行脚本
	run:应用程序和每个程序的配置和启动脚本
	list:系统用户、模块、数据库等配置列表，是脚本中最多变化的地方，也是配置的主要文件

使用方法：
	bin下面的脚本是最主要的脚本，各个脚本的使用方法
	(1)showall:
		showall 查看list.run下面的程序的运行情况
		showall 1 查看list.run下面第一个模块的运行情况
		showall qtrade 查看list.run下面qtrade模块的运行情况
		showall a 查看list.run下面所有模块的运行情况
		
	(2)startall/stopall/restartall和showall一样
		和startall一样，其核心逻辑在run_batch中
		
	(3)mcall(控制机的控制机)
		mcall show 查看list.user下面各个目标机器控制的程序的运行情况
		mcall show 1 查看list.user下面第一个目标机器控制的程序的运行情况
		mcall show qdp01 查看list.user下面代号为qdp01目标机器控制的程序的运行情况
		mcall show a 查看list.user下面所有目标机器控制的程序的运行情况
		mcall show qdp01 qtrade 查看list.user下面代号为qdp01目标机器控制的list.run下面qtrade模块的运行情况
		mcall show qdp01 1 查看list.user下面代号为qdp01目标机器控制的list.run下面qtrade模块的运行情况
		mcall show qdp01 a 查看list.user下面代号为qdp01目标机器控制的list.run下面所有模块的运行情况
		其核心逻辑在 mc_batch中
		
	(4)dball和mcall的运行机制一样
		其核心伙计在 dbaction.sh中
		
	以上程序可以选择运行哪个模块，使用calluser调用即可有选择的界面，手动选择运行哪个程序
	calluser默认使用list.user作为选择依据，也可以带上参数，提供list供其选择：
	./calluser dbaction.sh insctp ../list/list.db :使用list.db作为选择源，运行dbaction.sh脚本
	./calluser mc_batch show :使用list.user作为默认选择源，运行mc_batch脚本
	
	(5)portfuns:端口使用情况检查脚本
		portfuns link 查看list.link下面的端口号的使用情况
		portfuns up 查看list.up下面的端口号的使用情况
		portfuns port 查看list.port下面的端口号的使用情况
		
	
	