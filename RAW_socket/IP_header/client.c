#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

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
	
	int flag = 1;
	int rv = setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(flag));
	if (rv == -1) {

        perror("client: setsockopt error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server =
	{
		server.sin_family = AF_INET,
		server.sin_port = htons(7111),
		server.sin_addr.s_addr = inet_addr("127.0.0.1"),
	};
	socklen_t addrlen = sizeof(server);

    struct iphdr* ip_header;
    char packet[PACK_SIZE];
     
    ip_header = (struct iphdr*) packet;

    ip_header->ihl = 5; 
    ip_header->version = 4;
    ip_header->tos = 0; 
    ip_header->tot_len = PACK_SIZE;
    ip_header->id = htonl(22222);
    ip_header->frag_off = false;
    ip_header->ttl = 128;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->check = 0;
    ip_header->saddr = inet_addr("127.0.0.1");
    ip_header->daddr = server.sin_addr.s_addr;

    struct udphdr* udp_packet;
	udp_packet = (struct udphdr*)(packet + IP_HDR_LEN);

	udp_packet->uh_sport = htons(7111);
	udp_packet->uh_dport = htons(7100);
	udp_packet->uh_ulen = htons(PACK_SIZE - IP_HDR_LEN);
	udp_packet->uh_sum = 0;
	
	char *payload;
	payload = packet + UDP_HDR_LEN + IP_HDR_LEN; 

	const char message[] = "Hello world!";
	strcpy(payload, message);

	rv = sendto(sock_fd, &packet, PACK_SIZE, 0, (struct sockaddr *)&server, addrlen);

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

			printf("Packet received\n");
			break;
		}
		
	}
	printf("%s\n", payload);

	close(sock_fd);
	exit(EXIT_SUCCESS);
	
}