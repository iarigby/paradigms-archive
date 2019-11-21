/**
Manager
Clerk		[10-40]
Customer	[1-10] [1-4]
Cashier
**/

#define NUM_CUSTOMERS 10
#define NUM_MAX_CONES 4

typedef struct {
	int totalCones;
	sem_t requested;//0
	sem_t finished;//0
	sem_t lock;//1
	bool passed;
	lineT *line;
} inspectionT;

typedef struct {
	sem_t requested;//0
	int lineNumber;//0
	sem_t * lock;//1
	sem_t * line[NUM_CUSTOMERS];

} lineT;

void InitVariables(inspectionT * inspection, lineT * line);
void InitThreads(inspectionT * inspection, lineT * line);
void MakeCone();
void Browse(int customerId);
void Checkout(int customerId);
void FreeAll();

void * Manager(void * data) {
	inspectionT * d = (inspectionT *)data;
	int passedCones = 0;
	while (passedCones < d->totalCones) {
		sem_wait(&(d->requested));
		d->passed = Inspect();
		sem_post(&(d->finished))
		if (d->passed) {
			passedCones++
		}
	}

}

void * Clerk(void * data) {
	inspectionT * d = (inspectionT *)data;
	bool passed = false;
	while (!passed) {
		MakeCone();
		sem_wait(&(d->lock));
		sem_post(&(d->requested));
		sem_wait(&(d->finished));
		passed = d->passed;
		sem_post(&(d->lock));
	}
	sem_t * finished = *(sem_t **)((char *)d + sizeof(inspectionT))
	sem_post(finished);
}

void * Customer(void * data) {
	int * arr = (int *) data;
	Browse();
	int id = arr[0];
	const int n = arr[1];
	sem_t finished;
	sem_init(&finished, 0, 0);

	data = realloc(data, 2*sizeof(int) + 2*sizeof(void*));
	*(void **)((char *)data + 2*sizeof(int) + sizeof(void*)) = &finished;

	thread_t threads[n];
	for (int i=0; i<n; i++) {
		 thread_init(threads + i, NULL, Clerk, arr + 2);
	}

	for (int i=0; i<n; i++) {
		sem_wait(&finished);
	}

	inspectionT * d = (inspectionT)(arr + 2);
	sem_wait(d->line->lock);
	int lineNumber = d->line>lineNumber++;
	d->line->line[lineNumber] = &finished;
	sem_post(d->line->lock);

	sem_post(&(d->line->requested));
	sem_wait(&finished);
}

void * Cashier(void * data) {
	lineT * d = (lineT *)data;
	for (int i=0; i<NUM_CUSTOMERS; i++) {
		sem_wait(&(d->requested));
		Serve();
		sem_post(d->line[i]);
	}
}

pthread_t customer_threads[NUM_CUSTOMERS];
pthread_t manager_thread;
pthread_t cashier_thread;

int main() {
	int totalCones = 0;
	inspectionT inspection;
	lineT line;
	InitVariables(&inspection, &line);
	InitThreads(&inspection, &line);		
	RunAllThreads();
	//wait for all threads
	FreeAll();
}

void InitVariables(inspectionT * inspection, lineT * line) {
	sem_init(&(inspection->requested), 0, 0);
	sem_init(&(inspection->finished), 0, 0);
	sem_init(&(inspection->lock), 0, 1);
	inspection->passed = false;

	sem_init(&(line->requested), 0, 0);
	sem_init(&(line->lock), 0, 1);
	for (int i=0; i<NUM_CUSTOMERS; i++) {
		sem_init(&(line->customers[i]), 0, 0);
	}
	line->number = 0;
}

void InitThreads(inspectionT * inspection, lineT * line) {
	int totalCones = 0;
	inspection->line = line;
	//run customer threads
	for (int i=0; i<NUM_CUSTOMERS; i++) {
		int * data = malloc(2*sizeof(int) + sizeof(void *));
		data[0] = i;
		data[1] = rand() % NUM_MAX_CONES;
		*(void **)(data + 2) = inspection;
		pthread_create(customer_threads+i, NULL, Customer, data);
		inspection->totalCones += data[1];
	}

	//run manager thread
	pthread_create(&manager_threads, NULL, Manager, inspection);

	//run chashier thread
	pthread_create(&cashier_threads, NULL, Cashier, line);
}

void MakeCone() {
	//TODO: just sleep some time
}

void Browse() {
	//TODO: just sleep some time	
}

void Checkout() {
	//TODO: just sleep some time	
}

void FreeAll() {
	//TODO:	
}