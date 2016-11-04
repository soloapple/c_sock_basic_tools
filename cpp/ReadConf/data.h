/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *   
 *    Filename: data.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/18/16 19:32:42
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/18/16                  build this moudle
 ***************************************************************************************/


#ifndef  data_INCLUDE
#define  data_INCLUDE

#if  __cplusplus
extern "C" {
#endif  

struct s_test_this {
	int member;
};

void init_struct(s_test_this *ithis);

#if  __cplusplus
}
#endif  

#endif   
