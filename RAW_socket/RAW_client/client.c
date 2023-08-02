#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFF 256
#define IP_HDR_LEN 20
#define TRN_HDR_LEN 8

int main() {

	int sock_fd;

	if((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in server =
	{
		server.sin_family = AF_INET,
		server.sin_port = htons(7700),
		server.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};
	

	int addrlen = sizeof(server);
	
	char buffer[SIZE_BUFF];
	char *payload;
	payload = buffer + TRN_HDR_LEN; 

	const char message[] = "Hello world";
	strcpy(payload, message);


	if(sendto(sock_fd, &buffer, SIZE_BUFF, 0, 
				(struct sockaddr *)&server, addrlen) == -1) {

		perror("client: send message error");
		exit(EXIT_FAILURE);
	} else {

		printf("The message sended\n");
	}

	while (1) {


		if(recvfrom(sock_fd, &buffer, SIZE_BUFF, 0, 
				(struct sockaddr *)&server, &addrlen) == -1) {

			perror("client: receive message error");
			exit(EXIT_FAILURE);

		} else {

			printf("The message received\n");
		}

		printf("%s\n", payload + IP_HDR_LEN);
	}
	

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}