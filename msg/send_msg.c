/***************************************************************************************
 *   Copyright (C), 2016, X Co., Ltd.
 *
 *    Filename: send_msg.c
 * Description: 
 *     Version: 1.0
 *     Created: soloapple   08/27/16 01:24:31
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              soloapple   08/27/16                  build this moudle  
 ***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPEN_FILE  "test"
#define	UNIXSTR_PATH "/tmp/unix.str"

int main(int argc, char *argv[])
{
    int clifd;
    struct sockaddr_un servaddr;
    int ret;
    struct msghdr msg;
    struct iovec iov[1];
    char buf[100] = "AABB";
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct cmsghdr *pcmsg;
    int fd;
    
    clifd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clifd < 0) {
        printf("socket failed.\n");
        return -1;
    }
    
    fd = open(OPEN_FILE, O_CREAT| O_RDWR, 0777);
    if (fd < 0) {
        printf("open test failed.\n");
        return -1;
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    
    ret = connect(clifd,(struct sockaddr *)&servaddr, sizeof(servaddr));
    if (ret < 0) {
        printf("connect failed.\n");
        return 0;
    }
    
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    iov[0].iov_base = buf;
    iov[0].iov_len = 100;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
    
    pcmsg = CMSG_FIRSTHDR(&msg);
    pcmsg->cmsg_len = CMSG_LEN(sizeof(int));
    pcmsg->cmsg_level = SOL_SOCKET;
    pcmsg->cmsg_type = SCM_RIGHTS;
    *((int *)CMSG_DATA(pcmsg)) = fd;
    
    ret = sendmsg(clifd, &msg, 0);
    printf("ret = %d.\n", ret);

	for ( ;; )
	{
		printf ( "(((((((((((((((((((\n" );
		strncpy(buf, "1234", strlen("1234"));
		iov[0].iov_len = 30;
		iov[0].iov_base = buf;
		ret = sendmsg(clifd, &msg, 0);
		printf("ret = %d.\n", ret);

		printf ( "(((((((((((((((((((\n" );
		strncpy(buf, "5678", strlen("1234"));
		iov[0].iov_len = 40;
		iov[0].iov_base = buf;
		ret = sendmsg(clifd, &msg, 0);
		printf("ret = %d.\n", ret);

		sleep(1);
	}

    return 0;
}

