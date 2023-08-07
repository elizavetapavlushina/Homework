#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

#include <pthread.h>
#include <string.h>

#include "msgbuf_struct.h"
#include "service_pool.h"

int servicing_UDP (struct msgbuf request) {

	const char message[] = "Hi!";
	int sock_fd;

	sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_fd == -1) {
		perror("servicing UDP socket");
		return EXIT_FAILURE;
	}

	struct sockaddr_in client = request.data.client;

	if(sendto(sock_fd, message, sizeof(message), 0, (struct sockaddr *)&client,
			sizeof(request.data.client)) == -1) {
		perror("servicing UDP sendto");
		return EXIT_FAILURE;
	}
	printf("UDP request processed\n");
	close(sock_fd);
	
	return EXIT_SUCCESS;

}

void* serving_server(void* argv) {

	int msqfd = *((int*) argv);
	int state = SLEEP;
	struct msgbuf request;
	long msgtyp;

	while (true) {

		switch (state) {

			case SLEEP:
				if (msgrcv(msqfd, (void *) &request, sizeof(request), msgtyp, 0) == -1) {
					perror("serving server: msgrcv");
					pthread_exit(NULL);
				} else {
					state = UDP;
				}
				break;

			case UDP:
				printf("UDP request processing started\n");

				if(servicing_UDP(request) == -1) {
					state = ERROR;
				} else {
					state = SLEEP;
				}
				break;

			case ERROR:
				fprintf(stderr, "error processing serving server, restart\n");
				state = SLEEP;

			default:
				break;
		}
	}
}

int gen_threads(int count_threads, int msqfd) {

	pthread_t threads[count_threads];
	pthread_attr_t thread_attr;

	if (pthread_attr_init(&thread_attr) != 0) {
		perror("pthread_attr_init");            
        return EXIT_FAILURE;
	}

	printf("generation service pool...\n");
	for (int i = 0; i < count_threads;) {
		if (pthread_create(&threads[i], &thread_attr, serving_server, &msqfd) != 0) { // second pharam
			perror("server: pthread_create");
			continue;
		}
		i++;
	}

	return EXIT_SUCCESS;

}