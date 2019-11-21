#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#define PHIL_NUM 10

typedef struct {
	int id;
	sem_t * locks;
} dataT;

size_t getRandNumber(size_t start, size_t end) {
	return start + rand()%(end-start);
}

void Think(int id) {
	printf("%d Is Thinking.....\n", id);
	usleep(getRandNumber(1000, 10000));
}

void Eat(int id) {
	printf("%d Is Eating.....\n", id);
	usleep(getRandNumber(1000, 10000));
}

void * Philospher(void * data) {
	dataT * d = (dataT *)data;
	while (1) {
		Think(d->id);
		if (d->id < (d->id + 1)%PHIL_NUM) {
			sem_wait(d->locks + d->id);
			sem_wait(d->locks + (d->id + 1)%PHIL_NUM);
		} else {
			sem_wait(d->locks + (d->id + 1)%PHIL_NUM);
			sem_wait(d->locks + d->id);
		}
		Eat(d->id);
		sem_post(d->locks + d->id);
		sem_post(d->locks + (d->id + 1)%PHIL_NUM);
	}
}

int main() {
	dataT * arr = malloc(PHIL_NUM * sizeof(dataT));
	int i = 0;
	sem_t * locks = malloc(PHIL_NUM * sizeof(sem_t));

	for (; i<PHIL_NUM; i++) {
		arr[i].id = i;
		sem_init(locks + i, 0, 1);
		arr[i].locks = locks;
	}
	pthread_t threads[PHIL_NUM];
	for (i = 0; i<PHIL_NUM; i++) {
		pthread_create(threads+i, NULL, Philospher, arr+i);
	}

	pthread_exit(NULL);
}