#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFF 256

int main() {

	struct sockaddr_in server =
	{
		server.sin_family = AF_INET,
		server.sin_port = htons(7000),
		server.sin_addr.s_addr = inet_addr("127.0.0.1"),

	};

	int sock_fd;
	if((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {

		perror("server: socket error");
		exit(EXIT_FAILURE);
	}

	int size_serv = sizeof(server);
	
	if(bind(sock_fd, (struct sockaddr *)&server, size_serv) == -1) {

		perror("server: bind error");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in client;
	int size_client = sizeof(client);

	
	char message[SIZE_BUFF];
	const char mod[] = "23";
	while(1){

		if(recvfrom(sock_fd, &message, SIZE_BUFF, 0, 
				(struct sockaddr *)&client, &size_client) == -1) {

			perror("server: receive message error");
			exit(EXIT_FAILURE);

		} else {

			printf("The message received\n");
		}
		printf("%s\n", message);

		strcat(message, mod);

		if(sendto(sock_fd, &message, SIZE_BUFF, 0, (struct sockaddr *)&client, size_client) == -1) {

			perror("server: send message error");
			exit(EXIT_FAILURE);
		} else {

			printf("The message sended\n");
		}

	}

	
	
	close(sock_fd);

	exit(EXIT_SUCCESS);

}