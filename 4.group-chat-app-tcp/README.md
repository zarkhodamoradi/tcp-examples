# Group Chat Application

This project consists of a simple multi-client chat server and a corresponding client program implemented in C using socket programming and multithreading.

## Features
- The server supports up to 10 clients simultaneously.
- Clients can send messages to the server, which are then broadcast to all other connected clients.
- The server manages client connections using threads and ensures safe concurrent access using mutex locks.
- The client program continuously listens for messages from the server while allowing the user to send messages.
- If a client disconnects, the server handles it gracefully.

## Prerequisites
- A Linux or macOS system (or a Linux-based VM on Windows).
- GCC compiler.
- Basic knowledge of C, sockets, and threading.

## Compilation
To compile the server and client:
```bash
gcc server.c -o server -pthread
gcc client.c -o client -pthread
```

## Running the Server
Run the server with a specified port number:
```bash
./server <port>
```
Example:
```bash
./server 12345
```

## Running the Client
Run the client with the server's IP address and port number:
```bash
./client <server_ip> <port>
```
Example:
```bash
./client 127.0.0.1 12345
```

## How It Works
- The server listens for incoming connections and spawns a new thread for each client.
- Clients send messages to the server, which then broadcasts them to all connected clients.
- A client can disconnect at any time, and the server updates its client list accordingly.

## Notes
- The maximum number of clients is set to 10. This can be modified by changing `MAX_CLIENTS` in `server.c`.
- The buffer size is set to 1024 bytes.
- To exit a client, you can use `Ctrl + C`.
- If the server reaches its maximum client capacity, new connections are rejected.

## Example Usage
1. Start the server:
   ```bash
   ./server 8080
   ```
2. Start multiple clients:
   ```bash
   ./client 127.0.0.1 8080
   ./client 127.0.0.1 8080
   ```
3. Send messages from one client, and all connected clients should receive them.

## License
This project is open-source and free to use.

