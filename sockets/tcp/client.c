#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ADDRESS "/tmp/stream_serv"
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

	struct sockaddr_un server;
	int sock_fd;

	if((sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1) {

		perror("client: socket error");
		exit(1);
	}
	
	server.sun_family = AF_LOCAL;
	strcpy(server.sun_path, ADDRESS);

	int addrlen = 0;
	//addrlen = sizeof(server.sun_family) + strlen(server.sun_path);
	addrlen = sizeof(server);

	if(connect(sock_fd, (struct sockaddr *)&server, addrlen) == -1) {

		perror("client: connect error");
		exit(1);
	}
	
	char message[SIZE_BUFF] = "";

	printf("Enter the massage:\n");
	if(!(get_message(message))) {

		printf("server: message is full\n");
		exit(1);

	} else {

		printf("The message sended\n");
	}

	if(send(sock_fd, &message, SIZE_BUFF, 0) == -1) {

		perror("client: send message error");
		exit(1);
	}

	if(recv(sock_fd, &message, SIZE_BUFF, 0) == -1) {

		perror("client: receive message error");
		exit(1);

	} else {

		printf("The message received\n");
	}

	printf("%s\n", message);

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}