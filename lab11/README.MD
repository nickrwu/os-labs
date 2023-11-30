## TCP
`tcp.c` initializes the server, creates a TCP socket, binds the socket to the server address, listens for incoming connections, and handles client connections in an infinite loop.

1. `gcc tcp.c -o tcp; ./tcp`
2. `gcc client-tcp.c -o client-tcp; ./client-tcp`

## UDP
`udp.c` creates a UDP socket, binds it to a specific IP address and port number, and listens for incoming messages.
When a message is received, it prints the message from the client and sends a reply message back to the client.
The server runs in an infinite loop, continuously receiving and sending messages to and from the client.

1. `gcc udp.c -o udp; ./udp`
2. `gcc client-udp.c -o client-udp; ./client-udp`
