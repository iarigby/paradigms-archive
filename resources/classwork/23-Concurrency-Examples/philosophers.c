#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#define PHIL_NUM 10

typedef struct {
//
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

}

int main() {


	pthread_exit(NULL);
}
