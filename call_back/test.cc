/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: test.cc
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��02��20�� 21ʱ10��09��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��02��20��                  build this moudle  
 *****************************************************************************/

#include "test.h"
/**********************************************************
 *   Name: main
 *   Desc: use a call back function to do something.
 *  Input: 
 * Output: 
 * Return: int, 0 on success; 
 *             -1 on error;
 * Others: -
 *********************************************************/
int main()
{
	send_alarm_out = send_alarm_out_call_back;	
	send_alarm_out(NULL, NULL);
}


