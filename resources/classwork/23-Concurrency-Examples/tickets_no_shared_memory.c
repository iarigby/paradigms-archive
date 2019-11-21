#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


/*
int pthread_create( 	pthread_t * thread, const pthread_attr_t * attr, 
						void * ( * start_routine)(void * ), void * arg);

void pthread_exit(void *value_ptr); 

int sem_init(sem_t *sem, int pshared, unsigned int value); 
int sem_destroy(sem_t *sem); 
int sem_post(sem_t *sem); 
int sem_wait(sem_t *sem);
*/


#define NUM_TICKETS 150
#define NUM_SELLERS 10

typedef struct {
	int id;
	int ticketsNum;
} seller_t;

void RandomSleep() {
	int k = rand();
	if (k % 3 == 0) {
		usleep(100);
	}
}

void * SellTickets(void * data) {
	seller_t * s = (seller_t *)data;
	while (s->ticketsNum > 0) {
		s->ticketsNum--;
		printf("seller: %d, ticket: %d\n", s->id, s->ticketsNum);
		RandomSleep();
	}

	return NULL;
}


int main() {
	srand(time(NULL));
	pthread_t * threads[NUM_SELLERS];
	for (int i=0; i<NUM_SELLERS; i++) {
		seller_t *seller = malloc(sizeof(seller_t));
		seller->id = i;
		seller->ticketsNum = NUM_TICKETS / NUM_SELLERS;
		threads[i] = malloc(sizeof(pthread_t));
		printf("create seller thread %d\n", i);
		pthread_create(threads[i], NULL, SellTickets, seller);
	}

	pthread_exit(NULL);
}