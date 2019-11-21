#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

struct helper {
	int id;
	int * num;
	sem_t *sem;
};

void * SellTickets(void * data) {
	struct helper *h = (struct helper*)data;
	int *numTickets = h->num;
	int sellerId = h->id;

	while (1) {
		sem_wait(h->sem);//mutex_lock
		if (*numTickets == 0)
			break;
		(*numTickets)--;
		int tmp = *numTickets;
		printf("%d Seller Sold %d \n", sellerId, tmp);
		sem_post(h->sem);//mutex_unlock
		usleep(100);
	}
	sem_post(h->sem);//mutex_unlock
}

int main() {
	int numSellers = 10;
	int numTickets = 40;

	pthread_t t[10];
	struct helper h[10];
	sem_t sem;
	sem_init(&sem, 0, 1);

	int i;
	for (i=0; i<numSellers; i++) {
		h[i].id = i;
		h[i].num = &numTickets;
		h[i].sem = &sem;
		pthread_create(t+i, NULL, SellTickets, h+i);
	}

	pthread_exit(NULL);
}






