ALTER TABLE `t_oper_systeminfo` ADD UNIQUE INDEX systeminfo_index ( `systemid` );

ALTER TABLE `t_oper_order` ADD UNIQUE INDEX order_index ( `exchangeid`, `ordersysid`, `systemid` );

ALTER TABLE `t_oper_trade` ADD UNIQUE INDEX trade_index ( `exchangeid`, `tradeid`, `ordersysid`, `systemid` );

ALTER TABLE `t_oper_investoraccount` ADD UNIQUE INDEX account_index ( `brokerid`, `accountid`, `systemid` );

ALTER TABLE `t_oper_investorposition` ADD UNIQUE INDEX position_index (`brokerid`,  `exchangeid`,  `clientid`, `instrumentid`,`direction`, `systemid` );

ALTER TABLE `t_oper_user` ADD UNIQUE INDEX  user_index ( `brokerid`, `userid`, `systemid` );

ALTER TABLE `t_oper_usersession` ADD UNIQUE INDEX  sesion_index ( `brokerid`, `userid`, `sessionid`, `systemid` );

ALTER TABLE `t_oper_instrument` ADD UNIQUE INDEX  instrument_index (  `exchangeid`, `instrumentid`,`systemid` );

ALTER TABLE `t_oper_exchange` ADD UNIQUE INDEX  exchange_index ( `exchangeid`,`systemid` );