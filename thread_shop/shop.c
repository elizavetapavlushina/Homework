#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SHOPS_COUNT 5
#define REQUIREMENT 10000

pthread_t mutexes[SHOPS_COUNT];

int shops[] = {1000, 1000, 1000, 1000, 1000};
int cnt_ready_shoppers = 0;

void *loader() {

	while (cnt_ready_shoppers != SHOPS_COUNT) {
		
		for (int i = 0; i < SHOPS_COUNT; i++) {
	
			if (pthread_mutex_trylock(&mutexes[i]) != 0) 
				continue;

			shops[i] += 5000;
			printf("+5000 in %d shop\n", i);

			if (pthread_mutex_unlock(&mutexes[i]) != 0) {

				perror("loader mutex unlock error");
				exit(EXIT_FAILURE);
			}

			sleep(2);
			break;		
			 
		}
	}

	return NULL;
}

void *shopper(void *arg) {
	
	int shopper_number = *(int *)arg;
	int cur_req = 0;

	while (cur_req < REQUIREMENT) {

		for (int i = 0; i < SHOPS_COUNT; i++) {

			if (shops[i] <= 0)
				continue; 

			if (pthread_mutex_trylock(&mutexes[i]) != 0)
				continue;

			cur_req += shops[i];
			shops[i] = 0;

			printf("\nAll received from %d shop by %d shopper\n",
														i, shopper_number);
			printf("Current requirement of %d shopper = %d\n",
									 			shopper_number, cur_req);

			if (pthread_mutex_unlock(&mutexes[i]) != 0) {

				perror("shopper mutex unlock error");
				exit(EXIT_FAILURE);
			}

			sleep(1);
			break;			
			 
		}
	}

	cnt_ready_shoppers++;

	return NULL;
}


int main() {

	for (int i = 0; i < SHOPS_COUNT; i++) {

		if (pthread_mutex_init(&mutexes[i], NULL) != 0) {

			perror("mutex init error");
			exit(EXIT_FAILURE);
		}
	}
	
	int shoppers[SHOPS_COUNT] = {0, 1, 2, 3, 4};
	pthread_t thread_shop[SHOPS_COUNT];

	int retval;

	for (int i = 0; i < SHOPS_COUNT; i++) {

		retval = pthread_create(&thread_shop[i], NULL, shopper, &shoppers[i]);

		if (retval != 0) {

			perror("shop pthread create error");
			exit(EXIT_FAILURE);
		}
	}

	pthread_t thread_load;
	retval = pthread_create(&thread_load, NULL, loader, NULL);

	if (retval != 0) {

		perror("loader pthread create error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < SHOPS_COUNT; i++) {

		if (pthread_join(thread_shop[i], NULL) != 0) {

			perror("shop pthread join error");
			exit(EXIT_FAILURE);
		}
	}

	if (pthread_join(thread_load, NULL) != 0) {

		perror("loader pthread join error");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < SHOPS_COUNT; i++) {

		if (pthread_mutex_destroy(&mutexes[i]) != 0) {

			perror("mutex destroy error");
			exit(EXIT_FAILURE);
		}	
	}

	exit(EXIT_SUCCESS);
}