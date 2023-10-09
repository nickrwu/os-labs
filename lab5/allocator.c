#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct __node_t {
    char* p_name;
    int addr;
    int size;
    struct __node_t *next;
} Node;

void allocate_memory(Node *head, char *process_name, int size) {
    // Pointer to the head of the linked list
    Node *curr = head;
    Node *prev = NULL;

    // Pointer to the best fit block of memory
    Node *best_fit = NULL;

    // Initialize the minimum size to the maximum possible size
    int min_size = head->size + 1;

    int free_space = min_size;
    
    while (curr != NULL) {
        // Measure the free space between the previous and current block of memory
        // O -> O
        if (curr->next) {
            if (prev != NULL) {
                // If the current block of memory is not the head of the linked list
                // H -> [O] -> ... -> Null
                free_space = (curr->addr - 1) - (prev->addr + prev->size + 1);
            } else {
                // If the current block of memory is the head of the linked list
                // [H] -> O -> ... -> Null
                free_space = head->addr + (head->next->addr - 1);
            }
        } else {
            // Measure the free space between the current block of memory and the end of the memory
            // O -> Null
            if (curr != head) {
                // If the current block of memory is not the head of the linked list
                // O -> [O] -> Null
                free_space = head->size - (curr->addr + curr->size + 1);
            } else {
                // If the current block of memory is the head of the linked list
                // [H] -> Null
                free_space = head->size;
            }
        } 

        if (free_space >= size && free_space <= min_size) {
            // Set the minimum size to the free space
            min_size = free_space;
            best_fit = curr;

            // If an exact fit is found
            if (min_size == size) {
                break;
            }
        }

        prev = curr;
        curr = curr->next;
    }

    // No block of memory is found
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->p_name = process_name;
    new_node->size = size;

    if (best_fit == NULL) {
        printf("ERROR: Not enough memory to allocate process %s\n", process_name);
        return;
    }
    else if (best_fit == head) {
        // If the best fit is the head of the linked list
        
        if (head->next) {
            new_node->next = head->next;
        } else {
            new_node->next = NULL;
        }
        head->next = new_node;
        new_node->addr = 0;
    } else {
        // If the best fit is not the head of the linked list
        new_node->addr = best_fit->addr + best_fit->size + 1;
        new_node->next = best_fit->next;
        best_fit->next = new_node;
    }
}

void release_memory(Node *head, char *process_name) {
    Node *curr = head;
    Node *prev = NULL;
    while (curr != NULL) {
        if (strcmp(curr->p_name, process_name) == 0) {
            break;
        }

        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Error: Process %s not found\n", process_name);
        return;
    }

    // If the previous node is NULL, then the head needs to be updated.
    if (prev == NULL) {
        // X -> ... -> Null
        head->next = curr->next;
        free(curr);
    }


    Node *next = curr->next;

    // If the next node is not NULL, then the next node's address needs to be updated.
    if (next != NULL) {
        // O -> X -> O
        prev->next = next;
        free(curr);
    } else {
        // O -> X -> Null
        prev->next = NULL;
        free(curr);
    }
    printf("Released memory for process %s\n", process_name);
}

void compact (Node *head) {
    Node *curr = head;
    int end = 0;
    while (curr != NULL) {
        // Skip if the current node is the head of the linked list
        if (curr == head) { 
            curr = curr->next;
            continue;
        }
        
        // If the current node has a next node and they are the memory blocks are not next to each other
        if (curr->next && curr->next->addr != (curr->addr + curr->size) + 1) {
            // Set the next node's address to be next to the current node
            curr->next->addr = curr->addr + curr->size + 1;
        }

        curr = curr->next;
    }

    printf("Compacted memory\n");
}

void print_status(Node *head) {
    Node *curr = head;

    while (curr != NULL) {
        // If there is unused space from the head to the first process node
        if (curr == head && curr->next && curr->next->addr > 0) {
                printf("Addresses [%d:%d] Unused\n", curr->addr, curr->next->addr - 1);
        }

        // If the current node is not the head of the linked list
        else if (curr != head) {
            printf("Addresses [%d:%d] Process %s\n", curr->addr, curr->addr + curr->size, curr->p_name);
            if (curr->next && curr->next->addr - (curr->addr + curr->size + 1) > 0) {
                printf("Addresses [%d:%d] Unused\n", curr->addr + curr->size + 1, curr->next->addr - 1);
            } else if (!curr->next && curr->addr + curr->size < head->size) {
                printf("Addresses [%d:%d] Unused\n", curr->addr + curr->size + 1, head->size);
            }
        }

        curr = curr->next;
    }

    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2 || atoi(argv[1]) < 1) {
        printf("Usage: ./allocator {memory size}\n");
        exit(1);
    }

    // mmap() returns a pointer to a chunk of free space
    int memory_size = atoi(argv[1]);
    Node *head = mmap(NULL, memory_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    head->size = memory_size;
    head->p_name = "HEAD";
    head->next = NULL;
    head->addr = 0;

    while (1) {
        printf("allocator> ");

        char *input = NULL;
        size_t bufrsize = 0;
        getline(&input, &bufrsize, stdin);
        input[strcspn(input, "\n")] = '\0';

        char *command = strtok(input, " ");

        if (strcmp(command, "RQ") == 0 || strcmp(command, "rq") == 0) {
            char* process_name = strtok(NULL, " ");
            char* psize = strtok(NULL, " ");

            if (process_name && psize) {
                int process_size = atoi(psize);

                if (process_size > 0) {
                    allocate_memory(head, process_name, process_size);
                } else {
                    printf("Usage: RQ {process name} {process size}.\n");
                }

            } else {
                printf("Usage: RQ {process name} {process size}.\n");
            }

            // allocate_memory(, process_name, process_size);

        } else if (strcmp(command, "RL") == 0 || strcmp(command, "rl") == 0) {
            char *process_name = strtok(NULL, " ");
            release_memory(head, process_name);
        } else if (strcmp(command, "C") == 0 || strcmp(command, "c") == 0) {
            compact(head);
        } else if (strcmp(command, "STAT") == 0 || strcmp(command, "stat") == 0) {
            print_status(head);
        } else if (strcmp(command, "X") == 0 || strcmp(command, "x") == 0) {
            exit(0);
        } else {
            printf("ERROR: Invalid command.\n");
        }
    }
    return 0;
}