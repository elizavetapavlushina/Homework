#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <string.h>

#define BUFF_SIZE 255

typedef struct  
{
	long mtype;
	char mtext[BUFF_SIZE];

} msgbuf;

int main() {

	key_t key;

	key = ftok("server", 1);

	if (key == -1) {
		perror("server: ftok error");
		exit(EXIT_FAILURE);
	}

	int msgd;
	msgd = msgget(key, IPC_CREAT | 0666);

	if (msgd == -1) {
		perror("server: msgget error");
		exit(EXIT_FAILURE);
	}

	msgbuf server;
	server.mtype = 1;

	const char message[] = "Hi girl!";

	strcpy(server.mtext, message);
	

	int retval = msgsnd(msgd, &server, sizeof(server), 0);

	if (retval == -1) {
		perror("server: msgsnd error");
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

	msgbuf client;
	retval = msgrcv(msgd, &client, sizeof(client), 0, 0);

	if (retval == -1) {
		perror("server: msgrcv error");
		exit(EXIT_FAILURE);
	}
	printf("Client message received: %s\n", client.mtext);

	struct msqid_ds* msqid;
	retval = msgctl(msgd, IPC_RMID, msqid);

	if (retval == -1) {
		perror("server: msgctl error");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}