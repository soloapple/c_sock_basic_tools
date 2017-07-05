/******************************************************************************
 *   Copyright (C), 2017, 360 Legendsec Co., Ltd.
 *   soloapple   2017年07月03日 21时00分12秒
 *
 *   
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>

char cnt = 200;
int block = 10 * 1024 * 1024;

void * sigfree(int signal)
{
	for (i=0; i<cnt; i++) {
		if (mem[i]) {
			free mem[i];
			mem[i] = NULL;
		}
	}
}

	int
main(int argc, char *argv[])
{
	signal(SIGINT, free)
	char *mem[cnt];

	for (i=0; i<cnt; i++) {
		char mem[i] = (char *)malloc(block);
	}
	
	return 0;
}
