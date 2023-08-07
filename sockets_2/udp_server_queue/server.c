#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdbool.h>
#include <signal.h>

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "msgbuf_struct.h"
#include "service_pool.h"

volatile bool terminating = false;

void term_handler(int signum) {

	fputs("\nStart close server\n", stdout);
	terminating = true;
}

int main() {

	setbuf(stdout, NULL);

	sigset_t newset;
	sigfillset(&newset);

	struct sigaction new_action =
	{
		.sa_handler = term_handler,
		.sa_flags = 0,
		.sa_restorer = NULL,
		.sa_mask = newset
	};

	int rv = sigaction(SIGINT, &new_action, NULL);
	if (rv == -1) {
		perror("server: sigaction");
	}

	int msqfd;
	key_t key = ftok("server.c", 'S');

	msqfd = msgget(key, (IPC_CREAT | IPC_EXCL | 0777));
	if (msqfd == -1) {
		perror("server: msgget");
		exit(EXIT_FAILURE);
	}
	printf("Queue create id#%d\n", msqfd);

	int count_threads = 2;
	rv = gen_threads(count_threads, msqfd);
	if (rv == -1){
		fprintf(stderr, "generation thread poll error\n");
		exit(EXIT_FAILURE);
	}

	int sock_udp;
	sock_udp = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_udp == -1) {
		perror("server: socket create");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in server =
	{
		.sin_family = AF_INET,
		.sin_addr.s_addr = inet_addr("127.0.0.1"),
		.sin_port = htons(7077),
	};

	rv = bind(sock_udp, (struct sockaddr *)&server, sizeof(server));
	if (rv == -1) {
		perror("server: bind");
		exit(EXIT_FAILURE);
	}

	printf("UDP socket created with IP:%s ", inet_ntoa(server.sin_addr));
    printf("port:%s\n", "7077");

    int cl_addr_len;
    struct msgbuf request;

    while (true) {
    	printf("\nWaiting connections...\n");

    	if (terminating) {
    		goto terminating;
    	}

    	cl_addr_len = sizeof(request.data.client);
    	request.mtype = UDP_REQUEST;

    	rv = recvfrom(sock_udp, request.mtext, MSG_SIZE, 0, 
    			(struct sockaddr *)&(request.data.client), &cl_addr_len);
    	if (rv == -1) {
    		perror("server: recvfrom");
    		exit(EXIT_FAILURE);
    	}

    	rv = msgsnd(msqfd, (void *) &request, sizeof(request), 0);
    	if (rv == -1) {
    		perror("server: msgsnd");
    		exit(EXIT_FAILURE);
    	}
    	printf("A request from the client was added to the queue.\n");
        printf("Type:%d ", UDP_REQUEST);
        printf("message:%s\n", request.mtext);
    }

    terminating: if (msgctl(msqfd, IPC_RMID, 0) == -1) {
    	perror("server: msgctl");
    	exit(EXIT_FAILURE);
    }
    printf("Queue completed\n");

    close(sock_udp);

    printf("Sockets completed\n");

    exit(EXIT_SUCCESS);

}