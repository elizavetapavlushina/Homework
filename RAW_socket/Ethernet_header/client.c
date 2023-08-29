#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <netinet/in.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PACK_SIZE 256
#define ETH_HDR_LEN 14
#define IP_HDR_LEN 20
#define UDP_HDR_LEN 8

#define MAC_SIZE 6

unsigned char source_mac[MAC_SIZE] = {0x08, 0x00, 0x27, 0x68, 0x20,0x6a};
unsigned char dest_mac[MAC_SIZE] = {0x08, 0x00, 0x27, 0xee, 0xb8, 0xea};

// use with /sockets/udp_echo/server.c

int ip_check_sum_count(short *cur_ip_hdr) {

	
	int check_sum = 0;

    for (int i = 0; i < 11; i++) {

    	check_sum += *cur_ip_hdr;
    	cur_ip_hdr++;
    }
    char tmp = check_sum >> 16;
    check_sum = (check_sum & 0xFFFF) + tmp;

    printf("%d\n\n", check_sum);
    
    return check_sum;
}


int main() {

	int sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	if(sock_fd  == -1) {

		perror("client: socket error");
		exit(EXIT_FAILURE);
	}

    struct sockaddr_ll eth_server =
	{
		eth_server.sll_family = AF_PACKET,
		eth_server.sll_ifindex = if_nametoindex("enp0s3"),
		eth_server.sll_halen = 6,
	};
	socklen_t size_serv = sizeof(eth_server);

	for (int i = 0; i < MAC_SIZE; i++){

		eth_server.sll_addr[i] = source_mac[i];
		
	}

	char packet[PACK_SIZE];

	struct ethhdr* eth_header;
    eth_header = (struct ethhdr*) packet;

    for (int i = 0; i < MAC_SIZE; i++){

		eth_header->h_dest[i] = dest_mac[i];
		eth_header->h_source[i] = source_mac[i];
	}
    eth_header->h_proto = htons(0x0800);


    struct iphdr* ip_header;
    ip_header = (struct iphdr*)(packet + ETH_HDR_LEN);

    ip_header->ihl = 5; 
    ip_header->version = 4;
    ip_header->tos = 0; 
    ip_header->tot_len = PACK_SIZE - ETH_HDR_LEN;
    ip_header->id = htonl(22222);
    ip_header->frag_off = false;
    ip_header->ttl = 128;
    ip_header->protocol = IPPROTO_UDP;
    ip_header->check = 0;
    ip_header->saddr = inet_addr("192.168.0.81");
    ip_header->daddr = inet_addr("192.168.0.1");

// checksum ip

    short *cur_ip_hdr;
    cur_ip_hdr = (short *)(packet + ETH_HDR_LEN);
    int check_sum = 0;

	check_sum = ip_check_sum_count(cur_ip_hdr);

    if (check_sum <= 0) {

    	printf("client: ip_check_sum erorr");
    	exit(EXIT_FAILURE);
    }
    check_sum = ~(check_sum);

    ip_header->check = check_sum;


    struct udphdr* udp_packet;
	udp_packet = (struct udphdr*)(packet + ETH_HDR_LEN + IP_HDR_LEN);

	udp_packet->uh_sport = htons(7111);
	udp_packet->uh_dport = htons(7100);
	udp_packet->uh_ulen = htons(PACK_SIZE - ETH_HDR_LEN - IP_HDR_LEN);
	udp_packet->uh_sum = 0;


	char *payload;
	payload = packet + UDP_HDR_LEN + IP_HDR_LEN + ETH_HDR_LEN; 

	const char message[] = "Hello world!";
	strcpy(payload, message);

	int rv = sendto(sock_fd, &packet, PACK_SIZE, 0,
							 (struct sockaddr *)&eth_server, size_serv);

	if (rv == -1) {

		perror("client: sendto packet error");
		exit(EXIT_FAILURE);

	} else {

		printf("The packet sended\n");
	}

	while (1) {

		rv = recvfrom(sock_fd, &packet, PACK_SIZE, 0,
								 (struct sockaddr *)&eth_server, &size_serv);
		if(rv == -1) {

			perror("client: receive packet error");
			exit(EXIT_FAILURE);
		}

		if ( ((struct udphdr*)(packet + ETH_HDR_LEN + IP_HDR_LEN))->uh_sport == htons(7100) ){

			printf("Packet received\n");
			break;
		}
		
	}
	printf("%s\n", payload);

	if (close(sock_fd) != 0) {

		perror("client: close socket error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
	
}