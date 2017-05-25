/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: rewind.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月20日 15时09分20秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月20日                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include<stdio.h>
#include<stdarg.h>
FILE *fp;

int 
vfpf(char *fmt, ...)
{
	va_list argptr;
	int cnt;
	va_start(argptr, fmt);
	cnt = vfprintf(fp, fmt, argptr);
	va_end(argptr);
	return(cnt);
}

FILE *
tmpfile()
{
	fp = fopen("/tmp/fp_tmp.txt", "a+");
	return fp;
}

int 
main()
{
	int inumber = 30;
	float fnumber = 90.0;
	char string[4] = "abc";

	fp = tmpfile();
	if (fp == NULL)
	{
		perror("tmpfile() call");
		exit(1);
	}

//	vfpf("%d %f %s\n", inumber, fnumber, string);
//	rewind(fp);
//	vfpf("$%d $%f $%s\n", inumber, fnumber, string);

	fprintf(fp,"%d %f %s\n", inumber, fnumber, string);
	fprintf(fp,"%d %f %s\n", inumber, fnumber, string);

//	fscanf(fp,"%d %f %s", &inumber, &fnumber, string);
//	printf("%d %f %s\n", inumber, fnumber, string);
	fclose(fp);

	return 0;
}
