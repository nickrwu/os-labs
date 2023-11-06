#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int row1, col1, row2, col2;

void multiply(int m1[row1][col1], int m2[row2][col2]) {
        int product[row1][col2];

        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                product[i][j] = 0;

                for (int k = 0; k < col1; k++) {
                    product[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }

        printf("\nProduct of the matrices:\n");
        for (int i = 0; i < row1; i++) {
            for (int j = 0; j < col2; j++) {
                printf("%d ", product[i][j]);
            }
            printf("\n");
        }
}

int main (int argc, char *argv[]) {
    
    if (argc == 3) {
        row1 = atoi(argv[1]);
        row2 = atoi(argv[2]);

        col1 = row1;
        col2 = row2;
    } else if (argc == 5) {
        row1 = atoi(argv[1]);
        col1 = atoi(argv[2]);

        row2 = atoi(argv[3]);
        col2 = atoi(argv[4]);
    } else {
        fprintf(stderr, "usage: %s <m1 row> <m1 col> <m2 row> <m2 col>\n", argv[0]);
        exit(1);
    }

    if (col1 != row2) {
            printf("Invalid matrix dimensions: \n(1) m x n (2) n x p \n");
            printf("(1) %d x %d (2) %d x %d \n", row1, col1, row2, col2);
            return 1;
    }

    srand(time(NULL));
    

    int matrix1[row1][col1];
    int matrix2[row2][col2];

    // Populate matrix 1
    printf("Matrix 1: \n");
    for (int i=0; i < row1; i++) {
        for (int j=0; j < col1; j++) {
            matrix1[i][j] = rand() % 10;
            printf("%d ", matrix1[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // Populate matrix 2
    printf("Matrix 2: \n");
    for (int i=0; i < row2; i++) {
        for (int j=0; j < col2; j++) {
            matrix2[i][j] = rand() % 10;
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    clock_t begin = clock();

    multiply(matrix1, matrix2);
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // printf("%d: Total time spent: %f\n", i, time_spent);
    printf("Total time spent: %f\n", time_spent);
    sleep(1);
        
    return 0;

    
}