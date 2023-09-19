#include <stdio.h>
#include <stdlib.h>

int main () {
    int x, y;

    printf("Enter an integer for x: ");
    scanf("%d", &x);
    printf("Enter an integer for y: ");
    scanf("%d", &y);

    int * ptr = &x;

    int tmp = *ptr;

    x = y;
    y = tmp;

    printf("x: %d, y: %d\n", x, y);

    return 0;
}
