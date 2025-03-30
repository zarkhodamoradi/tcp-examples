#include <netdb.h>
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
void opening(char * ip , int port , int *ret_sockfd ){
    int portno, fd;
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
  

  
    portno = port ; 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
      error("Error openning socket . ");
     
    server = gethostbyname(ip);
    if (server == NULL) {
      fprintf(stderr, "Error no such host \n");
      exit(0);
    }
  
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr_list[0], &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
  
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
      error("Connection Failed");
    }

    *ret_sockfd = sockfd ; 
  
  
}
void closing(int sockfd){

    close(sockfd);
    printf("Connection closed"); 
}


