#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int start;
    int size;
    struct node *next;
} Node;

Node *head = NULL;
int memory_size;

void print_status() {
    Node *curr = head;
    int end = 0;
    while (curr != NULL) {
        if (curr->start > end) {
            printf("[%d:%d] Unused ", end, curr->start - 1);
        }
        printf("[%d:%d] Process ", curr->start, curr->start + curr->size - 1);
        end = curr->start + curr->size;
        curr = curr->next;
    }
    if (end < memory_size) {
        printf("[%d:%d] Unused ", end, memory_size - 1);
    }
    printf("\n");
}

void allocate_memory(char *process_name, int size) {
    Node *curr = head;
    Node *prev = NULL;
    Node *best_fit = NULL;
    int min_size = memory_size + 1;
    while (curr != NULL) {
        if (curr->size >= size && curr->size < min_size) {
            min_size = curr->size;
            best_fit = curr;
            if (min_size == size) {
                break;
            }
        }
        prev = curr;
        curr = curr->next;
    }
    if (best_fit == NULL) {
        printf("Error: Not enough memory to allocate process %s\n", process_name);
        return;
    }
    if (best_fit->size == size) {
        if (prev == NULL) {
            head = best_fit->next;
        } else {
            prev->next = best_fit->next;
        }
    } else {
        best_fit->start += size;
        best_fit->size -= size;
    }
    printf("Allocated %d bytes for process %s\n", size, process_name);
}

// This function releases memory for a given process name.
void release_memory(char *process_name) {
    // Initialize the current node to the head of the linked list and the previous node to NULL.
    Node *curr = head;
    Node *prev = NULL;
    // Traverse the linked list until the end or until the current node matches the process name.
    while (curr != NULL) {
        // If the current node is the first node and the process name is "P0", then it cannot be released.
        if (curr->start == 0 && strcmp(process_name, "P0") == 0) {
            printf("Error: Cannot release memory for process %s\n", process_name);
            return;
        }
        // If the process name is not "P0" and starts with "P" and the number after "P" matches the start of the current node, then break out of the loop.
        if (strcmp(process_name, "P0") != 0 && strncmp(process_name, "P", 1) == 0 && atoi(process_name + 1) == curr->start) {
            break;
        }
        // Update the previous and current nodes.
        prev = curr;
        curr = curr->next;
    }
    // If the current node is NULL, then the process name was not found.
    if (curr == NULL) {
        printf("Error: Process %s not found\n", process_name);
        return;
    }
    // If the previous node is NULL, then the head needs to be updated.
    if (prev == NULL) {
        head = curr;
    } else {
        prev->next = curr;
    }
    // Initialize the next node to the current node's next node and the end to the current node's start plus its size.
    Node *next = curr->next;
    int end = curr->start + curr->size;
    // Traverse the linked list while the next node is not NULL and its start is equal to the end of the current node.
    while (next != NULL && next->start == end) {
        // Merge the current node with the next node.
        curr->size += next->size;
        curr->next = next->next;
        free(next);
        next = curr->next;
        end = curr->start + curr->size;
    }
    // If the previous node is not NULL and its end is equal to the start of the current node, then merge the previous node with the current node.
    if (prev != NULL && prev->start + prev->size == curr->start) {
        prev->size += curr->size;
        prev->next = curr->next;
        free(curr);
    }
    // Print a message indicating that the memory has been released for the process name.
    printf("Released memory for process %s\n", process_name);
}

void compact_memory() {
    Node *curr = head;
    int end = 0;
    while (curr != NULL) {
        if (curr->start > end) {
            memmove((void *) (intptr_t) end, (void *) (intptr_t) curr->start, curr->size);
            curr->start = end;
        }
        end = curr->start + curr->size;
        curr = curr->next;
    }
    Node *prev = NULL;
    curr = head;
    while (curr != NULL) {
        if (curr->size == 0) {
            if (prev == NULL) {
                head = curr->next;
            } else {
                prev->next = curr->next;
            }
            Node *temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    printf("Compacted memory\n");
}

int main(int argc, char **argv) {
    if (argc != 2 || atoi(argv[1]) < 1) {
        printf("Usage: ./allocator {memory size}\n");
        exit(1);
    }

    memory_size = atoi(argv[1]);
    head = malloc(sizeof(Node));
    head->start = 0;
    head->size = memory_size;
    head->next = NULL;

    while (1) {
        printf("allocator> ");

        char *input = NULL;
        size_t bufrsize = 0;
        getline(&input, &bufrsize, stdin);
        input[strcspn(input, "\n")] = '\0';

        char *command = strtok(input, " ");
        if (strcmp(command, "RQ") == 0) {
            char *process_name = strtok(NULL, " ");
            int size = atoi(strtok(NULL, " "));
            allocate_memory(process_name, size);
        } else if (strcmp(command, "RL") == 0) {
            char *process_name = strtok(NULL, " ");
            release_memory(process_name);
        } else if (strcmp(command, "C") == 0) {
            compact_memory();
        } else if (strcmp(command, "STAT") == 0) {
            print_status();
        } else if (strcmp(command, "X") == 0) {
            break;
        } else {
            printf("Error: Invalid command\n");
        }

        free(input);
    }

    Node *curr = head;
    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }

    return 0;
}