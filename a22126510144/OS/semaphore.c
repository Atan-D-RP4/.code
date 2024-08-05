// Experiment 5: Solving The Dining Philosopher Problem Using Semaphores
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[N];
int phil[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void test(int phnum)
{
	if (state[phnum] == HUNGRY
			&& state[LEFT] != EATING
			&& state[RIGHT] != EATING) {
		// state that eating
		state[phnum] = EATING;

		sleep(2);

		printf("Philosopher %d takes chopstick %d and %d\n",
				phnum + 1, LEFT + 1, phnum + 1);

		printf("Philosopher %d is eating\n", phnum + 1);

		// sem_post(&S[phnum]) has no effect
		// during takechopstick
		// used to wake up hungry philosophers
		// during putchopstick
		sem_post(&S[phnum]);
	}
}

// take up chopsticks
void take_chopstick(int phnum)
{

	sem_wait(&mutex);

	// state that hungry
	state[phnum] = HUNGRY;

	printf("Philosopher %d is Hungry\n", phnum + 1);

	// eat if neighbours are not eating
	test(phnum);

	sem_post(&mutex);

	// if unable to eat wait to be signalled
	sem_wait(&S[phnum]);

	sleep(1);
}

// drop chopsticks
void drop_chopstick(int phnum)
{

	sem_wait(&mutex);

	// state that thinking
	state[phnum] = THINKING;

	printf("Philosopher %d drops chopstick %d and %d \n",
			phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		take_chopstick(*i);

		sleep(1);

		drop_chopstick(*i);
	}
}

int main()
{

	int i;
	pthread_t thread_id[N];

	// initialize the semaphores
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		// create philosopher processes
		pthread_create(&thread_id[i], NULL,
				philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
}

// Output:
/*
 * Philosopher 1 is thinking
 * Philosopher 2 is thinking
 * Philosopher 3 is thinking
 * Philosopher 4 is thinking
 * Philosopher 5 is thinking
 * Philosopher 1 is Hungry
 * Philosopher 2 is Hungry
 * Philosopher 3 is Hungry
 * Philosopher 5 is Hungry
 * Philosopher 4 is Hungry
 * Philosopher 4 takes chopstick 3 and 4
 * Philosopher 4 is eating
 * Philosopher 4 drops chopstick 3 and 4
 * Philosopher 4 is thinking
 * Philosopher 3 takes chopstick 2 and 3
 * Philosopher 3 is eating
 * Philosopher 5 takes chopstick 4 and 5
 * Philosopher 5 is eating
 * Philosopher 3 drops chopstick 2 and 3
 * Philosopher 3 is thinking
 * Philosopher 2 takes chopstick 1 and 2
 * Philosopher 2 is eating
 * Philosopher 5 drops chopstick 4 and 5
 * Philosopher 5 is thinking
 * Philosopher 4 is Hungry
 * Philosopher 4 takes chopstick 3 and 4
 * Philosopher 4 is eating
 * Philosopher 5 is Hungry
 * Philosopher 3 is Hungry
 * Philosopher 2 drops chopstick 1 and 2
 * Philosopher 2 is thinking
 * Philosopher 1 takes chopstick 5 and 1
 * Philosopher 1 is eating
 * Philosopher 4 drops chopstick 3 and 4
 * Philosopher 4 is thinking
 * Philosopher 3 takes chopstick 2 and 3
 * Philosopher 3 is eating
 * Philosopher 1 drops chopstick 5 and 1
 * Philosopher 1 is thinking
 */
