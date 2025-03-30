
# File Transfer Server-Client Application

This repository contains a simple server-client application for file transfer over TCP/IP using C. The server listens for incoming client connections and receives a file sent by the client. The client sends a file to the server over a specified port.

## Features
- **Server:**
  - Listens for incoming connections from clients.
  - Receives a file from the client and saves it locally as `received.txt`.
  - Displays a success message upon completion.

- **Client:**
  - Connects to a server and sends a file.
  - Sends the file size first and then sends the content in chunks.
  - Closes the connection once the file transfer is complete.

## Prerequisites

Before running the code, ensure that you have the following:

- A C compiler (e.g., `gcc`).
- A Unix-like operating system (Linux/macOS).
- Sockets library available (included in most standard libraries).

## File Structure

```plaintext
.
├── client.c        # Client code for sending files to the server
├── server.c        # Server code for receiving files from the client
├── file.txt        # File which you wish to transfer (you can have your own file)
└── README.md       # This README file

```

## Compilation

To compile the server and client code, run the following commands:

### Server

```bash
gcc server.c -o server 
```

### Client

```bash
gcc client.c -o client
```

## Usage

### Running the Server

1. Open a terminal and navigate to the directory where the files are located.
2. Run the server on a specified port:

```bash
./server <port_number>
```

Example:

```bash
./server 8080
```

### Running the Client

1. Open another terminal and navigate to the directory where the files are located.
2. Run the client, specifying the server's IP address, port number, and the file to be sent:

```bash
./client <server_ip_address> <port_number> <file_path>
```

Example:

```bash
./client 127.0.0.1 8080 file_to_send.txt
```

### Flow of Execution

1. The **server** waits for a client connection on the given port.
2. The **client** connects to the server and sends the file:
   - First, the client sends the file size.
   - Then, the file content is sent in chunks.
3. The **server** receives the file and stores it as `received.txt`.

## Error Handling

The application performs basic error handling. If an error occurs, a descriptive message is printed, and the program exits. For example:
- If the server fails to open a socket, the message `Error opening socket` will be shown.
- If the client fails to connect to the server, the message `Connection Failed` will be shown.

## Notes

- The server saves the received file as `received.txt`. You can modify this in the server code if you wish to save it under a different name.
- Ensure that the specified port is open and not being used by another service.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

