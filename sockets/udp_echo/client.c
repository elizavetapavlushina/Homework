#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFF 256

int main() {

	int sock_fd;

	if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in server =
	{
		server.sin_family = AF_INET,
		server.sin_port = htons(7000),
		server.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};
	

	int addrlen = 0;
	addrlen = sizeof(server);
	
	const char message[] = "Hello!";
	char buffer[SIZE_BUFF];

	while (1) {

		if(sendto(sock_fd, &message, sizeof(message), 0, 
				(struct sockaddr *)&server, addrlen) == -1) {

			perror("client: send message error");
			exit(EXIT_FAILURE);
	} else {

		printf("The message sended\n");
	}

		if(recvfrom(sock_fd, &buffer, SIZE_BUFF, 0,
				(struct sockaddr *)&server, &addrlen) == -1) {

			perror("client: receive message error");
			exit(EXIT_FAILURE);

		} else {

			printf("The message received\n");
		}

		printf("%s\n", buffer);
		sleep(1);
	}
	

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}