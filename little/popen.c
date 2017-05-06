/******************************************************************************
 *   Copyright (C), 2017, X Co., Ltd.
 *
 *    Filename: popen.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   2017��05��06�� 00ʱ11��47��
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   2017��05��06��                  build this moudle  
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
      perror("popenִ��ʧ�ܣ�");
      exit(1);
  }

  while ( fgets(result_buf, sizeof(result_buf), fp) != NULL )
  {
      if('\n' == result_buf[strlen(result_buf)-1])
      {
          result_buf[strlen(result_buf)-1] = '\0';
      }

      printf("���%s�� �����%s��\r\n", command, result_buf);
  }

  rc = pclose(fp);
  if ( -1 == rc )
  {
      perror("�ر��ļ�ָ��ʧ��");
      exit(1);
  }
  else
  {
      printf("���%s���ӽ��̽���״̬��%d�������ֵ��%d��\r\n", command, rc, WEXITSTATUS(rc));
  }

  return 0;
}
