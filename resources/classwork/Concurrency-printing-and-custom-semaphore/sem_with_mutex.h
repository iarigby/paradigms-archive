
typedef struct {
	int counter;
	pthread_cond_t * wait;
	pthread_mutex_t * lock;
} semT;

void semInit(semT * s, int counter) {
	s->counter = counter;
	s->wait = malloc(sizeof(pthread_cond_t));
	s->lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(s->lock, NULL);
	pthread_cond_init(s->wait, NULL);
}

void semPost(semT * s) {
	pthread_mutex_lock(s->lock);
	s->counter++;
	pthread_cond_signal(s->wait);	
	pthread_mutex_unlock(s->lock);
}

void semWait(semT * s) {
	pthread_mutex_lock(s->lock);
	// while instead of if because
	// depends on scheduler implementation
	// look up spurious wakeup
	while (s->counter == 0) {
		pthread_cond_wait(s->wait, s->lock);
	} 
	// can assert errno
	s->counter--;
	pthread_mutex_unlock(s->lock);
}
