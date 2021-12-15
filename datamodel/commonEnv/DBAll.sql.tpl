!!include setCommand.tpl!!
!!enter DB!!
	!!travel schemas!!
		!!let schemaName=@name!!
----\!!@schemaName!!_create.sql
!!travel self!!
@!!@schemaName!!_!!@name!!_create
!!next!!
----\!!@schemaName!!_clear.sql
!!travel self!!
@!!@schemaName!!_!!@name!!_clear
!!next!!
----\!!@schemaName!!_drop.sql
!!travel self!!
@!!@schemaName!!_!!@name!!_drop
!!next!!
		!!travel self!!
			!!let groupName=@name!!
			!!command startSetCommand();!!
			!!travel self!!
				!!command addSetCommand();!!
			!!next!!
			!!enter DB!!
				!!travel tableGroups!!
					!!if !strcmp(@group,@groupName)!!
----\!!@schemaName!!_!!@group!!_clear.sql
!!include clearTable.sql.tpl!!
----\!!@schemaName!!_!!@group!!_drop.sql
!!include dropTable.sql.tpl!!
----\!!@schemaName!!_!!@group!!_create.sql
!!include createTable.sql.tpl!!
----\!!@schemaName!!_!!@group!!_createMysql.sql
!!include createTableMysql.sql.tpl!!
					!!endif!!
				!!next!!
			!!leave!!
		!!next!!
	!!next!!
!!leave!!
