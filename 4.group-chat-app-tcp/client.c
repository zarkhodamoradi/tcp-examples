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
#define BUFFER_SIZE 1024
void error(const char *msg) {
  perror(msg);
  exit(0);
}
void * receive_message(void * arg){
  int sockfd = *(int *) arg ; 
  char buffer[BUFFER_SIZE] ; 
  while (1) {
    bzero(buffer , sizeof(buffer)) ; 
    int n = recv(sockfd, buffer, sizeof(buffer), 0) ; 
    if(n <= 0 ){
      printf("Server disconnected.\n");
      close(sockfd);
      exit(0);
    }
    printf("%s", buffer);
  }
}

int main(int argc, char *argv[]) {
  // argv[0] : filename
  // argv[1] : server_ipaddress
  // argv[2] : port number

  int portno, fd , sockfd ; 
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[255];
  if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]);
    exit(0);
  }

  portno = atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("Error openning socket . ");

  server = gethostbyname(argv[1]);
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
  int n;
  pthread_t thread ; 
  pthread_create(&thread, NULL, receive_message, &sockfd) ; 
  pthread_detach(thread) ; 

  while (1) {
  bzero(buffer, sizeof(buffer)); 
  fgets(buffer, BUFFER_SIZE, stdin) ; 
  send(sockfd, buffer,  strlen(buffer), 0) ; 

  }
 
  close(sockfd);
  printf("Connection closed"); 
  return 0;
}