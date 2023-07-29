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

	struct sockaddr_in client;
	struct sockaddr_in server = 
	{
		.sin_family = AF_INET,
		.sin_port = htons(7007),
		.sin_addr.s_addr = inet_addr("127.0.0.1"),

	};


	int tcp_sfd = socket(AF_INET, SOCK_STREAM, 0);

	if(tcp_sfd == -1) {
		perror("server: socket tcp error");
		exit(EXIT_FAILURE);
	}

	int rv = bind(tcp_sfd, (struct sockaddr *)&server, sizeof(server));

	if( rv == -1) {
		perror("server: tcp bind error");
		exit(EXIT_FAILURE);
	}

	rv = listen(tcp_sfd, 5);

	if(rv == -1) {
		perror("server: listen error");
		exit(EXIT_FAILURE);
	}

	int new_tcp_sfd;
	int cl_addr_len = sizeof(client);  
	const char tcp_message[] = "TCP!";
	char buff[BUFF_SIZE];
	int cl_count = 0;

	pid_t cpid;

	while (1){

		new_tcp_sfd = accept(tcp_sfd, (struct sockaddr *)&client, &cl_addr_len);

		if (new_tcp_sfd == -1){
			perror("server: accept error");
			exit(EXIT_FAILURE);
		} else {
			
			printf("Client connect\n");
			
		}

		cpid = fork();

		if (cpid == -1){
			perror("server: fork error");
			exit(EXIT_FAILURE);
		} else {
			rv = send(new_tcp_sfd, &tcp_message, sizeof(tcp_message), 0);

			if(rv == -1) {
				perror("server: send message error");
				exit(EXIT_FAILURE);
			} 
		}

	}
}