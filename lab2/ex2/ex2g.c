#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *arg[]) {

    int k,i;
    
    printf("Enter the number of children: ");
    scanf("%d", &k);

    pid_t pids [k];

    for (i = 0; i < k; i++) {
        pids[i] = fork();
        if(pids[i] < 0) {
            perror("fork failed");
            exit(1);
        } else if(pids[i] == 0) {
            printf("[son] pid %d from [parent] pid %d\n", (int) getpid(), (int) getppid());
        }
    }

    for(i=0; i < k; i++){
        waitpid(pids[i],NULL,0);
    }

    return 0;
}