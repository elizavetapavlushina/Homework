#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFF_SIZE 10

int main () {

	int pipes_fd[2];
	pipe(pipes_fd);

	pid_t cpid;
	pid_t status;
	cpid = fork();

	if (cpid == 0) {
		char message[BUFF_SIZE];

		if(close(pipes_fd[1]) == -1) {
			perror("close fd 1 error:");
			exit(EXIT_FAILURE);
		}

		int size;

		size = read(pipes_fd[0], &message, BUFF_SIZE);
		if (size == -1) {
			perror("read fd 0 error:");
			exit(EXIT_FAILURE);
		}

		size = write(STDOUT_FILENO, &message, BUFF_SIZE);
		if (size == -1) {
			perror("write fd 1 error:");
			exit(EXIT_FAILURE);
		}
		printf("The message recieved\n");

		if(close(pipes_fd[0]) == -1) {
			perror("close fd 0 error:");
			exit(EXIT_FAILURE);
		}

	} else {

		if(close(pipes_fd[0]) == -1) {
			perror("close fd 0 error:");
			exit(EXIT_FAILURE);
		}

		const char buffer[] = "Hello";
		printf("The message sended\n");

		if (write(pipes_fd[1], &buffer, BUFF_SIZE) == -1) {
			perror("write fd 1 error:");
			exit(EXIT_FAILURE);
		}

		if(close(pipes_fd[1]) == -1) {
			perror("close fd 1 error:");
			exit(EXIT_FAILURE);
		}

		wait(&status);
		exit(EXIT_SUCCESS);
	}
}