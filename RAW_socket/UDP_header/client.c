#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#define PACK_SIZE 256
#define IP_HDR_LEN 20
#define UDP_HDR_LEN 8

// use with /sockets/udp_echo/server.c

int main() {

	int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

	if(sock_fd  == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}
	
	struct udphdr* udp_packet; 
	char packet[PACK_SIZE];

	udp_packet = (struct udphdr*) packet;

	udp_packet->uh_sport = htons(7111);
	udp_packet->uh_dport = htons(7100);
	udp_packet->uh_ulen = htons(PACK_SIZE);
	udp_packet->uh_sum = 0;
	
	char *payload;
	payload = packet + UDP_HDR_LEN; 

	const char message[] = "Hello world!";
	strcpy(payload, message);

	struct sockaddr_in server =
	{
		server.sin_family = AF_INET,
		server.sin_port = htons(7111),
		server.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};
	socklen_t addrlen = sizeof(server);

	int rv = sendto(sock_fd, &packet, PACK_SIZE, 0, (struct sockaddr *)&server, addrlen);

	if(rv == -1) {

		perror("client: send packet error");
		exit(EXIT_FAILURE);

	} else {

		printf("The packet sended\n");
	}

	while (1) {
		rv = recvfrom(sock_fd, &packet, PACK_SIZE, 0, NULL, NULL);

		if(rv == -1) {

			perror("client: receive packet error");
			exit(EXIT_FAILURE);

		}

		if ( ((struct udphdr*)(packet + IP_HDR_LEN))->uh_sport == htons(7100) ){

			printf("server packet received\n");
			break;
		}
		
	}
	printf("%s\n", payload + IP_HDR_LEN);

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}