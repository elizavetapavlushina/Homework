#include <sys/types.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SIZE_BUFF 256

int main() {

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock_fd == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in client =
	{
		client.sin_family = AF_INET,
		client.sin_port = htons(7000),
		client.sin_addr.s_addr = inet_addr("255.255.255.255"),
	};

	int retval = bind(sock_fd, (struct sockaddr *)&client, sizeof(client));
	
	if(retval == -1) {

		perror("client: bind error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server;
	int size_server = sizeof(server);
	
	char buffer[SIZE_BUFF];
	retval = recvfrom(sock_fd, &buffer, SIZE_BUFF, 0,
								(struct sockaddr *)&server, &size_server);

	if (retval == -1) {
 
		perror("client: receive message error");
		exit(EXIT_FAILURE);

	} else {

		printf("The message received\n");
	}

	printf("%s\n", buffer);

	if (close(sock_fd) == -1) {

		perror("client: socket close error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}