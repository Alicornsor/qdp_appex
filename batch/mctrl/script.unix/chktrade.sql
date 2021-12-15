select t.sysnumber,count(*) from t_oper_trade t group by t.sysnumber order by t.sysnumber;
exit;
