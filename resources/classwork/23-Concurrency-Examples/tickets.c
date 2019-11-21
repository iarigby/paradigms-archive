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

	int sellerId = h->id;
	// don't need esmaphore because the addressdoesn't change, only value
	int *numTickets = h->num;
	int ticketsSold = 0;
	while (1) {
		sem_wait(h->sem);//mutex_lock
		if (*numTickets == 0) {
			sem_post(h->sem);//mutex_unlock
			break;
		}
		(*numTickets)--;
		ticketsSold++;
		printf("%d Seller Sold %d \n", sellerId, *numTickets);
		sem_post(h->sem);//mutex_unlock
		// try without sleep
		usleep(100);
	}
	printf("%d noticed all tickets sold! (I sold %d myself) \n",
		   sellerId, ticketsSold);
}

int main() {
	int numSellers = 10;
	// try 40000 without sleep
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
	printf("here\n");
	pthread_exit(NULL);
}






