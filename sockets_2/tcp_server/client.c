#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define BUFF_SIZE 256

int main() {

	struct sockaddr_in server = 
	{
		.sin_family = AF_INET,
		.sin_port = htons(7007),
		.sin_addr.s_addr = inet_addr("127.0.0.1"),

	};


	int sock_fd;

	char buff[BUFF_SIZE];
	int serv_addrlen = 0;
	serv_addrlen = sizeof(server);
	int cl_count = 0;

	while(1) {
		sock_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(sock_fd == -1) {
		perror("client: socket tcp error");
		exit(EXIT_FAILURE);
		}

		int rv = connect(sock_fd, (struct sockaddr *)&server, serv_addrlen);
	
		if(rv == -1) {

			perror("client: connect error");
			exit(EXIT_FAILURE);
		}
		
		rv = recv(sock_fd, &buff, BUFF_SIZE, 0);
		if(rv == -1) {

			perror("client: receive message error");
			exit(EXIT_FAILURE);

		} else {

			printf("The message received\n");
		}

		printf("%s\n\n", buff);

	}
	

	close(sock_fd);
	exit(EXIT_SUCCESS);
}