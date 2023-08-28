#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE_BUFF 256

int main() {

	int sock_fd;

	if((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1) {

		perror("sniffer: socket error");
		exit(EXIT_FAILURE);
	}
	
	char buffer[SIZE_BUFF];
	int udp_packets_cnt;

	while (1) {

		if(recvfrom(sock_fd, &buffer, SIZE_BUFF, 0, NULL, NULL) == -1) {

			perror("sniffer: receive packet error");
			exit(EXIT_FAILURE);
		}
		udp_packets_cnt++; 
		printf("Udp packets count %d\n",udp_packets_cnt);
	}
	

	if (close(sock_fd) < 0) {

		perror("sniffer: close socket error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
	
}