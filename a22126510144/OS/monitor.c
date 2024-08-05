// Experiment 6: Solving Producer-Consumer Problem using a Monitor
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 3

// Buffer to hold the produced items
int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer

// Monitor structure
typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond_producer;
	pthread_cond_t cond_consumer;
} Monitor;

Monitor monitor = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_COND_INITIALIZER,
	PTHREAD_COND_INITIALIZER
};

// Function prototypes
void* producer(void* param);
void* consumer(void* param);
void* counter(void* param);
void produce(int item);
int consume();

// Main function
int main() {
	pthread_t tid_counter;
	pthread_create(&tid_counter, NULL, counter, NULL);

	pthread_t tid_producer[2], tid_consumer[2];

	// Create producer and consumer threads
	for (int i = 0; i < 2; i++) {
		pthread_create(&tid_producer[i], NULL, producer, NULL);
		pthread_create(&tid_consumer[i], NULL, consumer, NULL);
	}

	// Wait for all threads to finish
	for (int i = 0; i < 2; i++) {
		pthread_join(tid_producer[i], NULL);
		pthread_join(tid_consumer[i], NULL);
		pthread_join(tid_counter, NULL);
	}

	return 0;
}

// Producer thread function
void* producer(void* param) {
	while (1) {
		int item = rand() % 100;  // Produce an item
		produce(item);
		sleep(1);  // Simulate time taken to produce an item
	}
}

// Consumer thread function
void* consumer(void* param) {
	while (1) {
		int item = consume();
		printf("Consumed: %d\n", item);
		sleep(2);  // Simulate time taken to consume an item
	}
}

void* counter(void* param) {
	while (1) {
		printf("Buffer: ");
		for (int i = 0; i < count; i++) {
			printf("%d ", buffer[i]);
		}
		printf("\n");
		sleep(1);
	}
}

// Function to produce an item and add it to the buffer
void produce(int item) {
	pthread_mutex_lock(&monitor.mutex);

	// Wait if the buffer is full
	while (count == BUFFER_SIZE) {
		pthread_cond_wait(&monitor.cond_producer, &monitor.mutex);
	}

	// Add the item to the buffer
	buffer[count++] = item;
	printf("Produced: %d\n", item);

	// Signal the consumer that an item is available
	pthread_cond_signal(&monitor.cond_consumer);

	pthread_mutex_unlock(&monitor.mutex);
}

// Function to consume an item from the buffer
int consume() {
	pthread_mutex_lock(&monitor.mutex);

	// Wait if the buffer is empty
	while (count == 0) {
		pthread_cond_wait(&monitor.cond_consumer, &monitor.mutex);
	}

	// Remove the item from the buffer
	int item = buffer[--count];

	// Signal the producer that there is space available
	pthread_cond_signal(&monitor.cond_producer);

	pthread_mutex_unlock(&monitor.mutex);

	return item;
}

/* Output:
 * Buffer: 83
 * Produced: 83
 * Consumed: 83
 * Produced: 86
 * Consumed: 86
 * Buffer:
 * Produced: 77
 * Produced: 15
 * Consumed: 15
 * Buffer:
 * Produced: 93
 * Produced: 35
 * Consumed: 77
 * Buffer: 93 35
 * Produced: 86
 * Consumed: 86
 * Produced: 92
 * Buffer: 93 35 92
 * Consumed: 92
 * Produced: 49
 * Buffer: 93 35 49
 * Consumed: 49
 * Produced: 21
 * Consumed: 21
 * Produced: 62
 * Buffer: 93 35 62
 * Buffer: 93 35 62
 */
