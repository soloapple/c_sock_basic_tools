/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *   
 *    Filename: test.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年02月20日 21时34分40秒
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年02月20日                  build this moudle
 *****************************************************************************/

#include "send_alarm_out_call_back.h"

void (*send_alarm_out)(char *msg, alarm_send_out_switch_t *out_switch);
extern void send_alarm_out_call_back(char*, alarm_send_out_switch_t*);
