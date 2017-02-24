/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: macro_offset.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月24日 05时52分02秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月24日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

/* this two kinds write way is all ok ---> */
//#define offset(MEMBER, TYPE) ((size_t) &((TYPE*)0)->MEMBER)
#define offset(MEMBER, TYPE) (size_t) &(((TYPE*)0)->MEMBER)
#define offset_diff(MEMBER, TYPE) (size_t) &(((TYPE*)4)->MEMBER)

struct same
{ 
	size_t field_1; 
	size_t field_2; 
}; 

struct diff 
{
	int num;
    char ch;
    float fl;
};

int
main() 
{ 
	printf("<same> %d:%d\n", offset(field_1, struct same), offset(field_2, struct same)); 

    printf("<diff> num)= %d\n", offset_diff(num, struct diff) - 4);
    printf("<diff> ch) = %d\n", offset_diff(ch, struct diff) - 4);
    printf("<diff> f1) = %d\n", offset_diff(fl, struct diff) - 4);

	return 0;
} 
