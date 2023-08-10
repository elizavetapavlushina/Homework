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
	
	int retval = msgrcv(msgd, &server, sizeof(server), 0, 0);
	if (retval == -1) {

		perror("client: msgrcv error");
		exit(EXIT_FAILURE);
	}
	printf("Server message received: %s\n", server.mtext);

	msgbuf client;
	client.mtype = 1;

	const char message[] = "Hello!";
	strcpy(client.mtext, message);

	retval = msgsnd(msgd, &client, sizeof(client), 0);
	if (retval == -1) {

		perror("client: msgsnd error");
		exit(EXIT_FAILURE);
	}
	printf("Client message sended\n");

	exit(EXIT_SUCCESS);
}