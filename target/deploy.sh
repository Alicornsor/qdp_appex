#!/bin/bash
#Auth:xlong
#Date:20160223

ENV_FILE=$HOME/.bash_profile
FILE_LIST=$HOME/bin/list.run
FILE_SERVICE=$HOME/bin/service.cfg

Modify_ini()
{
	if [ "$1" == "list_run" ]; then
		echo -n "[$2] Modify list.run[y/n]? "
		read _VALUE
		if [ "$_VALUE" == "y" ]; then
			vim $FILE_LIST
		fi
	else
		echo -n "[$2] Modify $1.ini[y/n]? "
		read _VALUE
		if [ "$_VALUE" == "y" ]; then
			vim $RUN_DIR/$1/$1.ini
		fi
	fi
}

Modify_cfg()
{
	Modify_ini "list_run" "11"
	rm -rf $FILE_SERVICE 1>/dev/null 2>/dev/null
	touch $FILE_SERVICE


	_arr=();
	_arr=(`cat $FILE_LIST`);

	for LINE in ${_arr[@]}
	 do
		remark=`echo $LINE | grep "^\s*#"`
		if [ "$remark" != "" ]; then
			continue;
		fi
		LINE=`echo $LINE | tr -d "\n"`
		echo "$LINE          01          3       @" >> $FILE_SERVICE
		Modify_ini $LINE "7"
	done 

}

Add_file()
{
	_RET=`cat $ENV_FILE | grep "$1"`
	if [ "$_RET" == "" ]; then
		echo "$1" >> $ENV_FILE 
	fi
}

Add_env()
{
	
	Add_file "alias mv='mv -i'"
	Add_file "export LANG=en_US"
	Add_file "export PATH=$PATH:$HOME/bin/:."
	Add_file "LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:."
	Add_file "export LD_LIBRARY_PATH"
	source .bash_profile
}


DeplayNew()
{
	echo "**********************************************************************************"
	echo "deploy new env"
	echo "**********************************************************************************"
	cd $HOME
	pwd 1>/dev/null 2>/dev/null

	echo "[1] tar xzf bin.tar.gz"
	tar xzf bin.tar.gz

	echo "[2] mkdir run"
	RUN_DIR=$HOME/run
	if [ -e $RUN_DIR ]; then
		rm -rf run
	fi
	mkdir run

	echo "[3] tar xzf run.tar.gz -C run"
	tar xzf run.tar.gz -C run

	echo "[4] tar xzf ini.tar.gz -C run"
	tar xzf ini.tar.gz -C run

	echo "[5] modify $ENV_FILE"
	Add_env
	echo "[6] add authorized_keys"
	cd $HOME
	pwd 1>/dev/null 2>/dev/null
	mkdir .ssh

	#Must be 700, why?
	chmod 700 .ssh -R
    cd .ssh
	pwd 1>/dev/null 2>/dev/null
	ssh-keygen
	cp id_rsa.pub authorized_keys
	cd $HOME/bin
	pwd 1>/dev/null 2>/dev/null
	rm -rf list.user 1>/dev/null 2>/dev/null
	touch list.user
	echo "$USER localhost" >> list.user

	Modify_cfg

	echo "[11] ./deploy_batch make_deploy_dir"
	rm -rf $HOME/qdata $HOME/qtrade $HOME/qmarket $HOME/qquery
	cd $HOME/bin
	pwd 1>/dev/null 2>/dev/null
	./deploy_batch make_deploy_dir

	echo "[12] deploy_batch cpall"
	./deploy_batch cpall

	cd $HOME
	pwd 1>/dev/null 2>/dev/null

	echo "**********************************************************************************"
	echo "All is done!!!"
	echo "**********************************************************************************"
}

DeplayOld()
{
	echo "**********************************************************************************"
	echo "deploy old env"
	echo "**********************************************************************************"
	Modify_ini "qdata" "1"
	Modify_ini "qmarket" "2"
	Modify_ini "qquery" "3"
	Modify_ini "qtrade" "4"

	cd $HOME/bin
	pwd 1>/dev/null 2>/dev/null
	./deploy_batch cpall
	cd $HOME
	pwd 1>/dev/null 2>/dev/null
	echo "**********************************************************************************"
	echo "All is done!!!"
	echo "**********************************************************************************"
}

Delete_env()
{
	cd $HOME
	pwd 1>/dev/null 2>/dev/null

	_arr=();
	_arr=(`cat $FILE_LIST`);

	for LINE in ${_arr[@]}
	 do
		remark=`echo $LINE | grep "^\s*#"`
		if [ "$remark" != "" ]; then
			continue;
		fi
		LINE=`echo $LINE | tr -d "\n"`
		rm -rf $HOME/$LINE 1>/dev/null 2>/dev/null
	done 

	rm -rf bin run .ssh/env.flg 1>/dev/null 2>/dev/null
}

Main()
{
	if [ "$1" == "del" ]; then
		echo -n "Do you want to delete this env?[y/n] "
		read _VALUE
		if [ "$_VALUE" == "y" ]; then
			Delete_env
			echo "[OK] Del env success"
		fi
		return
	fi

	if [ -e "$HOME/.ssh/env.flg" ]; then
		DeplayOld
	else
		DeplayNew
		touch $HOME/.ssh/env.flg
	fi
}

Main $1
