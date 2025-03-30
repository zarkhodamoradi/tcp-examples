# TCP Socket Communication - Simple Calculator (Multi-Threaded )

## Overview
This project implements a multi-threaded calculator server using C, which communicates with clients over a network using sockets. The server accepts multiple client connections and provides basic arithmetic operations (+, -, *, /).

## Features
- Multi-threaded handling of multiple clients using `pthread`
- Supports addition, subtraction, multiplication, and division
- Interactive communication between client and server
- Graceful handling of client disconnection

## Requirements
- GCC compiler
- POSIX-compliant system (Linux, macOS)
- Basic knowledge of socket programming

## Compilation
To compile the server program, use:
```sh
gcc server.c -o server -pthread
```
To compile the client program:
```sh
gcc client.c -o client
```

## Usage
### Running the Server
Start the server by providing a port number:
```sh
./server <port_number>
```
Example:
```sh
./server 8080
```

You can use any port number between 1024 and 49151 

### Running the Client
On a separate terminal, connect a client to the server:
```sh
./client <server_ip> <port_number>
```
Example:
```sh
./client 127.0.0.1 8080
```

## Server-Client Interaction
1. The client enters two numbers.
2. The client chooses an arithmetic operation:
   - 1: Addition (+)
   - 2: Subtraction (-)
   - 3: Multiplication (*)
   - 4: Division (/)
3. The server processes the request and returns the result.
4. The client can continue operations or choose to exit.

## Example Interaction
```
Client: Enter number 1: 5
Client: Enter number 2: 3
Client: Enter your choice:
1. +
2. -
3. *
4. /
Client: 1
Server: Result is 8
Client: Do you want to exit? (y/n)
```

## Multi-threading Support
- Each client connection is handled in a separate thread.
- The server continues accepting new clients without blocking ongoing operations.

## Error Handling
- The server properly handles socket errors and client disconnections.
- Invalid inputs are managed gracefully.

## License
This project is open-source under the MIT License.

