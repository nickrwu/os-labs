#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

int BUFFERSIZE;
volatile int * buffer;
int iter;
int count;
int p_index = 0, c_index = 0;

pthread_t producer, consumer;

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

    pthread_mutex_lock(&buffer_lock);

    while (count == 0) {
        pthread_cond_wait(&buffer_not_full, &buffer_lock);
    }

    buffer[p_index] = -1;
    p_index = (p_index + 1) % BUFFERSIZE;
    count++;
    pthread_cond_signal(&buffer_not_full);
    pthread_mutex_unlock(&buffer_lock);

    return NULL;
}

void *consume(void *arg) {
    printf("Consuming...\n");
    int consume = 0;

    while (consume != -1) {
        pthread_mutex_lock(&buffer_lock);
        while (count == 0) {
            pthread_cond_wait(&buffer_not_empty, &buffer_lock);
        }

        consume = buffer[c_index];
        c_index = (c_index + 1) % BUFFERSIZE;
        printf("Consumed: %d\n", consume);
        count--;
        pthread_cond_signal(&buffer_not_full);
        pthread_mutex_unlock(&buffer_lock);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s <buffersize> <iterations>\n", argv[0]);
        exit(1);
    }

    BUFFERSIZE = atoi(argv[1]);
    iter = atoi(argv[2]);

    buffer = (int*) malloc(BUFFERSIZE * sizeof(int));
    assert(buffer != NULL);

    for (int i = 0; i < BUFFERSIZE; i++) {
        buffer[i] = 0;
    }

    pthread_create(&producer, NULL, produce, NULL);
    pthread_create(&consumer, NULL, consume, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}