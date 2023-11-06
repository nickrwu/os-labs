#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUFFERSIZE 5

int buffer[BUFFERSIZE];
int count = 0;
int in = 0;
int out = 0;

void producer(int w_end) {
    int item;
    while (1) {
        if (count == BUFFERSIZE) {
            printf("Buffer is full. Producer is waiting...\n");
            sleep(1);
        }
        
        int item = rand() % 100;
        buffer[in] = item;
        in = (in + 1) % BUFFERSIZE;

        count++;

        printf("Producing item: %d\n", item);

        write(w_end, &buffer, sizeof(buffer));
        sleep(1);
    }

    close(w_end);
}

void consumer(int r_end) {
    int item;
    while (1) {
        if (count == 0) {
            printf("Buffer is empty. Consumer is waiting...\n");
            sleep(1);
        }

        read(r_end, &buffer, sizeof(buffer));
        
        item = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % BUFFERSIZE;
        count--;

        printf("Consuming item: %d\n", item);
        sleep(1);
    }

    close(r_end);
}

int main (int argc, char *argv[]) {
    srand(time(NULL));

    int fd[2];

    if(pipe(fd) == -1){
        printf("\nError: Pipe could not be created\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error: Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child Process = Producer
        // Closing read/write end of producer pipe and read end of consumer pipe
        close(fd[0]);
        producer(fd[1]);
       
        exit(EXIT_SUCCESS);

    } else {
        // Parent Process = Consumer
        // Closing read end of producer pipe and write end of consumer pipe
        close(fd[1]);
        consumer(fd[0]);

        exit(EXIT_SUCCESS);
    }

    return 0;
}