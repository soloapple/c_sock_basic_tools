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
#include <unistd.h>
#include <stdarg.h>
#include "colorpt.h"

#define	_GUN_SOURCE
#include <getopt.h>

#define	PORT 3308

const char *short_options = "i:p:u:w:d:s:h";
struct option long_options[] =
{
	{"ip", 1, NULL, 'i'},    
	{"port", 1, NULL, 'p'},
	{"user", 1, NULL, 'u'},
	{"pass", 1, NULL, 'w'},
	{"db", 1, NULL, 'd'},
	{"sock", 1, NULL, 's'},
	{0, 0, 0, 0}
};

void
usage(int argc, char *argv[])
{
	printf ( "%s -i ip -p port -u user w pass -s sock -d db\n", argv[0] );
}

typedef struct sql_login {
	char *ip;
	char *port;
	char *user;
	char *pass;	
	char *db;	
	char *sock;
} sql_login_t;			

sql_login_t login;

void
insert_mysql_data(MYSQL *db, char *query_info, int *pos_buff)
{
	int res_mysql_query = 0;

	mysql_autocommit(db, 0);

	res_mysql_query = mysql_real_query(db, query_info, *pos_buff);
	if ( res_mysql_query )
	{
		LOGE("mysql real query error: %s\n", mysql_error(db));
		LOGE("[%s]\n", query_info);
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

void
parse_args(int argc, char *argv[])
{
	int c;      
	while((c = getopt_long (argc, argv, short_options, long_options, NULL)) != -1)      
	{
		switch (c)
		{
			case 'i':
				login.ip = strdup(optarg);
				break;
			
			case 'p':
				login.port = strdup(optarg);
				break;
				
			case 'u':
				login.user = strdup(optarg);
				break;

			case 'w':
				login.pass = strdup(optarg);
				break;

			case 's':
				login.sock = strdup(optarg);
				break;

			case 'd':
				login.db = strdup(optarg);
				break;
			
			case 'h':
				usage(argc, argv);	
				break;
		
			default:
				usage(argc, argv);	
				break;
		}
	}
}

int 
main(int argc, char *argv[])
{
	int i = 0;
	int len = 0;
	int total = 0;

	parse_args(argc, argv);
	LOGD("parse arg OK.\n");

	MYSQL mysql_conn;
	MYSQL_RES *mysql_result;
	MYSQL_ROW mysql_row;

	if (mysql_init(&mysql_conn) == NULL)
	{
		LOGE("init mysql error\n");
		return 0;
	}
	LOGD("init mysql OK.\n");

	LOGD("+-----------------------------------------------------------------+\n");
	LOGD("| login.ip   = %-50s |\n", login.ip);
	LOGD("| login.port = %-50s |\n", login.port);
	LOGD("| login.user = %-50s |\n", login.user);
	LOGD("| login.pass = %-50s |\n", login.pass);
	LOGD("| login.db   = %-50s |\n", login.db);
	LOGD("| login.sock = %-50s |\n", login.sock);
	LOGD("+-----------------------------------------------------------------+\n");

	if ( !mysql_real_connect(
				&mysql_conn, login.ip, 
				login.user, login.pass, login.db, 
				atoi(login.port), login.sock,
				CLIENT_MULTI_STATEMENTS) )
	{
		LOGE("%s\n", mysql_error(&mysql_conn));
		return 0;
	}
	LOGD("connect mysql right\n");

	int version = mysql_get_client_version();
	LOGD("version %d\n", version);

	int ret = mysql_set_character_set(&mysql_conn, "gbk");
	LOGD ("set character ret : %d, now setis :%s\n", ret, mysql_character_set_name(&mysql_conn));

	char *data = (char*)calloc(8192, 1);
	char ins_tab_alarm[1024] = {0};
	sprintf(ins_tab_alarm, "%s",
	"insert into tab_alarm set optime =\"2017-06-12 15:06:21\", severity=\"info\", reptime=\"0\", gap_ip=\"(null)\", mode=\"10\", type=\"6\", \
	msg=\"告警日志，左边告一次，右边告一次，上边告一次，下边告一次\";"
	);

	char ins_tab_manage[1024] = {0};
	strcat(ins_tab_manage, "insert into tab_manage set optime=\"2015-06-19 01:01:12\", severity=\"debug\", \
	msg=\"这是管理日志的测试，因为是测试日志，所以要尽可能的长，长到你怀疑你的代码为止.\";");

	for ( i = 0; i < 10; i++ ) 
	{
//		len = sprintf(data + total, "%s", ins_tab_alarm);
//		total += len;

		len = sprintf(data + total, "%s", ins_tab_manage);
		total += len;
	}

	
	total++;
	LOGI("len+:%d\n", total);
	LOGI("+------------------------------------------------------------------+\n");
	LOGI(" %-65s \n", data);
	LOGI("+------------------------------------------------------------------+\n");

	total = strlen(data);
	for ( i = 0; i < 700000; i++ ) 
	{
		insert_mysql_data(&mysql_conn, data, &total);
	}

	free(data);
	mysql_close(&mysql_conn);

	return 0;
}
