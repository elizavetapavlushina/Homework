#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SIZE_BUFF 256

int main() {

	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock_fd == -1) {

		perror("server: socket error");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in client =
	{
		client.sin_family = AF_INET,
		client.sin_port = htons(7000),
		client.sin_addr.s_addr = inet_addr("224.0.0.1"),

	};

	int retval;
	char message[SIZE_BUFF] = "Hello!";

	retval = sendto(sock_fd, &message, SIZE_BUFF, 0,
							 (struct sockaddr *)&client, sizeof(client));
	if(retval == -1) {

		perror("server: sendto message error");
		exit(EXIT_FAILURE);

	} else {

		printf("The message sended\n");
	}
	
	if (close(sock_fd) == -1) {

		perror("server: socket close error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}