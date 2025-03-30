# TCP Connection Library

This project provides a simple and reusable C library for establishing a TCP connection using client-server architecture. It abstracts the low-level socket programming details, making it easier to set up and manage TCP connections.

## Features
- **Easy-to-use API**: Provides simple functions for opening and closing TCP connections.
- **Client and Server Support**: Includes separate headers for client and server functionalities.
- **Minimal Configuration**: Just pass the required parameters, and the library handles the rest.

---

## Getting Started
### Prerequisites
Ensure you have a C compiler (e.g., `gcc`) and standard networking libraries installed on your system.

### Compilation
To compile the server and client programs, run:
```sh
gcc server.c -o server
gcc client.c -o client
```

### Usage
#### 1️⃣ Start the Server
Run the server first, specifying a port number:
```sh
./server <port>
```
Example:
```sh
./server 8080
```

#### 2️⃣ Start the Client
Run the client, providing the server's IP address and port:
```sh
./client <server_ip> <port>
```
Example:
```sh
./client 127.0.0.1 8080
```

The client will prompt you to enter a string, which will be sent to the server. The server will then print the received message.

---

## Library Functions
### `client.h`
#### `void opening(char *ip, int port, int *ret_sockfd);`
- Establishes a TCP connection to the server.
- **Parameters:**
  - `ip`: Server IP address
  - `port`: Port number to connect to
  - `ret_sockfd`: Pointer to store the connected socket file descriptor

#### `void closing(int sockfd);`
- Closes the client socket.
- **Parameter:** `sockfd` - Socket file descriptor to close

### `server.h`
#### `void opening(int portnumber, int number_of_connections, int *welcoming_sock, int *established_sock);`
- Sets up a TCP server socket and waits for incoming connections.
- **Parameters:**
  - `portnumber`: Port number to bind the server to
  - `number_of_connections`: Maximum number of pending connections
  - `welcoming_sock`: Pointer to store the welcoming socket file descriptor
  - `established_sock`: Pointer to store the accepted client socket file descriptor

#### `void closing(int welcoming_sockfd, int established_sockfd);`
- Closes both the client and server sockets.
- **Parameters:**
  - `welcoming_sockfd`: Server socket file descriptor
  - `established_sockfd`: Connected client socket file descriptor

---

## Example Code
### Server Example (`server.c`)
```c
#include "server.h"

int main(int argc, char *argv[]) {
  // argv[0] : file name
  // argv[1] : port number
  if (argc < 2) {
    fprintf(stderr, "port No. not provided . program terminated . \n");
    exit(1);
  }
  int welcoming_sockfd, established_sockfd;
  char buffer[255];

  // openning the tcp connection
  opening(atoi(argv[1]), 3, &welcoming_sockfd, &established_sockfd);

  // do whatever you want
  read(established_sockfd, &buffer, sizeof(buffer));
  printf("%s", buffer);

  // closing the tcp connection
  closing(welcoming_sockfd, established_sockfd);
}

```

### Client Example (`client.c`)
```c
#include "client.h"

int main(int argc, char *argv[]) {
    // argv[0] : filename
    // argv[1] : server_ipaddress
    // argv[2] : port number
    int sockfd ; 
    char buffer[255] ; 
    //connection the tcp connection 
    opening(argv[1],atoi(argv[2]),&sockfd ) ; 

    // here do whatever you want 
    printf("Enter a string : ") ; 
    fgets(buffer, sizeof(buffer), stdin);
    write(sockfd, buffer, sizeof(buffer)); 


    // closing the tcp connection 
    closing(sockfd); 
  
  
    return 0;
  }
```

---

## Contribution
Feel free to contribute by submitting issues or pull requests!

## License
This project is licensed under the MIT License.

