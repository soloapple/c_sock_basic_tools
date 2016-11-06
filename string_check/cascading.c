/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: a.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/19/16 08:08:12
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/19/16                  build this moudle  
 ***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char sqlstr[] = "'mode=system' 'msg=testmsg' 'src_ip=127.0.0.1'";
const char flag_mode[] = "mode=";
char *deal_with_system_line(char *line, char *table_name);

char bigbuffer[BUFSIZ];
static int ptr_buf;

char *
get_value_from_key( char *line, char *key, char *value)
{
	printf ( "line:%s\n", line );
	printf ( "lline:%d\n", strlen(line) );
	printf ( "key:%s\n", key );
	printf ( "lkey:%d\n", strlen(key) );

	static char _value[128] = {0};
	char* p = (char*)memmem(line, strlen(line), key, strlen(key));
	if (p != NULL)
	{
		sscanf(p+strlen(flag_mode), "%[^']", _value);
		value = _value;
		printf ( "mode name:%s\n", value);
		return value;
	}

	printf ( "NULL\n" );

	return NULL;
}

char *
get_table_name_from_mode(char *mode_name, char *table_name)
{
	static char _table_name[128] = {0};
	sprintf(_table_name, "tab_%s", mode_name);
	table_name = _table_name;
	
	return table_name;
}

char *
get_table_name( char *line )
{
	char *p, *t_mode_name;

   	t_mode_name = get_value_from_key(line, flag_mode, t_mode_name);
	if (t_mode_name == NULL)
		return NULL;	

	//get table name from mode name
	char *table_name = get_table_name_from_mode(t_mode_name, table_name);
	printf ( "table_name:%s\n", table_name );

	if (table_name != NULL)
		deal_with_system_line(line, table_name);
}

char *	
deal_with_system_line(char *line, char *table_name)
{
	char s_sql_insert[BUFSIZ] = {0};
	char s_field_name[BUFSIZ] = {0};
	char s_field_value[BUFSIZ] = {0};

	char *saveptr;

	int len = strlen(line);		
	int n = 0;
	int count = 0;

	for (len; len>0; len--)
	{
		if(line[len] == ' ')
			count++;
	}

	printf ( "%d\n", count );
	printf("%s\n", line);

	char *pairs[count+1];
	pairs[0] = strtok_r(line, " ", &saveptr);
	printf ( "pairs[%d]:%s\n", n, pairs[n] );

	for(n=1; n<count+1; n++)
	{
		pairs[n] = strtok_r(NULL, " ", &saveptr);
		printf ( "pairs[%d]:%s\n", n, pairs[n] );
	}

	char *table = NULL;
	char *key, *value;
	int vlen, ntable;
	for(n=0; n<count+1; n++)
	{
		printf ( "pairs:%s\n", pairs[n] );
		key = strtok_r(pairs[n], "=", &saveptr) + 1;
		value = strtok_r(NULL, "'", &saveptr);
		if (n != count)
		{
			strncat(s_field_name, key, strlen(key));
			strncat(s_field_name, ",", 1);
			strncat(s_field_value, value, strlen(value));
			strncat(s_field_value, ",", 1);
		}
		else
		{
			strncat(s_field_name, key, strlen(key));
			strncat(s_field_value, value, strlen(value));
		}
	}

	sprintf(s_sql_insert, "insert into %s (%s) values (%s);", table_name, s_field_name, s_field_value);
	printf ( "sql insert:%s\n", s_sql_insert );

	sprintf(bigbuffer + ptr_buf, "%s", s_sql_insert);
	ptr_buf += strlen(s_sql_insert);
	printf("bigbuffer:%s\n", bigbuffer);

	return NULL;
}

int 
getid()
{
	return random();	
}

int
main ( int argc, char *argv[] )
{
	//time_t tm = time(NULL);
	//srandom(tm);
	char *buffer = (char*)malloc(128);
	
	memcpy(buffer, sqlstr, strlen(sqlstr));
	get_table_name(buffer);

	memcpy(buffer, sqlstr, strlen(sqlstr));
	get_table_name(buffer);

	memcpy(buffer, sqlstr, strlen(sqlstr));
	get_table_name(buffer);

	memcpy(buffer, sqlstr, strlen(sqlstr));
	get_table_name(buffer);
//	printf ( "random is %d\n", getid() );
//	printf ( "random is %d\n", getid() );
//	printf ( "random is %d\n", getid() );
	
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
