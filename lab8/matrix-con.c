#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 3
#define NUM_THREADS 4

int step = 0;

int matrix1[SIZE][SIZE];
int matrix2[SIZE][SIZE];
int result[SIZE][SIZE];

void *multiply(void *arg) {
    int i = step++;

    for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < SIZE; k++) {
            result[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }

    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    srand(time(NULL));

    // Populate matrix 1
    // printf("Matrix 1: \n");
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            matrix1[i][j] = rand() % 10;
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Populate matrix 2
    // printf("Matrix 2: \n");
    for (int i=0; i < SIZE; i++) {
        for (int j=0; j < SIZE; j++) {
            matrix2[i][j] = rand() % 10;
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    clock_t begin = clock();

    // Create threads
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multiply, (void*)(p));
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // Print result matrix
    printf("\nProduct of the matrices:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("n=%d: Total time spent: %f\n", SIZE, time_spent);
    sleep(1);
        
    return 0;

    
}