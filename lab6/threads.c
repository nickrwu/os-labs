#include <stdio.h>
#include <pthread.h>
void *print_thread(void *arg) {
    printf("Executing Thread %s...\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2, p3, p4;
    pthread_create(&p1, NULL, print_thread, "p1");
    pthread_create(&p2, NULL, print_thread, "p2");
    pthread_create(&p3, NULL, print_thread, "p3");
    pthread_create(&p4, NULL, print_thread, "p4");

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);

    return 0;
}
