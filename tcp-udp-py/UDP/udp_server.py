from socket import * 

serverPort = 12000
serverSocket = socket(AF_INET , SOCK_DGRAM)
serverSocket.bind(('',serverPort))
print("The server is ready to recieve : ")
while True : 
    message , clientAddress  = serverSocket.recvfrom(2048)
    print(message.decode() ,"  ",clientAddress )
    modifiedMessage = message.decode().upper()
    serverSocket.sendto(modifiedMessage.encode() , clientAddress)
