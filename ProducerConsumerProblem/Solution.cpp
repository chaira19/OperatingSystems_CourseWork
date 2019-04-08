// including libraries

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <random>
#include <unistd.h>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

int BUFFER_SIZE = 10;

// defining linear array of buffer size
int buffer[BUFFER_SIZE];
int index = 0;

// semaphores to check fullness and emptyness of the array
sem_t full,empty;
// variable for mutual exclusion so that producer and consumer cannot work simultaneously
pthread_mutex_t mutex;

// producer function pointer to pass in the thread
void* Producer(void* arg){

	while(true){

		sleep(3);

		pthread_mutex_lock(&mutex);
		sem_wait(&empty);
		
		int item = rand()%100;
		buffer[index++] = item;

		cout<<"Produced item number "<<item<<endl;

		sem_post(&full);
		pthread_mutex_unlock(&mutex);

	}
}

// consumer function pointer to pass in the thread
void* Consumer(void* arg){

	while(true){

		sleep(3);

		pthread_mutex_lock(&mutex);
		sem_wait(&full);
		
		int item = buffer[--index];
		cout<<"Consumed item number "<<item<<endl;

		sem_post(&empty);
		pthread_mutex_unlock(&mutex);

	}
}

int main(){

	cout<<"Please enter the buffer size: ";
	cin>>BUFFER_SIZE;

	pthread_t produce,consume;                    // defining threads

	sem_init(&empty,0,BUFFER_SIZE);               // initializing semaphores
	sem_init(&full,0,0);

	pthread_mutex_init(&mutex,NULL);
	pthread_create(&produce,NULL,Producer,NULL);
	pthread_create(&consume,NULL,Consumer,NULL);
	pthread_exit(NULL);
}
