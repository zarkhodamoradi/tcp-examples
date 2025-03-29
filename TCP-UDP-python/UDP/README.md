
# UDP Server and Client (Educational Example)

This repository demonstrates basic UDP communication using Python, designed for educational purposes.

## Files:
1. **udp_server.py**: A server that listens on port `12000` for incoming UDP messages, modifies them (capitalizes), and sends them back to the client. It can handle multiple clients sending messages simultaneously.
2. **udp_client.py**: A client that sends messages to the server and prints the server's response.

## How to Run:
1. **Start the Server**:
   ```bash
   python3 udp_server.py
   ```
   The server listens on port `12000` and can accept messages from multiple clients.

2. **Start the Client(s)**:
   ```bash
   python3 udp_client.py
   ```
   The client will send messages to the server and print the capitalized response. You can run multiple clients, and each one will receive a response from the server.

## How it Works:
- The **server** listens on port `12000` for incoming UDP messages and sends back the capitalized message.
- The **client** connects to the server at `127.0.0.1` (localhost), sends a message, and displays the server's response.
- Multiple clients can send messages to the server simultaneously. Each client's message will be processed and responded to independently.
- To exit, type `q` in the client terminal.

## Educational Purpose:
This project demonstrates:
- Sending and receiving UDP messages.
- Handling multiple clients sending messages simultaneously.
- Basic message processing (capitalization) and Python socket usage.

## Requirements:
- Python 3.x
