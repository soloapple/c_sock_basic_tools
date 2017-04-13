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
#include "common.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

typedef enum {
	sz_label = 128,
	sz_line  = 1024,
	sz_file = 4096
} sz_config;				

char *path = "/storage/hawk/syslog-ng/sqlsyslogd/etc/sql_alarm_out.conf";

char *label_mail_basic = "[ mailbasic ]";
char *label_mail_list = "[ maillist ]";

char *mail_addr_local = NULL;
char *mail_local_passwd = NULL;
char *mail_addr_server = "b@163.com";
char *mail_ip = "172.24.111.11";
char *mail_port = "6666";

char *T0_0 = "cc@qq.com";
char *T1_0 = "cc@163.com";

void
write_to_file(FILE *fp, char *buf)
{
	int fd;

	fd = fileno(fp);
	ftruncate( fd, 0);
	lseek(fd, 0, SEEK_SET);

	fwrite((void*)buf, 1, strlen(buf), fp);
}

void
label_not_exist(char *label_name, char *label_info, char **buf, int *nread, FILE *fp)
{
	printf ( "LABEL NOT exist, name:%s info:%s\n", label_name, label_info );
	char *tmp = *buf;

	strcat(tmp, label_name);
	strcat(tmp, "\n");
	strcat(tmp, label_info);
	strcat(tmp, "\n");

//	write_to_file(fp, *buf);
}

void
label_has_exist(char *label_name, char *label_info, char **buf, int *nread, FILE *fp)
{
	char *fst = NULL;
	char *snd = NULL;
	int xlen;

	char *xbuf = (char*)calloc(sz_line, 1);

	printf ( "LABEL HAS exist, name:%s info:%s\n", label_name, label_info );

	fst = (char*)memmem((void*)*buf, *nread, (void*)label_name, strlen(label_name));
	xlen = fst - *buf;

//	printf ( "offset:%d, length:%d\n", xlen, *nread - xlen );

	snd = (char*)memmem((void*)(fst+1), *nread - xlen, (void*)"[", 1);
	if ( snd != NULL )
	{
		printf ( "EXIST [ total:%d, offset:%d, length:%d\n", *nread, xlen, (int)(snd - fst) );
		memcpy(xbuf, fst, (int)(snd - fst));
	}
	else
	{
		printf ( "NOT EXIST [ total:%d, offset:%d, length:%d\n", *nread, xlen, *nread - xlen );
		memcpy(xbuf, fst, *nread - xlen);
	}


	xbuf = xbuf + strlen(label_name) + 1;

	printf ( "\n### rep src ###\n%s\n", xbuf );
	printf ( "\n### rep dst ###\n%s\n", label_info);

//	printf("%d\n", *nread - (fst - *buf));
	memreplace(buf, nread, xbuf, strlen(xbuf), label_info, strlen(label_info));

//	write_to_file(fp, *buf);
}


int
read_conf()
{
	int nread;
	char *buf = (char*)malloc(sz_file);

	char *mail_basic_info = (char*)malloc(sz_file);
	char *mail_list_info  = (char*)malloc(sz_file);

	char *p;

	FILE *fp = fopen(path, "a+");

	nread = fread(buf, 1, sz_file, fp);
	if ( nread < 0 )
		return -1;

	sprintf(mail_basic_info,
		"mail_addr_local = %s\n"
		"mail_local_passwd = %s\n"	
		"mail_addr_server = %s\n"
		"mail_ip = %s\n"
		"mail_port = %s\n",
		mail_addr_local,
		mail_local_passwd,
		mail_addr_server, 
		mail_ip, 
		mail_port 
	);

	strncat(mail_list_info, T0_0, strlen(T0_0));
	strncat(mail_list_info, "\n", 1);
	strncat(mail_list_info, T1_0, strlen(T1_0));
	strncat(mail_list_info, "\n", 1);

//	printf ( "&&& mail_basic_info:\n%s\n", mail_basic_info );
//	printf ( "&&& mail_list_info:\n%s\n", mail_list_info );

	p = (char*)memmem((void*)buf, nread, (void*)label_mail_basic, strlen(label_mail_basic));
	if ( p == NULL )
	{
		label_not_exist(label_mail_basic, mail_basic_info, &buf, &nread, fp);
		printf ( "replace one ---- now buf is:%s\n", buf );
	}
	else if ( p != NULL )
	{
		label_has_exist(label_mail_basic, mail_basic_info, &buf, &nread, fp);
		printf ( "replace two ---- now buf is:%s\n", buf );
	}


	p = (char*)memmem((void*)buf, nread, (void*)label_mail_list, strlen(label_mail_list));
	if ( p == NULL )
	{
		label_not_exist(label_mail_list, mail_list_info, &buf, &nread, fp);
		printf ( "replace three ---- now buf is:%s\n", buf );
	}
	else if ( p != NULL )
	{
		label_has_exist(label_mail_list, mail_list_info, &buf, &nread, fp);
		printf ( "replace four ---- now buf is:%s\n", buf );
	}

	write_to_file(fp, buf);
	fclose(fp);

	return 0;
}

int
main(void)
{
	read_conf();

	return 0;
}
