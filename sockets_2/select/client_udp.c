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
	int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock_fd  == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	

	int addrlen = 0;
	addrlen = sizeof(server);
	
	const char message[] = "hi!";
	char buff[SIZE_BUFF];
	
	int rv = sendto(sock_fd, &message, sizeof(message), 0, (struct sockaddr *)&server, sizeof(server));

	if(rv == -1) {

		perror("client: send message error");
		exit(EXIT_FAILURE);

	} else {

		printf("The message sended\n");
	}

	int svr_addr_len = sizeof(server);
	rv = recvfrom(sock_fd, &buff, SIZE_BUFF, 0, (struct sockaddr *)&server, &svr_addr_len);

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