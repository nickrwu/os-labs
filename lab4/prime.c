#include <stdio.h>
#include <stdlib.h>

int checkPrime(int num) {
    // Edge Case
    if (num == 0 || num == 1) {
        return 0;
    }

    for (int i = 2; i <= (num / 2); i++ ) {
        // Check if the number is divisible by the numbers up to half of the number 
        if (num % i == 0) {
            return 0;
        }
    }

    // If the number is not divisible by any number up to half of the number, it is prime
    return 1;
}

int main() {
    int n;

    printf("Enter the number you want to check the prime numbers up to: ");
    scanf("%d", &n);

    int *primes = (int *) malloc(n * sizeof(int));
    int index = 0;
    for (int num = 2; num <= n; num++) {
        if (checkPrime(num) == 1) {
            primes[index] = num;
            index++;
        }
    }

    // Printing Prime Numbers Array
    if (primes != NULL) {
        printf("Prime numbers up to %d:\n", n);
        for(int i=0; primes[i]; i++) {
            printf("%d ", primes[i]);
        }
    }

    free(primes);

    return 0;
} 