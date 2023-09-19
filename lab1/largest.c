#include <stdio.h>
#include <stdlib.h>

void findLargest(int* array, int size) {
    int* max = array;

    for (int i = 0; i < size; i++) {
        if (array[i] > *max) {
            max = &array[i];
        }
    }

    printf("Largest: %d\n", *max);
}

int main() {
    int size;
    int* arr;
    int done = 1;
    
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);
    
    arr = (int*) malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Memory not allocated");
        exit(0);
    }

    for (int i = 0; i < size; i++) {
        int element;
        printf("Add an array element: ");
        scanf("%d", &element);

        if (element == 0) {
            printf("NULL element detected. Exiting...\n");
            exit(0);
        } else {
            *(arr + i) = element;
        }
    }
    findLargest(arr, size);
}