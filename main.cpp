#include <mutex>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

std::mutex m;


using namespace std;

#define NUM_THREADS 5

int counting = 0;

void* wait(void *t) {
	int i;
	long tid;
	tid = (long)t;

	sleep(1);
	m.lock();
	counting++;
	cout << "count: " << counting << endl;
	m.unlock();
	pthread_exit(NULL);
}

int main () {
	int rc;
	int i;
	pthread_t threads[NUM_THREADS];
	pthread_attr_t attr;
	void *status;

	// Initialize and set thread joinable
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	for( i = 0; i < NUM_THREADS; i++ ) {
		m.lock();
		cout << "main() : creating thread, " << i << endl;
		m.unlock();
		rc = pthread_create(&threads[i], NULL, wait, (void *)i );

		if (rc) {
			m.lock();
			cout << "Error:unable to create thread," << rc << endl;
			m.unlock();
			exit(-1);
		}
	}

	// free attribute and wait for the other threads
	pthread_attr_destroy(&attr);
	for( i = 0; i < NUM_THREADS; i++ ) {
		rc = pthread_join(threads[i], &status);
		if (rc) {
			cout << "Error:unable to join," << rc << endl;
			exit(-1);
		}
		m.lock();
		cout << "Main: completed thread id :" << i ;
		cout << "  exiting with status :" << status << endl;
		m.unlock();
	}

	cout << "Main: program exiting." << endl;
	pthread_exit(NULL);
}
