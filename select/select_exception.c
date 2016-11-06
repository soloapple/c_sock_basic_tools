#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		printf("%s ip port\n", argv[0]);
		return 1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	int ret = 0;
	int yes = 0;
	int listenfd = 0;
    struct sockaddr_in address;    // server address information
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

	struct sockaddr_in client_address;
	socklen_t client_addrlength = sizeof(client_address);
	int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);
	if (connfd < 0)
		close(listenfd);

	char buf[1024];
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);

    while (1) {
		memset(buf, '\0', sizeof(buf));
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);

        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if (ret < 0) {
            perror("select");
            break;
        }		

        if (FD_ISSET(connfd, &read_fds)) {
			memset(buf, 0x00, sizeof(buf) - 1);
            ret = recv(connfd, buf, sizeof(buf) - 1, 0);
            if (ret <= 0) {
				break;
            }             
			printf("get %d bytes of normal data:%s\n", ret, buf);
		}

		 if (FD_ISSET(connfd, &exception_fds)) {
			memset(buf, 0x00, sizeof(buf) - 1);
            ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
            if (ret <= 0) {
				break;
            }             
			printf("get %d bytes of oob data:%s\n", ret, buf);
		}

	}

	close(connfd);
	close(listenfd);	

	return 0;
}
