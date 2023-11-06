#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

int BUFFERSIZE;
volatile int * buffer;
int iter;
int count;
int c_count;
int p_index = 0, c_index = 0;

pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_not_empty = PTHREAD_COND_INITIALIZER;

void *produce(void *arg) {
    printf("Producing...\n");
    
    for (int i = 0; i < iter; i++) {
        pthread_mutex_lock(&buffer_lock);
        while (count == BUFFERSIZE) {
            pthread_cond_wait(&buffer_not_full, &buffer_lock);
        }

        buffer[p_index] = i;
        p_index = (p_index + 1) % BUFFERSIZE;
        printf("Produced: %d\n", i);
        count++;
        pthread_cond_signal(&buffer_not_empty);
        pthread_mutex_unlock(&buffer_lock);
    }

    // Signal consumers to exit
    for (int i = 0; i < c_count; i++) {
        pthread_mutex_lock(&buffer_lock);

        while (count == BUFFERSIZE) {
            pthread_cond_wait(&buffer_not_full, &buffer_lock);
        }

        buffer[p_index] = -1;
        p_index = (p_index + 1) % BUFFERSIZE;

        count++;
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_lock);

    }

    return NULL;
}

void *consume(void *arg) {
    int consume = 0;

    int id = *((int *) arg);

    // Keep consuming until -1
    while (consume != -1) {
        pthread_mutex_lock(&buffer_lock);
        
        while (count == 0) {
            pthread_cond_wait(&buffer_not_empty, &buffer_lock);
        }

        consume = buffer[c_index];
        c_index = (c_index + 1) % BUFFERSIZE;
        printf("Consumer %d: %d\n", id, consume);
        count--;
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_lock);
    }

    free(arg);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "usage: %s <buffersize> <loops> <consumers> \n", argv[0]);
        exit(1);
    }

    srand(time(NULL));

    BUFFERSIZE = atoi(argv[1]);
    iter = atoi(argv[2]);
    c_count = atoi(argv[3]);

    pthread_t producer;
    pthread_t consumers[c_count];

    buffer = (int*) malloc(BUFFERSIZE * sizeof(int));
    assert(buffer != NULL);

    int i, j;

    for (i = 0; i < BUFFERSIZE; i++) {
        buffer[i] = 0;
    }

    pthread_create(&producer, NULL, produce, NULL);

    for (i = 0; i < c_count; i++) {
        int *arg = malloc(sizeof(*arg));
        assert(arg != NULL);
        *arg = i + 1;
        pthread_create(&consumers[i], NULL, consume, arg);
    }

    pthread_join(producer, NULL);
 
    for (i = 0; i < c_count; i++) {
        pthread_join(consumers[i], NULL);
    }

    return 0;
}