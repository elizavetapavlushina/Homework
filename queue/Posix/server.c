#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>

#define Q_NAME "/queue"
#define MAX_MSG 5
#define BUFF_SIZE 255

int main() {

	struct mq_attr mqueue =
	{
		.mq_maxmsg = MAX_MSG,
		.mq_msgsize = BUFF_SIZE,
	};

	mqd_t mq;

	mq = mq_open(Q_NAME, O_CREAT | O_RDWR | O_EXCL, 0777, &mqueue);

	if (mq == -1) {
		perror("server: mq_open error");
		exit(EXIT_FAILURE);
	}

	const char message[] = "Hi girl!";

	int retval = mq_send(mq, message, sizeof(message), 0);

	if (retval == -1) {
		perror("server: mq_send error");
		exit(EXIT_FAILURE);
	}
	printf("Server message sended\n");

	pid_t cpid;
	pid_t status;

	cpid = fork();

	if (cpid == 0) {

		if(execl("client", "client", NULL) == -1) {
			perror("server: execl error");
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);

	} else {

		wait(&status);
	}

	char buffer[BUFF_SIZE];
	retval = mq_receive(mq, buffer, BUFF_SIZE, 0);

	if (retval == -1) {
		perror("server: mq_receive error");
		exit(EXIT_FAILURE);
	}
	printf("Client message received: %s\n", buffer);

	if(mq_unlink(Q_NAME) == -1) {
		perror("server: mq_unlink error");
		exit(EXIT_FAILURE);
	}

	if(mq_close(mq) == -1) {
		perror("server: mq_close error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}