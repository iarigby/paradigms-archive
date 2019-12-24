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


#define NUM_RACERS 10
#define DISTANCE 100

typedef struct {
	int id;
	int * counter;
	sem_t * lock;
} racer_t;



void * RunRace(void * data) {
	racer_t * racer = (racer_t *)data;
	
	return NULL;
}

int main() {
	int * counter = malloc(sizeof(int));
	* counter = 0;
	sem_t * lock = malloc(sizeof(sem_t));
	sem_init(lock, 0, 1);
	for (int i=0; i<NUM_RACERS; i++) {
		
	}

	pthread_exit(NULL);
}

sudo apt-get update