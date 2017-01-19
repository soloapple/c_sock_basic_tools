/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: mysql_query_table.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年01月13日 11时28分34秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年01月13日                  build this moudle  
 *****************************************************************************/
#include<stdio.h>
#include<mysql.h>

#define	MYSQL_PORT 3306

int main(int argc, char *argv[])
{
	MYSQL mysql_conn;
	MYSQL_RES *mysql_result;
	MYSQL_ROW mysql_row;

	char execsql[256];
	int f1,f2,num_row,num_col;

	if(mysql_init(&mysql_conn)!=NULL)
	{
		if(mysql_real_connect(&mysql_conn, "172.24.141.28", "root", "123456", "gap", MYSQL_PORT, "/tmp/mysql.sock", 0)!=NULL)
		{
			printf("connect success!!!\n");
			sprintf(execsql,"select * from tab_system;");

			if(mysql_query(&mysql_conn,execsql)==0)
			{
				printf("query success!\n");
				mysql_result=mysql_store_result(&mysql_conn);
				num_row=mysql_num_rows(mysql_result);
				num_col=mysql_num_fields(mysql_result);
				printf("row: %d,col: %d\n",num_row,num_col);
				for(f1=0;f1<num_row;f1++)
				{
					mysql_row=mysql_fetch_row(mysql_result);
					for(f2=0;f2<num_col;f2++)
					{
						printf("[Row %d,Col %d]==>[%s]\n",f1,f2,mysql_row[f2]);
					}
				}
			}else
			{
				printf("query error!!!\n");
			} 
		}else
		{
			printf("connect failed\n");
		}
	}else
	{
		printf("initial failed\n");
	}
	mysql_free_result(mysql_result);
	mysql_close(&mysql_conn);
	return 0;
}
