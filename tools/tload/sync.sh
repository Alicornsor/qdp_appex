
echo "execute pk_std_sync.sp_runcmd('$1','$2');" > sync.sql
echo quit  >> sync.sql

sqlplus smt/smt123@orabiz @sync.sql >> sync.log
