#include "syshead.h"

#define MAX_EVENT_NUMBER 1024
#define TCP_BUFFER_SIZE  512
#define UDP_BUFFER_SIZE  1024

int setnonblocking(int fd)
{
	int old_option = fcntl(fd, F_GETFL);
	int new_option = old_option|O_NONBLOCK;
	fcntl(fd, F_SETFL, new_option);
	return old_option;
}

void addfd(int epollfd, int fd)
{
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
	setnonblocking(fd);
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

	int ret = 0;
	int listenfd = 0;
	int udpfd = 0;
	int yes = 1;
	struct sockaddr_in address;
		
	bzero(&address, sizeof(address));
    address.sin_family = AF_INET;         // host byte order
	inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);     // short, network byte order

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

	bzero(&address, sizeof(address));
    address.sin_family = AF_INET;         // host byte order
	inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);     // short, network byte order
	if ((udpfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
	
   	if (bind(udpfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }

	struct epoll_event events[ MAX_EVENT_NUMBER];
	int epollfd = epoll_create(5);
	assert(epollfd != -1);
	addfd(epollfd, listenfd);
	addfd(epollfd, udpfd);

	while(1)
	{
		int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
		if (number < 0)
		{
			printf("epoll failure\n");
			break;
		}	

		int i = 0;
		for (i; i<number; i++)
		{
			int sockfd = events[i].data.fd;
			if (sockfd == listenfd)
			{
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);

				int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
				addfd(epollfd, connfd);
			}
			else if (sockfd == udpfd)
			{
				char buf[UDP_BUFFER_SIZE];
				memset(buf, '\0', UDP_BUFFER_SIZE);
				struct sockaddr_in client_address;
				socklen_t client_addrlength = sizeof(client_address);
				ret = recvfrom(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
						(struct sockaddr*)&client_address, &client_addrlength);
				if (ret > 0)
				{
						sendto(udpfd, buf, UDP_BUFFER_SIZE - 1, 0,
						(struct sockaddr*)&client_address, client_addrlength);
				}
			}
			else if (events[i].events & EPOLLIN)
			{
				char buf[TCP_BUFFER_SIZE];
				while(1)
				{
					memset(buf, '\0', TCP_BUFFER_SIZE);
					ret = recv(sockfd, buf, TCP_BUFFER_SIZE - 1, 0);
					if (ret < 0)
					{
						if ((errno == EAGAIN) ||(errno == EWOULDBLOCK))
						{
							break;
						}
						close(sockfd);
						break;
					}
					else if(ret == 0)
					{
						close(sockfd);
					}
					else
					{
						send(sockfd, buf, ret, 0);
					}
				}
			}
			else
			{
				printf("something else happened\n");
			}
		}

	}

	close(listenfd);
	return 0;
}

