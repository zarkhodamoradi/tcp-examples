#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>



void error(const char *msg) {
  perror(msg);
  exit(0);
}

void opening(int portnumber , int number_of_connections , int *welcoming_sock , int *established_sock ){
    int welcoming_sockfd, portno, n;
    int establised_sockfd;
    struct sockaddr_in serv_addr, cli_addr; // ipv4
    socklen_t clilen;                       // 32bit

  
    welcoming_sockfd =
        socket(AF_INET, SOCK_STREAM,
               0); // ipv4 , tcp , default protocol which is tcp for sock_stream
    if (welcoming_sockfd < 0)
      error("Error openning socket");
  
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = portnumber ; 
    serv_addr.sin_family = AF_INET;         // ipv4
    serv_addr.sin_addr.s_addr = INADDR_ANY; // like 127.0.0.1
    serv_addr.sin_port =
        htons(portno); // host to network short (port no. to network byte order)
  
    if (bind(welcoming_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
        0) {
      error("Binding failed");
    }
  
    listen(welcoming_sockfd, number_of_connections);
    clilen = sizeof(cli_addr);
  
    establised_sockfd =
        accept(welcoming_sockfd, (struct sockaddr *)&cli_addr, &clilen);
  
    if (establised_sockfd < 0) {
      error("Error on Accept");
    }

    *welcoming_sock = welcoming_sockfd ; 
    *established_sock = establised_sockfd ; 

  
}

void closing(int welcoming_sockfd , int establised_sockfd){
    close(establised_sockfd); 
    close(welcoming_sockfd);
  
}
