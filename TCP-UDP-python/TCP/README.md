

# TCP Server and Client (Educational Example)

This repository contains a simple Python-based TCP server and client, designed for educational purposes to demonstrate basic TCP communication.

## Files:
1. **tcp_server.py**: A server that listens on a specific IP and port, receives messages from clients, and sends back the capitalized version of the message.
2. **tcp_client.py**: A client that connects to the server, sends a message, and prints the server's response.

## How to Run:
1. **Start the Server**:
   ```bash
   python3 tcp_server.py
   ```
2. **Start Multiple Clients**:
   In separate terminals, run:
   ```bash
   python3 tcp_client.py
   ```

   Each client will send a message to the server and print the server's capitalized response along with the client's IP and port.

## How it Works:
- The **server** listens on port `12000` and processes multiple client connections.
- The **client** connects to the server at `127.0.0.1` (localhost), sends a message, and displays the capitalized response.

## Notes:
- Multiple clients can send messages to the server . Each message from a client is processed, and the server responds with the modified message.
- Use `127.0.0.1` for the server IP to run both on the same machine (localhost).

## Educational Purpose:
This project demonstrates:
- TCP server and client communication.
- Sending and receiving messages over TCP.
- Basic string processing (capitalization) and Python socket usage.

## Requirements:
- Python 3.x
