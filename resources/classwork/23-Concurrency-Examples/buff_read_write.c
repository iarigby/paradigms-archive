#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFF_SIZE 8
#define DATA_TO_READ 32

typedef struct {
	char buff[BUFF_SIZE];
	sem_t readLock;
	sem_t writeLock;

} dataT ;

char getRandomChar() {
	return (char)('a' + rand()%26);
}

void * reader(void * data) {
	dataT * d = (dataT *) data;
	int i=0;
	for (; i<DATA_TO_READ; i++) {
		sem_wait(&d->readLock);
		char c = d->buff[i%BUFF_SIZE];
		printf("reader %d %c\n", i, c);
		sem_post(&d->writeLock);
	}
}

void * writer(void * data) {
	dataT * d = (dataT *) data;
	int i=0;
	for (; i<DATA_TO_READ; i++) {
		sem_wait(&d->writeLock);
		d->buff[i%BUFF_SIZE] = getRandomChar();
		printf("writer %d %c\n", i, d->buff[i%BUFF_SIZE]);
		sem_post(&d->readLock);
	}
}


int main() {
	pthread_t readerThread;
	pthread_t writerThread;
	dataT * data = malloc(sizeof(dataT));
	sem_init(&data->readLock, 0, 0);
	sem_init(&data->writeLock, 0, BUFF_SIZE);

	pthread_create(&readerThread, NULL, reader, data);
	pthread_create(&writerThread, NULL, writer, data);

	pthread_exit(0);
	return 0;
}