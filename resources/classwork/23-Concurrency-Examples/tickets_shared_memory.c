#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void RandomSleep() {
	int k = rand();
	if (k % 3 == 0) {
		usleep(100);
	}
}
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
	int * ticketsNum;
	sem_t * lock;
} seller_t;




void * SellTickets(void * data) {
	seller_t * s = (seller_t *)data;
	while (1) {
		sem_wait(s->lock);
		if (*s->ticketsNum == 0) {
			break;
		}
		*s->ticketsNum--;
		sem_post(s->lock);
		printf("seller: %d, ticket: %d\n", s->id, *s->ticketsNum);
	}
	sem_post(s->lock);
	return NULL;
}

int main() {
	pthread_t * threads[NUM_SELLERS];
	int * numTickets = malloc(sizeof(int));
	*numTickets = NUM_TICKETS;
	sem_t * lock = malloc(sizeof(sem_t));
	sem_init(lock, 0, 1);

	for (int i=0; i<NUM_SELLERS; i++) {
		seller_t *seller = malloc(sizeof(seller_t));
		seller->id = i;
		seller->ticketsNum = numTickets;
		seller->lock = lock;
		threads[i] = malloc(sizeof(pthread_t));
		printf("create seller thread %d\n", i);
		pthread_create(threads[i], NULL, SellTickets, seller);
	}

	pthread_exit(NULL);
}