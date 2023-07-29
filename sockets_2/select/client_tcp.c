

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE_BUFF 256


int main() {

	struct sockaddr_in server =
	{
		.sin_family = AF_INET,
		.sin_port = htons(7007),
		.sin_addr.s_addr = inet_addr("127.0.0.1")
	};
	int sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if(sock_fd == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	

	int addrlen = 0;
	addrlen = sizeof(server);
	int rv = connect(sock_fd, (struct sockaddr *)&server, addrlen);
	
	if(rv == -1) {

		perror("client: connect error");
		exit(EXIT_FAILURE);
	}
	
	char buff[SIZE_BUFF];
	
	rv = recv(sock_fd, &buff, SIZE_BUFF, 0);
	if(rv == -1) {

		perror("client: receive message error");
		exit(EXIT_FAILURE);

	} else {

		printf("The message received\n");
	}

	printf("%s\n", buff);

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}