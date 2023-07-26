#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ADDRESS "/tmp/stream_serv"
#define SIZE_BUFF 256

int main() {

	struct sockaddr_un server, client;
	int sock_fd;

	if((sock_fd = socket(AF_LOCAL, SOCK_STREAM, 0)) == -1) {

		perror("server: socket error");
		exit(1);
	}

	server.sun_family = AF_LOCAL;
	strcpy(server.sun_path, ADDRESS);
	unlink (ADDRESS);

	int addrlen = 0;
	addrlen = sizeof(server);
	
	if(bind(sock_fd, (struct sockaddr *)&server, addrlen) == -1) {

		perror("server: bind error");
		exit(1);
	}
	
	if(listen(sock_fd, 5) == -1) {

		perror("server: listen error");
		exit(1);
	}
	

	int new_s_fd;
	int client_ad_len = 0;
	client_ad_len = sizeof(client);

	if((new_s_fd = accept(sock_fd, (struct sockaddr *)&client, &client_ad_len)) == -1) {

		perror("server: accept error");
		exit(1);
	}
	
	char message[SIZE_BUFF] = "";

	if(recv(new_s_fd, &message, SIZE_BUFF, 0) == -1) {

		perror("server: receive message error");
		exit(1);

	} else {

		printf("The message received\n");
	}
	printf("%s\n", message);

	char serv_mes[SIZE_BUFF]= "Hello!";
	if(send(new_s_fd, &serv_mes, SIZE_BUFF, 0) == -1) {

		perror("server: send message error");
		exit(1);
	} else {

		printf("The message sended\n");
	}
	
	close(new_s_fd);
	close(sock_fd);

	exit(EXIT_SUCCESS);

}