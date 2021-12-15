
echo execute SMT.pk_std_sync.sp_runcmd('%1','%2'); > sync.sql
echo quit  >> sync.sql

sqlplus system/oracle@BIZDB2 @sync.sql >> sync.log
