from socket import * 

serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET , SOCK_STREAM)
clientSocket.connect((serverName , serverPort))
message = "We are testing the tcp clinet , hello from here ... "
clientSocket.send(message.encode())
modifiedMessage = clientSocket.recv(1024)
print(modifiedMessage.decode())
clientSocket.close()