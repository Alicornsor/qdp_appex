export ORACLE_BASE=/oracle
export ORACLE_HOME=/oracle/product/11.2
export PATH=$PATH:$ORACLE_HOME/bin:.:$HOME
export SHLIB_PATH=$ORACLE_HOME/lib:$ORACLE_HOME/rdbms/lib:/oracle
export NLS_LANG=american_america.zhs16gbk
export NLS_DATE_FORMAT='YYYY-MM-DD HH24:MI:SS'
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ORACLE_HOME/lib:/lib:/usr/lib:$ORACLE_HOME/rdbms/lib:.
export LD_LIBRARY_PATH


USER=qdp
PASSWD=admin123
TNSNAME=qdp

sqlplus -S  $USER/$PASSWD@$TNSNAME @$1.sql
