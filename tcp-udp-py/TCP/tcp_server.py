from socket import *
serverPort = 12000
welcomingSocket = socket(AF_INET,SOCK_STREAM)
welcomingSocket.bind(('',serverPort))
welcomingSocket.listen(1)
print ("The server is ready to receive ")
while True:
     connectionSocket, addr = welcomingSocket.accept()
     
     sentence = connectionSocket.recv(1024).decode()
     print(sentence , addr)
     capitalizedSentence = sentence.upper()
     connectionSocket.send(capitalizedSentence.encode())
     connectionSocket.close()
     