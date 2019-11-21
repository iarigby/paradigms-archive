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
	if (k % 5 == 0) {
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


#define MAX_NUM 100

typedef struct {
	int counter;
	pthread_cond_t * oddWait;
	pthread_cond_t * evenWait;
	pthread_mutex_t * lock;
} dataT;


void * OddPrinter(void * data) {
	dataT * d = (dataT *)data;

	for (int i=1; i<=100; i+=2) {
		RandomSleep();
		pthread_mutex_lock(d->lock);
		if (d->counter % 2 == 1) {
			pthread_cond_wait(d->evenWait, d->lock);
		}
		d->counter++;
		printf("%d\n", i);
		pthread_mutex_unlock(d->lock);
		RandomSleep();
		pthread_cond_signal(d->oddWait);
	}
	return NULL;
}

void * EvenPrinter(void * data) {
	dataT * d = (dataT *)data;

	for (int i=2; i<=100; i+=2) {
		RandomSleep();
		pthread_mutex_lock(d->lock);
		if (d->counter % 2 == 0) {
			pthread_cond_wait(d->oddWait, d->lock);
		}
		d->counter++;
		printf("%d\n", i);
		pthread_mutex_unlock(d->lock);
		RandomSleep();
		pthread_cond_signal(d->evenWait);
	}
	return NULL;
}

int main() {
	pthread_t * tEven = malloc(sizeof(pthread_t));
	pthread_t * tOdd = malloc(sizeof(pthread_t));
	dataT * data = malloc(sizeof(dataT));
	data->lock = malloc(sizeof(pthread_mutex_t));
	data->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->lock, NULL);
	pthread_mutex_init(data->lock, NULL);
	data->evenWait = malloc(sizeof(pthread_cond_t));
	data->oddWait = malloc(sizeof(pthread_cond_t));
	pthread_cond_init(data->evenWait, NULL);
	pthread_cond_init(data->oddWait, NULL);
	data->counter = 0;


	pthread_create(tEven, NULL, EvenPrinter, data);
	pthread_create(tOdd, NULL, OddPrinter, data);

	pthread_exit(NULL);
}