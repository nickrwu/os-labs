#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int pid;
    int arrival_time;
    int run_time;
} Process;

void SJF(Process arr [], int n) {
    for ( int i = 0; i < n - 1; i++) {
        for ( int j = i+1; j < n; j++) {
            // Sort by arrival time
            if (arr[i].run_time > arr[j].run_time) {
                Process temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Sort processes with the same arrival time based on run time
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(arr[i].arrival_time == arr[j].arrival_time) {
                if(arr[i].run_time > arr[j].run_time) {
                    Process temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
            else {
                break;
            }
        }
    }

    int time = 0;

    for (int i = 0; i < n; i++) {
        // Print the order in which the jobs are scheduled for execution
        printf("PID: %d \n", arr[i].pid);
        printf("Schedule time: %d \n", time);
        printf("Arrival time: %d \n", arr[i].arrival_time);
        printf("Run time: %d \n", arr[i].run_time);

        if (time + arr[i].run_time < arr[i+1].arrival_time) {
            time = arr[i+1].arrival_time;
        } else {
            time += arr[i].run_time;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s <processes> \n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        Process *p = malloc(sizeof(Process));
        
        p->pid = i;
        p->arrival_time = rand() % 10;
        p->run_time = rand() % 10;

        processes[i] = *p;
    }

    printf("Processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: arrival time = %d, run time = %d\n", processes[i].pid, processes[i].arrival_time, processes[i].run_time);
    }

    SJF(processes, n);

    return 0;

}