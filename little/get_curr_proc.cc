/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: get_curr_proc.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月06日 02时08分58秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月06日                  build this moudle  
 *****************************************************************************/
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

size_t 
get_executable_path( char* processdir,char* processname, size_t len)
{
	char* path_end;
	if(readlink("/proc/self/exe", processdir,len) <=0)
		return -1;

	path_end = strrchr(processdir,  '/');
	if(path_end == NULL)
		return -1;

	++path_end;
	strcpy(processname, path_end);
	*path_end = '\0';

	return (size_t)(path_end - processdir);
}

int 
main()
{
	char path[PATH_MAX];
	char processname[1024];
	get_executable_path(path, processname, sizeof(path));
	printf("directory:%s\nprocessname:%s\n",path,processname);
}
