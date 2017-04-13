/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: macro_joint_str.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��04��13�� 19ʱ58��17��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��04��13��                  build this moudle  
 *****************************************************************************/
#include <syslog.h>

#define	LOG_SYSTEM_DEBUG(fmt, ARGS...)     syslog(FAC_LOG_SYSTEM | LOG_DEBUG, fmt, ##ARGS)
#define MOD_SYSTEM        1 
#define FAC_LOG_SYSTEM    LOG_LOCAL0

int main()
{
	LOG_SYSTEM_DEBUG("mode=%d, msg=\"%s\"", MOD_SYSTEM, "123");
}
