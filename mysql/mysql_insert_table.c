/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: mysql_insert_table.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年01月15日 00时38分18秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年01月15日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include "/revive/git/c_sock_basic_tools/include/colorpt.h"
#define	PORT 3308

void
insert_mysql_data(MYSQL *db, char *query_info, int *pos_buff)
{
	int res_mysql_query = 0;

	mysql_autocommit(db, 0);

	res_mysql_query = mysql_real_query(db, query_info, *pos_buff);
	if ( res_mysql_query )
	{
		LOGE("mysql real query error: %s\n", mysql_error(db));
		return;
	}

	do 
	{
		MYSQL_RES *res = mysql_store_result(db);
		if ( res )
		{   
			mysql_free_result(res);
		}   
		else
		{   
			if ( mysql_field_count(db) != 0 )
				break;
		}   
	} while ( !mysql_next_result(db) );

	mysql_commit(db);

	return ;
}		

int 
main(int argc, char *argv[])
{
	MYSQL mysql_conn;
	MYSQL_RES *mysql_result;
	MYSQL_ROW mysql_row;

	char execsql[256];
	int f1,f2,num_row,num_col;

	if (mysql_init(&mysql_conn) == NULL)
		return 0;

	if ( !mysql_real_connect(
				&mysql_conn, "172.24.141.28", 
				"root", "secdataclient", "gap", 
				PORT, "/tmp/mysql.sock", 0) )
	{
		LOGE("%s\n", mysql_error(&mysql_conn));
		return 0;
	}

	int version = mysql_get_client_version();
	LOGD("version %d\n", version);

	int ret = mysql_set_character_set(&mysql_conn, "gbk");
	LOGD ("set character ret : %d, now setis :%s\n", ret, mysql_character_set_name(&mysql_conn));

	char data[4096] = {0};
	char *insert_word = (char*)calloc(256, 1);
	strcpy(insert_word, "insert into tab_system set optime =\"2015-06-19 01:01:13\", severity=\"warning\", msg=\"王勇\";");
	int len = sprintf(data, "%s", insert_word);
	LOGD("data:%s\n", data);

	insert_mysql_data(&mysql_conn, data, &len);

	sprintf(execsql,"select * from tab_system;");
	if(mysql_query(&mysql_conn,execsql) != 0)
		return 0;
	
	mysql_result=mysql_store_result(&mysql_conn);
	num_row=mysql_num_rows(mysql_result);
	num_col=mysql_num_fields(mysql_result);
	printf("row: %d,col: %d\n",num_row,num_col);

	for (f1 = 0; f1 < num_row; f1++)
	{
		mysql_row=mysql_fetch_row(mysql_result);
		for (f2 = 0; f2 < num_col; f2++)
		{
			printf("[Row %d,Col %d]==>[%s]\n",f1,f2,mysql_row[f2]);
		}
	}

	mysql_free_result(mysql_result);
	mysql_close(&mysql_conn);
	return 0;
}
