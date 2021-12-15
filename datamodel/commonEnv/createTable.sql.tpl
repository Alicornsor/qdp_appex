!!travel self!!
!!let tableName=@name!!
--******************************
--~{44=(~}!!@title!!~{1m~}
--******************************
create table t_!!@name!!
(
!!let keyList=" "!!
!!travel Columns!!
	!!if @pumpid!=0!!,!!endif!!!!@name!! !!@type!! !!if valid_name("default")!! default !!@default!! !!endif!!!!if isNotNull(@tableName)!!not null!!endif!!
	!!if isKey(@tableName)!!
		!!if !strcmp(@keyList," ")!!
			!!let keyList=@name!!
		!!else!!
			!!let keyList=multiaddstring(3,@keyList,",",@name)!!
		!!endif!!
	!!endif!! 
!!next!!
!!if strcmp(@keyList," ")!!
	,constraint pk_!!@name!! primary key (!!@keyList!!)
!!endif!!
);

comment on table t_!!@name!! is '!!@title!!';
!!travel Columns!!
	comment on column t_!!@tableName!!.!!@name!! is '!!@label!!';
!!next!!

!!travel Index!!
!!if !isDelete(@tableName)!!
--~{44=(~}!!@title!!~{1m5D~}!!@label!!
create !!if isUnique(@tableName)!!unique!!endif!! index i_!!@tableName!!_!!@name!! on t_!!@tableName!!
(
!!travel self!!
	!!if @pumpid!=0!!,!!endif!!!!@name!! !!@order!!
!!next!!
);

!!endif!!
!!next!!

!!next!!
