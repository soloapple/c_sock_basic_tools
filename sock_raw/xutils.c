#include <stdio.h>
#include <ctype.h>

#include "xutils.h"

void __print_x(unsigned char *str, int s, int e)
{
	printf("%2s", " ");
	while (s < e) {
		if (isprint(str[s]))
			printf("%c", str[s]);
		else
			printf(".");
		s++;
	}
	printf("\n");
}

/*********************************************************************
 * desc: output string content to hex, for example;
 * 31 32 33 34 35 36 37 38  31 32 33 34 35 36 37 38   1234567812345678
 * 39 30							                  90				  
 * date: 2014/06/25
 *********************************************************************/
void output_str_to_hex(unsigned char *str, int len)
{
	int i = 0, t = 0, s = len;
	unsigned char *ps = str;

	while (s--) {
		printf("%02x ", *ps);
		i++ ;

		if (i == 8)
			printf(" ");

		if (!(i % 16)) {
			__print_x(str, t, t + i);
			t += i;
			i = 0;
		}
		ps++ ;
	}

	/* printf leave content */
	if (i > 0) {
		s = i;
		while (s++ < 16) {
			if (s == 8)
				printf(" ");

			/* 02x + " " */
			printf("%3s", " ");
		}
		__print_x(str, t, t + i);
	}
	printf("\n");
}
