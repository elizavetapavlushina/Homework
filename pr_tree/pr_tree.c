#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {

	pid_t child_pid;
	pid_t child_pid2;
	pid_t child_pid3;
	pid_t child_pid4;
	pid_t child_pid5;
	int status;
	int status2;
	int status3;
	int status4;
	int status5;

	child_pid = fork(); // child 1 from parent

	if (child_pid == -1) {
		perror("Fork error:");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0){

		printf("child pid 1 = %d, ", getpid());
		printf("ppid = %d\n",getppid());

		child_pid2 = fork(); //child 2 from child 1

		if (child_pid2 == -1) {

			perror("Fork error:");
			exit(EXIT_FAILURE);
		}
		
		if (child_pid2 == 0) {

			printf("child pid 3 = %d, ", getpid());
			printf("ppid = %d\n",getppid());

			sleep(1);
			exit(EXIT_SUCCESS);
		} 
		else {

			child_pid3 = fork(); //child 3 from child 1

			if (child_pid3 == -1) {

				perror("Fork error:");
				exit(EXIT_FAILURE);
			}

			if (child_pid3 == 0) {

				printf("child pid 4 = %d, ", getpid());
				printf("ppid = %d\n",getppid());

				sleep(1);
				exit(EXIT_SUCCESS);
			}
		}
		waitpid(child_pid2, &status2, 0);
		waitpid(child_pid3, &status3, 0);
		printf("status 3 = %d\n", WEXITSTATUS(status2));
		printf("status 4 = %d\n", WEXITSTATUS(status3));
		exit(EXIT_SUCCESS);

	}

	else {

		child_pid4 = fork(); //child 4 from parent

		if (child_pid4 == -1) {

			perror("Fork error:");
			exit(EXIT_FAILURE);
		}

		if (child_pid4 == 0) {

			printf("child pid 2 = %d, ", getpid());
			printf("ppid = %d\n",getppid());

			child_pid5 = fork(); //child 5 from child 4

			if (child_pid5 == -1) {

				perror("Fork error:");
				exit(EXIT_FAILURE);
			}

			if (child_pid5 == 0) {

				printf("child pid 5 = %d, ", getpid());
				printf("ppid = %d\n",getppid());

				sleep(1);
				exit(EXIT_SUCCESS);
			}

			waitpid(child_pid5, &status5, 0);
			printf("status 5 = %d\n", WEXITSTATUS(status5));
			exit(EXIT_SUCCESS);
		}

		
	}
	
	waitpid(child_pid, &status, 0);
	printf("status 1 = %d\n", WEXITSTATUS(status));
	waitpid(child_pid4, &status4, 0);
	printf("status 2 = %d\n", WEXITSTATUS(status4));
	exit(EXIT_SUCCESS);

}
