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
#define MAX(a,b) (a >= b) ? a : b


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

	int udp_sfd = socket(AF_INET, SOCK_DGRAM, 0);

	if(udp_sfd == -1) {
		perror("server: socket udp error");
		exit(EXIT_FAILURE);
	}

	rv = bind(udp_sfd, (struct sockaddr *)&server, sizeof(server));

	if( rv == -1) {
		perror("server: udp bind error");
		exit(EXIT_FAILURE);
	}



	int maxfd = 0;
	maxfd = MAX(tcp_sfd, udp_sfd) + 1;
	fd_set rfds;

	int new_tcp_sfd;
	int cl_addr_len;  
	const char tcp_message[] = "TCP!";
	const char udp_message[] = "UDP!";
	char buff[BUFF_SIZE];
	int cl_count = 0;

	while (cl_count < 5) {

		FD_ZERO(&rfds);
		FD_SET(tcp_sfd, &rfds);
		FD_SET(udp_sfd, &rfds);

		rv = select(maxfd, &rfds, NULL, NULL, NULL);

		if(rv == -1) {
			perror("server: select error");
			exit(EXIT_FAILURE);
		}

		if(FD_ISSET(tcp_sfd, &rfds)) {

			
			cl_addr_len = sizeof(client);
			new_tcp_sfd = accept(tcp_sfd, (struct sockaddr *)&client, &cl_addr_len);
			
			if(new_tcp_sfd  == -1) {
				perror("server: accept error");
				exit(EXIT_FAILURE);
			} else {
				printf("client connect\n");
			}

			rv = send(new_tcp_sfd, &tcp_message, sizeof(tcp_message), 0);
			if(rv == -1) {
				perror("server: send tcp message error");
				exit(EXIT_FAILURE);
			}
			close (new_tcp_sfd);
			cl_count++;

		}

		if(FD_ISSET(udp_sfd, &rfds)) {

			cl_addr_len = sizeof(client);
			rv = recvfrom(udp_sfd, &buff, BUFF_SIZE, 0, (struct sockaddr *)&client, &cl_addr_len);
			
			if(rv == -1) {
				perror("server: recvfrom error");
				exit(EXIT_FAILURE);
			}
			else {
				printf("client connect, message received\n");
			}
			printf("%s\n", buff);

			rv = sendto(udp_sfd, &udp_message, BUFF_SIZE, 0, (struct sockaddr *)&client, cl_addr_len);
			if(rv == -1) {
				perror("server: sendto error");
				exit(EXIT_FAILURE);
			} else {
				printf("message sended\n");
			}

			cl_count++;
		}

	}
	close(tcp_sfd);
	close(udp_sfd);
	exit(EXIT_SUCCESS);
}