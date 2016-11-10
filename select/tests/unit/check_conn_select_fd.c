#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../include/color_print.h"

#define MYPORT 1234    // the port users will be connecting to
#define BACKLOG 120     // how many pending connections queue will hold
#define BUF_SIZE 200

int fd_A[BACKLOG];    // accepted connection fd
int conn_amount;    // current connection amount

void showclient()
{
	char buf[256];
	char tmp[16];

    int i;
    LOGD("client amount: %d\n", conn_amount);
    for ( i = 0; i < BACKLOG; i++ ) 
	{
		sprintf(tmp, "[%-3d]:%-3d ", i, fd_A[i]);
        strcat(buf, tmp);
		if ( ((i+1) % 5) == 0 )
		{
			LOGD("%s\n", buf);
			memset(buf, '\0', sizeof(buf));
		}
    }
    printf("\n\n");
}

int main(void)
{
	return 0;
    int sock_fd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct sockaddr_in server_addr;    // server address information
    struct sockaddr_in client_addr; // connector's address information
    socklen_t sin_size;
    int yes = 1;
    char buf[BUF_SIZE];
    int ret;
    int i;

    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
        LOGE("socket");
        exit(1);
    }

    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
	{
        LOGE("setsockopt");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;         // host byte order
    server_addr.sin_port = htons(MYPORT);     // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        LOGE("bind");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG) == -1) {
        LOGE("listen");
        exit(1);
    }

    LOGN("listen port %d\n", MYPORT);

    fd_set fdsr;
    int maxsock;
    struct timeval tv;

    conn_amount = 0;
    sin_size = sizeof(client_addr);
    maxsock = sock_fd;

    for (;;) 
	{
        FD_ZERO(&fdsr);
        FD_SET(sock_fd, &fdsr);

        tv.tv_sec = 30;
        tv.tv_usec = 0;

        for (i = 0; i < BACKLOG; i++) 
		{
            if (fd_A[i] != 0) 
			{
                FD_SET(fd_A[i], &fdsr);
            }
        }
		
		fd_A[i-1] = 100;
        FD_SET(fd_A[i-1], &fdsr);

		LOGD("maxsock:%d\n", maxsock);
        ret = select(maxsock + 1, &fdsr, NULL, NULL, &tv);
        if (ret < 0) {
            LOGE("select");
            break;
        } else if (ret == 0) {
            LOGD("timeout\n");
            continue;
        } 
		
        for (i = 0; i < conn_amount; i++) 
		{
            if (FD_ISSET(fd_A[i], &fdsr)) 
			{
                ret = recv(fd_A[i], buf, sizeof(buf), 0);
                if (ret <= 0) 
				{        
                    LOGD("client[%d] close\n", i);
                    close(fd_A[i]);
                    FD_CLR(fd_A[i], &fdsr);
                    fd_A[i] = 0;
                } 
				else 
				{       
                    if (ret < BUF_SIZE)
                        memset(&buf[ret], '\0', 1);
                    LOGD("client[%d] send:%s\n", fd_A[i], buf);
                }
            }
        }

        if (FD_ISSET(sock_fd, &fdsr)) 
		{
            new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
            if (new_fd <= 0) 
			{
                LOGE("accept");
                continue;
            }

            if (conn_amount < BACKLOG) 
			{
                fd_A[conn_amount++] = new_fd;

                LOGD("new connection client[%d] %s:%d\n", conn_amount,
                        inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                if (new_fd > maxsock)
                    maxsock = new_fd;
            }
            else 
			{
                LOGW("max connections arrive, exit\n");
                send(new_fd, "bye", 4, 0);
                close(new_fd);
                break;
            }
        }
        showclient();
    }

    // close other connections
    for (i = 0; i < BACKLOG; i++) {
        if (fd_A[i] != 0) {
            close(fd_A[i]);
        }
    }

    exit(0);
}
 
 
