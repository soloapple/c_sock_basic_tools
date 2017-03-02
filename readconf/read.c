/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: maincgi.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年03月02日 12时35分01秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年03月02日                  build this moudle  
 *****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#include "webadmin.h"
#include "cgi.h"


typedef enum {
	sz_label = 128,
	sz_file = 1024
} sz_config;				

char *path = "/storage/hawk/syslog-ng/sqlsyslogd/etc/sql_alarm_out.conf";

void line_handle_switch(char *line);
void line_handle_snmp(char *line);
void line_handle_script(char *line);
void line_handle_log(char *line);
void line_handle_mail(char *line);
void line_handle_mail_list(char *line);

char *cgiDebug;
typedef void (*config_line_handle)(char *line);

typedef struct config_item 
{
	char line_label[sz_label];
	config_line_handle line_handle;
} config_item_t;			

config_item_t item[] = 
{
	{
		line_label:"switch",
		line_handle:line_handle_switch,		   
	},
	{
		line_label:"script",
		line_handle:line_handle_script,
	},
	{
		line_label:"mailbasic",
		line_handle:line_handle_mail,
	},
	{
		line_label:"log",
		line_handle:line_handle_log,	
	},
	{
		line_label:"snmp",
		line_handle:line_handle_snmp,
	},
	{
		line_label:"maillist",
		line_handle:line_handle_mail_list	   
	}
};

typedef struct line_pair 
{
	char *key;
	char *value;
} line_pair_t;			

typedef struct line_pos 
{
	size_t start;
	size_t end;

	int n;
} line_pos_t;			

typedef struct mail_conf 
{
	char mail_addr_local[128];
	char mail_addr_server[128];
	char mail_ip[16];
	char mail_port[16];
} mail_conf_t;			

typedef struct mail_list_conf {
	char mail_addr[256];
	struct mail_list_conf *next;	
} mail_list_conf_t;			

mail_conf_t c_mail;
mail_list_conf_t *c_list_head, *c_list_tail;

void
mail_display()
{
//	printf ( "%s\n", c_mail.mail_addr_local );
//	printf ( "%s\n", c_mail.mail_addr_server );
//	printf ( "%s\n", c_mail.mail_addr_ip );
//	printf ( "%s\n", c_mail.mail_addr_port );
	
	printf ( "local:  %s", c_mail.mail_addr_local );
	printf ( "server: %s", c_mail.mail_addr_server );
	printf ( "ip:     %s", c_mail.mail_ip );
	printf ( "port:   %s", c_mail.mail_port );
}

void
mail_list_display()
{
	mail_list_conf_t *t = c_list_head->next;

	while ( t != NULL )
	{
		printf ( "mail address:%s", t->mail_addr );
		t = t->next;
	}
}

int
read_conf()
{
	int fi;
	int i;

	char line[sz_file];
	int got_label;
	int nmemb = (int)(sizeof(item)/sizeof(config_item_t));

	FILE *fp = fopen(path, "r+");
	if ( fp == NULL )
	{
		printf ( "file is null\n" );
		return -1;
	}

	while ( fgets(line, sz_file, fp) != NULL )
	{
		if ( strstr(line, "#") != NULL )
			continue;

		if( (line[0] == '\n') || (line[0] == ' ') || (line[0] == '\n') )
			continue;

		if ( strstr(line, "[") != NULL )
		{
			got_label = 0;

			for ( i=0; i<nmemb; i++ )	
			{
				if ( strstr(line, item[i].line_label ) != NULL )
				{
					got_label = 1;
					break;
				}
			}

			continue;
		}

		if ( got_label )
		{
			if ( item[i].line_handle )	
				item[i].line_handle(line);
		}
	}

	fclose(fp);

	return 0;
}

void
line_handle_switch(char *line)
{
	return;
}

void
line_handle_snmp(char *line)
{
	return;
}

void
line_handle_script(char *line)
{
	return;
}

void
line_handle_log(char *line)
{
	return;
}

void
line_handle_mail(char *line)
{
	char *p = NULL;

	if ( strstr(line, "mail_addr_local") != NULL )		
	{
		p = strstr(line, "=");
		p = p + 1;
		strncpy(c_mail.mail_addr_local, p, strlen(p));
		return;
	}

	if ( strstr(line, "mail_addr_server") != NULL )		
	{
		p = strstr(line, "=");
		p = p + 1;
		strncpy(c_mail.mail_addr_server, p, strlen(p));
		return;
	}
	
	if ( strstr(line, "mail_ip") != NULL )		
	{
		p = strstr(line, "=");
		p = p + 1;
		strncpy(c_mail.mail_ip, p, strlen(p));
		return;
	}
	
	if ( strstr(line, "mail_port") != NULL )		
	{
		p = strstr(line, "=");
		p = p + 1;
		strncpy(c_mail.mail_port, p, strlen(p));
		return;
	}

	return;
}

void
line_handle_mail_list(char *line)
{
	mail_list_conf_t *ml = (mail_list_conf_t*)malloc(sizeof(mail_list_conf_t));
	
	strncpy(ml->mail_addr, line, strlen(line));
	ml->next = NULL;

	c_list_tail->next = ml;
	c_list_tail = c_list_tail->next;

	return;
}

void
list_init()
{
	c_list_head = c_list_tail = (mail_list_conf_t *)malloc(sizeof(mail_list_conf_t));
	c_list_head->next = NULL;
}

void
list_free()
{
	mail_list_conf_t *t;
	mail_list_conf_t *p;
	t = p = c_list_head->next;

	while ( t!= NULL )
	{
		p = t;
		t = t->next;
		free(p);
		p = NULL;
	}
}

int
main(void)
{
	list_init();
	read_conf();

//	cgiHeaderContent("text/html");
//	printf("<html><head>main</head>"); 
//	printf("<body>it works.</body></html>"); 
	mail_display();
	mail_list_display();

	list_free();	

	return 0;
}
