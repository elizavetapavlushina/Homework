#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

#define Q_NAME "/queue"
#define BUFF_SIZE 255

int main() {

	mqd_t mq;

	mq = mq_open(Q_NAME, O_RDWR);
	if (mq == -1) {

		perror("client: mq_open error");
		exit(EXIT_FAILURE);
	}

	char buffer[BUFF_SIZE];

	int retval = mq_receive(mq, buffer, BUFF_SIZE, NULL);
	if (retval == -1) {

		perror("client: mq_receive error");
		exit(EXIT_FAILURE);
	}
	printf("Server message received: %s\n", buffer);


	const char message[] = "Hello!";

	retval = mq_send(mq, message, sizeof(message), 0);
	if (retval == -1) {

		perror("client: mq_send error");
		exit(EXIT_FAILURE);
	}
	printf("Client message sended\n");

	exit(EXIT_SUCCESS);
}