set serveroutput off
set termout on
set trimspool on
set feed on
set verify on
set pagesize 0
set linesize 9999
set head off

delete from t_oper_order where sysnumber='&1';
delete from t_oper_trade where sysnumber='&1';
delete from t_oper_usersession where sysnumber='&1';
delete from t_oper_tmdbaccomplish where sysnumber='&1';
delete from t_oper_instrument where sysnumber='&1';
delete from t_Oper_DataSyncStatus where sysnumber='&1';

delete from t_oper_clientposition where sysnumber='&1' ;
delete from t_oper_investoraccount where sysnumber='&1';
delete from t_oper_user where sysnumber='&1';
insert into t_oper_clientposition (select * from t_sync_clientposition where sysnumber='&1');
insert into t_oper_investoraccount (select * from t_sync_investoraccount where sysnumber='&1');
insert into t_oper_user (select * from t_sync_user where sysnumber='&1');

update t_sync_systemstatus set systemstatus='2' where sysnumber='&1';
exit;
