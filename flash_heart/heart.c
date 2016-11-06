/***************************************************************************************
 *   Copyright (C), 2006-2016, Legendsec Technology Co., Ltd.
 *
 *    Filename: heart.c
 * Description: Heart
 *     Version: 1.0
 *     Created: Liujfa   05/07/16 09:47:18
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   05/07/16                  build this moudle  
 ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

void strroll(char *str)
{
	int ix = 0;
	char tmp = 0;

	if ( !str ) {
		return;
	}

	tmp = str[0];

	for ( ix = 1; str[ix] != '\0'; ix++ ) {
		str[ix - 1] = str[ix];
	}

	str[ix - 1] = tmp;
	return;
}

int main()
{

	float x, y, z, f;
	char str[] = ".:-~=+o80@";

	while ( 1 ) {
		for ( y = 1.5f; y > -1.5f; y -= 0.1f ) {
			for ( x = -1.5f; x < 1.5f; x += 0.05f ) {

				z = x * x + y * y - 1;
				f = z * z * z - x * x * y * y * y;
				printf("\033[40;31m%c\033[1m", f <= 0.0f ? str[(int)(f * -8.0f)] : ' ');
			}
			putchar('\n');
		}
		strroll(str);
		usleep(100000);
//		getchar();
		printf("\033[2J");
	}

	return 0;
}
