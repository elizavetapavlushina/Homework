#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFF 256

bool get_message(char * buffer) {

	int i = 0;
	int symbol;
	while((symbol = getchar()) != '\n') {

		if (i < SIZE_BUFF - 1){
			buffer[i] = symbol;
			i++;
		}
		else return false;
		
	}
	buffer[i] = '\0';

	return true;
}

int main() {

	struct sockaddr_in server;
	int sock_fd;

	if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(7000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int addrlen = 0;
	addrlen = sizeof(server);

	if(connect(sock_fd, (struct sockaddr *)&server, addrlen) == -1) {

		perror("client: connect error");
		exit(EXIT_FAILURE);
	}
	
	char message[SIZE_BUFF] = "";

	printf("Enter the massage:\n");
	if(!(get_message(message))) {

		printf("server: message is full\n");
		exit(EXIT_FAILURE);
	}
	

	if(send(sock_fd, &message, SIZE_BUFF, 0) == -1) {

		perror("client: send message error");
		exit(EXIT_FAILURE);
	} else {

		printf("The message sended\n");
	}

	if(recv(sock_fd, &message, SIZE_BUFF, 0) == -1) {

		perror("client: receive message error");
		exit(EXIT_FAILURE);

	} else {

		printf("The message received\n");
	}

	printf("%s\n", message);

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}