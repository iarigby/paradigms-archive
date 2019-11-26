#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFF_SIZE 8
#define DATA_TO_READ 10

typedef struct {

} dataT ;

char getRandomChar() {
	return (char)('a' + rand()%26);
}

void * reader(void * data) {
	//
	int i=0;
	for (; i<DATA_TO_READ; i++) {
		//
		printf("reader %d %c\n", i, c);
		//
	}
}

void * writer(void * data) {
	//
	int i=0;
	for (; i<DATA_TO_READ; i++) {
		//
		printf("writer %d %c\n", i, d->buff[i%BUFF_SIZE]);
		//
	}
}


int main() {


	pthread_exit(0);
	return 0;
}
