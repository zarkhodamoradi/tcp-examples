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
int sockfd;
void error(const char *msg) {
  perror(msg);
  exit(0);
}
int running  = 1 ; 
void *write_messages(void *arg) {
  char buffer[255];
  int n;
  while (running) {
    bzero(buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
      error("Error writing message");
    if (strncmp(buffer, "q", 1) == 0) {
      printf("Closing connection...\n");
      running = 0 ; 
      shutdown(sockfd, SHUT_WR);
      break;
    }
  }
  return NULL;
}

void *read_messages(void *arg) {
  char buffer[255];
  int n;
  while (running) {
    bzero(buffer, sizeof(buffer));

    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
      error("Error on reading ");
    
    printf("Server : %s\n", buffer);

    if (strncmp(buffer, "q", 1) == 0) {
      printf("Server has left the chat.\n");
      running = 0 ; 
      break;
    }
  }

  return NULL;
}
int main(int argc, char *argv[]) {
  // argv[0] : filename
  // argv[1] : server_ipaddress
  // argv[2] : port number

  int portno, fd;
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
  pthread_t read_thread, write_thread;
  pthread_create(&read_thread, NULL, read_messages, NULL);
  pthread_create(&write_thread, NULL, write_messages, NULL);
  pthread_join(read_thread, NULL);
  pthread_join(write_thread, NULL);
 
  close(sockfd);
  printf("Connection closed"); 
  return 0;
}