/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: popen.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017年05月06日 00时11分47秒
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017年05月06日                  build this moudle  
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#define MAXLINE 1024

int 
main()
{
  char result_buf[MAXLINE], command[MAXLINE];
  int rc = 0;
  FILE *fp = NULL;

  snprintf(command, sizeof(command), "lm ./ ");

  fp = popen(command, "r");
  if ( NULL == fp )
  {
      perror("popen执行失败！");
      exit(1);
  }

  while ( fgets(result_buf, sizeof(result_buf), fp) != NULL )
  {
      if('\n' == result_buf[strlen(result_buf)-1])
      {
          result_buf[strlen(result_buf)-1] = '\0';
      }

      printf("命令【%s】 输出【%s】\r\n", command, result_buf);
  }

  rc = pclose(fp);
  if ( -1 == rc )
  {
      perror("关闭文件指针失败");
      exit(1);
  }
  else
  {
      printf("命令【%s】子进程结束状态【%d】命令返回值【%d】\r\n", command, rc, WEXITSTATUS(rc));
  }

  return 0;
}
