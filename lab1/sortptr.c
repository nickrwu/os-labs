#include <stdio.h>

void insertionSort(int* ptr, int size) {
    int current;

    for (int i = 1; i < size; i++) {
        current = *(ptr + i);
        for (int j = i - 1; j >= 0; j--) {
            if (current < *(ptr + j)) {
                // shift to the right
                *(ptr + j + 1) = * (ptr + j);
                *(ptr + j) = current;
            } else {
                continue;
            }
        }
    }

    printf("Sorted array: \n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(ptr + i)); 
    }
    printf("\n");
}

int main() {
    int size = 5;
    int array [] = { 0, 23, 14, 12, 9 };

    insertionSort(array, size);
    return 0;
}