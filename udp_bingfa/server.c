/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: server.c
 * Description: 
 *     Version: 1.0
 *     Created: Liujfa   06/18/15 00:32:12
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   06/18/15                  build this moudle  
 ***************************************************************************************/
#include "syshead.h"

int main(int argc,char *argv[])
{
    int socket_fd, file_fd;
    struct sockaddr_in netaddr;
    struct sockaddr_in fromaddr;
    socklen_t len = sizeof(struct sockaddr);

    memset(&netaddr, 0, len);
    netaddr.sin_family = AF_INET;
    netaddr.sin_port = htons(5000);
    netaddr.sin_addr.s_addr = INADDR_ANY;

    if((socket_fd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("Fail to create socket");
        return -1;
    }
    if (bind(socket_fd, (struct sockaddr*)&netaddr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    
    while (1) {
        char buf[100] = {};
        int ret = recvfrom(socket_fd, buf, 100, 0, (struct sockaddr *)&fromaddr, &len);
        if (ret == -1) {
            perror("recvfrom");
            exit(1);
        }
        printf("buf=%s\n", buf);
        if (fork() == 0)
            break;
        printf("next==============\n");
    }
    int sock2;
    if((sock2 = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        perror("child Fail to create socket");
        return -1;
    }
    if (sendto(sock2, "world", 5, 0, (struct sockaddr*)&fromaddr, len) == -1) {
        perror("child sendto");
        exit(1);
    }


    while (1) {
        char buf[100] = {};
        int ret = recvfrom(sock2, buf, 100, 0, (struct sockaddr *)&fromaddr, &len);
        if (ret == -1) {
            perror("child recvfrom");
            exit(1);
        }
        printf("child buf=%s\n", buf);
    }

    close(socket_fd);

    return 0;
}

