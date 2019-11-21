#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>

#define FILE_NUM 10

typedef struct {
	char * fileName;
	void ** file;
	int * totalBytesDownloaded;
	sem_t * lock;
	sem_t * notify;
} dataT;

char * intToString(int k) {
	char * res = strdup("               ");
	sprintf(res, "%d", k);
	return res;
}

size_t getRandNumber(size_t start, size_t end) {
	return start + rand()%(end-start);
}

int DownloadSingleFile(char * name, void ** whereToCopy) {
	printf("Downloading file %s\n", name);
	usleep(getRandNumber(100000, 2000000));//sleep some time
	int bytes = getRandNumber(1000, 2000);
	printf("Downloading file %s %d bytes\n", name, bytes);
	return bytes;//return random size(Bytes)
}


void * DownloadHelper(void * data) {
	dataT * d = (dataT *)data;
	int bytes = DownloadSingleFile(d->fileName, d->file);
	sem_wait(d->lock);
	*(d->totalBytesDownloaded) = *(d->totalBytesDownloaded) + bytes;
	sem_post(d->lock);

	//mutxe_lock
	//cond_signal
	//mutex_unlock
	sem_post(d->notify);
}


int DownloadAllFiles() {
	int totalBytesDownloaded = 0;
	pthread_t threads[FILE_NUM];

	sem_t lock;
	sem_init(&lock, 0, 1);
	sem_t notify;
	sem_init(&notify, 0, 0);
	dataT arr[FILE_NUM];
	int i=0;
	for (; i<FILE_NUM; i++) {
		arr[i].totalBytesDownloaded = &totalBytesDownloaded;
		arr[i].fileName = intToString(i);
		arr[i].lock = &lock;
		arr[i].notify = &notify;
		pthread_create(threads+i, NULL, DownloadHelper, arr+i);
	}

	
	//cond_wait
	i=0;
	for (; i<FILE_NUM; i++) {
		sem_wait(&notify);//cond_wait
	}


	printf("Total bytes downloaded %d\n", totalBytesDownloaded);
	return totalBytesDownloaded;
}

int main() {
	DownloadAllFiles();

	pthread_exit(NULL);
}