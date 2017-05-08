/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: ctrim.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��05��06�� 06ʱ28��59��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��05��06��                  build this moudle  
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>

char *
ctrim(char* s, char c)
{
    char *t  = s;
    while ( *s == c ) 
    {   
        s++;
    };  

    if ( *s )
    {   
        char *t1 = s;
        while ( *s )
        {   
            s++;
        };  

        s--;

        while ( *s == c ) 
        {   
            s--;
        };  

        while (t1 <= s)
        {   
            *(t++) = *(t1++);
        }   
    }   

    *t = 0;

    return s;
}

int
main(int argc, char *argv[])
{
	char s[] = "  sss  ";
	ctrim(s, ' ');
	printf ( "%s\n", s );
	
	return 0;
}
