#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int main() {

	printf("Second program started\n");
	
	while (1) {

		if ( kill(getppid(), SIGUSR1) == -1 ){

			perror("second program: kill erorr");
			exit(EXIT_FAILURE);
		}
		printf("Second program: sent SIGUSER1 to first program\n");

		sleep(1);
	}
	
}