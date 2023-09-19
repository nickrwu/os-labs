#include <stdio.h>
#include <stdlib.h>

int fib (int n) {
    if  (n < 1) {
        return 0;
    } else if (n == 1) {
        return 1;
    }

    return fib(n-1) + fib(n-2);
}

int main () {
    int num;
    printf("Type a number: ");
    scanf("%d", &num);

    int result = fib(num);
    printf("The fibbonaci of %d is: %d\n", num, result);
    
    return 0;
}