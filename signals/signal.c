#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>


int main() {

	sigset_t set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);

	sigprocmask(SIG_BLOCK, &set, NULL);

	int sig;
	pid_t cpid;
	printf("First program started\n");

	cpid = fork();

	if (cpid == 0) {

		execl("client", "client", NULL);
		exit(EXIT_SUCCESS);

	} else {

		while (1) {

			sigwait(&set, &sig);

			if (sig == SIGUSR1) {

				printf("First program: signal SIGUSR1 received\n");
			}
		}
	}
}