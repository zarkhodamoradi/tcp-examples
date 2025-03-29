from socket import * 
serverName = '127.0.0.1' 
serverPort = 12000
clientSocket = socket(AF_INET , SOCK_DGRAM)
message=""
while True : 
    message = input("client : ")
    clientSocket.sendto(message.encode() , (serverName , serverPort))
    modifiedMessage , serverAddress = clientSocket.recvfrom(2048)
    
    print ("server : ", serverAddress , modifiedMessage.decode())
    if message == 'q' : 
        break 

clientSocket.close()
