/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *   
 *    Filename: send_alarm_out_call_back.h
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��02��20�� 21ʱ24��05��
 *    Revision: none
 *      
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��02��20��                  build this moudle
 *****************************************************************************/

#include "common.h"

typedef struct alarm_send_out_switch {
	bool b_send_mail;
	bool b_send_log;
	bool b_send_snmp;
} alarm_send_out_switch_t;			

void send_alarm_out_call_back(char *msg, alarm_send_out_switch_t *out_switch);
