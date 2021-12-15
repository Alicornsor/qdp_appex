select t.sysnumber,t.userid,t.interfaceproductinfo,count(*) from t_oper_usersession t group by t.sysnumber,t.userid,t.interfaceproductinfo order by t.sysnumber;
exit;
