#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP_ADDRESS "127.0.0.1";
#define PORT 8080;
 
int main() {
    int port = PORT;
    char *ip = IP_ADDRESS;

    // Define variables
    int server_fd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024] = {0};

    // Create TCP socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("[-]Socket error");
        exit(EXIT_FAILURE);
    }
    printf("[+]TCP server socket created.\n");

    // Initialize server address and port
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Bind socket descriptor to server address
    if (bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Bind error");
        exit(EXIT_FAILURE);
    }
    printf("[+]Bind to the port number: %d\n", port);

    // Listen for incoming client connections
    if (listen(server_fd, 3) < 0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    } else {
        printf("[+]Listening...\n");
    }


    while(1) {
        // Accept client connection
        addr_size = sizeof(client_addr);
        if ((client_sock = accept(server_fd, (struct sockaddr*) &client_addr, &addr_size)) < 0) {
            perror("[-]Accept failed");
            exit(EXIT_FAILURE);
        } else {
            printf("[+]Client connected.\n");
        }

        // Receive message from client
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s\n", buffer);

        // Send reply message to client
        bzero(buffer, 1024);
        strcpy(buffer, "Message Received. Hello!!");
        printf("Server: %s\n", buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        // Close socket connection
        close(client_sock);
        printf("[+]Client disconnected.\n\n");

    }
    return 0;
}