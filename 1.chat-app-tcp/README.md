
# Chat Application (Client-Server)

This is a simple multithreaded chat application built using C programming language. The application follows a client-server model where the client can send messages to the server and the server can reply. Both the client and server run on separate threads to allow simultaneous reading and writing of messages. The communication happens over a TCP socket.

## Features

- **Multithreaded Communication:** The client and server both have separate threads for reading and writing messages.
- **Graceful Shutdown:** Both client and server can gracefully close the connection when the client sends `"q"`.
- **TCP Communication:** Uses TCP sockets for communication between the client and the server.

## Prerequisites

- **C Compiler:** You need a C compiler (e.g., GCC) to compile the source code.
- **Operating System:** The application is designed to run on Linux or other Unix-based systems. Ensure your system supports `pthread` and `sockets`.

## Compilation

To compile the server and client, follow these steps:

1. Clone this repository to your local machine.

   ```bash
   git clone https://github.com/zarkhodamoradi/tcp-examples.git
   cd chat-application-c
   ```

2. Compile the server and client programs:

   ```bash
   gcc -o server server.c 
   gcc -o client client.c 
   ```

## Running the Application

### 1. Start the Server

Run the server with a specified port number. For example, to run the server on port `8080`:

```bash
./server 8080
```

Server Port Range: Port numbers range from 0 to 65535, but certain ranges are reserved:

0-1023: These are well-known ports and are typically used by system services (e.g., HTTP, FTP).

1024-49151: These are registered ports and are used by user applications.

49152-65535: These are dynamic or private ports used for temporary connections.

For the purpose of this chat application, it's advisable to use a port number in the registered range (1024-49151) or dynamic range (49152-65535) to avoid conflicts with well-known ports.

The server will start listening for incoming connections from clients.

### 2. Start the Client

Run the client with the server's IP address and the port number. For example, if the server is running on `localhost` with port `8080`:

```bash
./client localhost 8080
```
To run the client and server on the same machine, use `127.0.0.1` or `localhost` as the server IP address in the client code and bind the server to `127.0.0.1` or `INADDR_ANY`.


You can now start sending messages from the client to the server. Both the client and server can send and receive messages simultaneously.

### 3. Exiting the Chat

- To exit the chat, type `"q"` in the client or server terminal.
- The connection will be closed, and the program will terminate gracefully.

## Code Structure

- **server.c**: The server-side implementation.
  - Listens for incoming client connections.
  - Creates separate threads for reading and writing messages to the client.

- **client.c**: The client-side implementation.
  - Connects to the server.
  - Creates separate threads for reading and writing messages to the server.

## License

This project is open-source and available under the MIT License.

## Contributing

Feel free to fork the repository and submit pull requests for any improvements or bug fixes.

