#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS]; // Mutex for forks
pthread_t philosophers[NUM_PHILOSOPHERS]; // Philosopher threads
int philosopher_ids[NUM_PHILOSOPHERS]; // IDs of philosophers

void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    sleep(rand() % 3 + 1); // Random thinking time
}

void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(rand() % 2 + 1); // Random eating time
}

void* philosopher(void* arg) {
    int id = *(int*)arg;

    while (1) {
        think(id);

        // Pick up left fork
        pthread_mutex_lock(&forks[id]);
        printf("Philosopher %d picked up fork %d (left).\n", id, id);

        // Pick up right fork
        pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up fork %d (right).\n", id, (id + 1) % NUM_PHILOSOPHERS);

        eat(id);

        // Put down right fork
        pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down fork %d (right).\n", id, (id + 1) % NUM_PHILOSOPHERS);

        // Put down left fork
        pthread_mutex_unlock(&forks[id]);
        printf("Philosopher %d put down fork %d (left).\n", id, id);
    }
    return NULL;
}

int main() {
    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        philosopher_ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Wait for philosopher threads to finish (infinite loop in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
s
