/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: inet_pton4.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月08日 05时59分01秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月08日                  build this moudle  
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int 
inet_pton4(src, dst)
    const char *src;
    unsigned char *dst;
{
    static const char digits[] = "0123456789";
    int saw_digit, octets, ch; 
    unsigned char tmp[4], *tp;
	int rrr;

    saw_digit = 0;
    octets = 0;
    *(tp = tmp) = 0;
    while ((ch = *src++) != '\0') {
        const char *pch;

        if ((pch = strchr(digits, ch)) != NULL) {
			printf ( "pch:%s digits:%s X:%d\n", pch, digits, (pch - digits) );
            unsigned int new = *tp * 10 + (pch - digits);
			printf ( "new: %d\n", new );

            if (new > 255)
                return (0);
            *tp = new;
            if (! saw_digit) {
                if (++octets > 4)
				{
					printf ( "octets:%d\n", octets );
                    return (0);
				}
				printf ( "one time\n" );
                saw_digit = 1;
            }   
        } else if (ch == '.' && saw_digit) {
            if (octets == 4)
                return (0);
            *++tp = 0;
            saw_digit = 0;
        } else
            return (0);
    }   
    if (octets < 4)
        return (0);
    memcpy(dst, tmp, 4);
    memcpy(&rrr, tmp, 4);
	printf ( "tmp:%#+05x\n", rrr );
	printf ( "tmp:%c%c%c%c\n", tmp[0], tmp[1], tmp[2], tmp[3] );
    return (1);
}



	int
main(int argc, char *argv[])
{
	char *s = (char *)calloc(16, 1);

	inet_pton4("192.168.1.1", s);
	printf ( "%x\n", atoi(s) );

	free(s);
	s = NULL;

	return 0;
}






