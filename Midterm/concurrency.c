#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct shared_data {
    int counter;
    pthread_mutex_t mutex;
} SharedData;

int threads;

void *access_shared(void *arg) {
    SharedData* data = (SharedData*) arg;

    for (int i = 0; i < 5; i++) {
        // Acquire the lock
        pthread_mutex_lock(&data->mutex);

        data->counter++;

        // Release the locks
        pthread_mutex_unlock(&data->mutex);
    }
   

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <threads> <loops>\n", argv[0]);
        exit(1);
    }

    threads = atoi(argv[1]);
    pthread_t tid[threads];

    // Initialize share data structure
    SharedData shared_data;

    shared_data.counter = 0;
    pthread_mutex_init(&shared_data.mutex, NULL);

    // Create threads
    printf("NOTE: Each thread increments the counter by 5\n");
    for (int i = 0; i < threads; i++) {
        printf("Creating thread %d\n", i);
        pthread_create(&tid[i], NULL, access_shared, (void *) &shared_data);
    }

    // Join threads
    for (int i = 0; i < threads; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&shared_data.mutex);

    printf("Counter: %d\n", shared_data.counter);

    return 0;
}
