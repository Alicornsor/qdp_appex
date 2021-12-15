select t.userid,t.interfaceproductinfo,count(*) from t_oper_usersession t group by t.userid,t.interfaceproductinfo order by t.userid;
