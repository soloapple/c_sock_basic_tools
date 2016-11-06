/***************************************************************************************
 *   Copyright (C), 2006-2015, Legendsec Technology Co., Ltd.
 *
 *    Filename: epoll_chat_client.c
 * Description: 
 *     Version: 1.0
 *     Created: Liujfa   06/18/15 11:57:20
 *    Revision: none
 *
 *     History: <author>   <time>    <version >         <desc>
 *              Liujfa   06/18/15                  build this moudle  
 ***************************************************************************************/
#include "syshead.h"

#define USER_LIMIT 5
#define BUFFER_SIZE 64
#define FD_LIMIT 65535

struct client_data
{
	sockaddr_in address;
	char *write_buf;
	char buf[BUFFER_SIZE];
};

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option|O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

int main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		printf("usage: %s ip port\n", basename(argv[0]));
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);
	
	int yes = 1;
	int ret = 0;
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
    address.sin_family = AF_INET;         // host byte order
	inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);     // short, network byte order

	int listenfd = 0;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    if (bind(listenfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(listenfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

	client_data *users = new client_data[FD_LIMIT];
	pollfd fds[USER_LIMIT + 1];
	int user_counter = 0;
	int i = 0;
	for(i;i<=USER_LIMIT;++i)
	{
		fds[i].fd = -1;
		fds[i].events = 0;
	}
	fds[0].fd = listenfd;
	fds[0].events = POLLIN|POLLERR;
	fds[0].revents = 0;

	while (1)
	{
		ret = poll(fds, user_counter+1, -1);
		if (ret < 0)
		{
			printf("poll failure\n");
			break;
		}

		int i = 0;
		for (i; i<user_counter+1; ++i)
		{
			printf("val:fd[%d]:%d\n", i, fds[i].fd);

			puts("--------------------------------------");
			printf("circles\n ");
			puts("--------------------------------------");
			if ((fds[i].fd == listenfd) && (fds[i].revents & POLLIN))
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);

				int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
				if(connfd < 0)
				{
					printf("errno  is:%d\n", errno);
					continue;
				}
				if (user_counter >= USER_LIMIT)
				{
					const char* info = "too many users\n";
					printf("%s\n", info);
					send(connfd, info, strlen(info), 0);
					close(connfd);
					continue;
				}
				user_counter++;
				users[connfd].address = client_address;
				setnonblocking(connfd);
				fds[user_counter].fd = connfd;
				fds[user_counter].events = POLLIN|POLLRDHUP|POLLERR;
				fds[user_counter].revents = 0;
				printf("come a new user, now have %d users\n", user_counter);
			}
			else if (fds[i].revents & POLLERR)
			{
				printf("get an error from %d\n", fds[i].fd);
				char errors[100];
				memset(errors, '\0', 100);
				socklen_t length = sizeof(errors);
				if (getsockopt(fds[i].fd, SOL_SOCKET, SO_ERROR, &errors, &length) < 0)
				{
					printf("get socket option failed\n");
				}
				continue;
			}
			else if (fds[i].revents & POLLRDHUP)
			{
				users[fds[i].fd] = users[fds[user_counter].fd];
				close(fds[i].fd);
				fds[i] = fds[user_counter];
				i--;
				user_counter--;
				printf("a client left\n");
			}
			else if (fds[i].revents & POLLIN)
			{
				int connfd = fds[i].fd;
				memset(users[connfd].buf, '\0', BUFFER_SIZE);
				ret = recv(connfd, users[connfd].buf, BUFFER_SIZE -1, 0);
				printf("get %d bytes of client data %s from %d\n",ret, users[connfd].buf, connfd);
				if (ret < 0)
				{
					if (errno != EAGAIN)
					{
						close(connfd);
						users[fds[i].fd] = users[fds[user_counter].fd];
						fds[i] = fds[user_counter];
						i--;
						user_counter--;
					}
				}
				else if(ret == 0)
				{
					close(connfd);
				}
				else
				{
					int j;
					for(j=1; j<=user_counter; ++j)
					{
						if (fds[j].fd == connfd)
							continue;

						fds[j].events |= ~POLLIN;
						fds[j].events |= POLLOUT;
						users[fds[j].fd].write_buf = users[connfd].buf;
					}
				}
			}
			else if (fds[i].revents & POLLOUT)
			{
				int connfd = fds[i].fd;
				if ( ! users[connfd].write_buf)
					continue;
				ret = send(connfd, users[connfd].write_buf,
						strlen(users[connfd].write_buf), 0);
				users[connfd].write_buf = NULL;

				fds[i].events |= ~POLLOUT;
				fds[i].events |= POLLIN;
			}
		}
	}
	
	delete [] users;
	close(listenfd);
	return 0;
}
