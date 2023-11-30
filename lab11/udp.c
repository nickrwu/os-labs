#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP_ADDRESS "127.0.0.1"
#define PORT 8080
 
int main() {
    int port = PORT;
    char *ip = IP_ADDRESS;

    // Define variables
    int server_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024] = {0};

    // Create UDP socket
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("[-]Socket error");
        exit(EXIT_FAILURE);
    }
    printf("[+]UDP server socket created.\n");

    // Initialize server address and port
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind socket descriptor to server address
    if (bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Bind error");
        exit(EXIT_FAILURE);
    }
    printf("[+]Bind to the port number: %d\n", port);

    while(1) {
        // Receive message from client
        addr_size = sizeof(client_addr);
        if (recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr*) &client_addr, &addr_size) < 0) {
            perror("[-]Receive failed");
            exit(EXIT_FAILURE);
        } else {
            printf("[+]Message received from client.\n");
        }

        printf("Client: %s\n", buffer);

        // Send reply message to client
        strcpy(buffer, "Message Received. Hello!!");
        printf("Server: %s\n", buffer);
        if (sendto(server_fd, buffer, strlen(buffer), 0, (struct sockaddr*) &client_addr, addr_size) < 0) {
            perror("[-]Send failed");
            exit(EXIT_FAILURE);
        }

        printf("[+]Reply message sent to client.\n\n");
    }

    return 0;
}