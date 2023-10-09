#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
    // argv[1] is the string to be passed to the child process
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

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
        // Closing the write end of the pipe
        close(fd[1]);
        // Duplicate the read end of the pipe to stdin
        dup2(fd[0], STDIN_FILENO);

        // Read string from stdin
        char buf[100];
        read(STDIN_FILENO, buf, 100);
        printf("Passing into child process: %s\n", buf);

        exit(EXIT_SUCCESS);

    } else {
        // Parent process writes to child process

        // Closing the read end of the pipe
        close(fd[0]);

        // Duplicate the write end of the pipe to stdout
        dup2(fd[1], STDOUT_FILENO);

        printf("Passing from parent process: %s\n", argv[1]);

        // Write to stdout
        write(STDOUT_FILENO, argv[1], 100);

        exit(EXIT_SUCCESS);
    }

    return 0;
}