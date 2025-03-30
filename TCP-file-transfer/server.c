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

int main(int argc, char *argv[]) {
  // argv[0] : file name
  // argv[1] : port number
  if (argc < 2) {
    fprintf(stderr, "port No. not provided . program terminated . \n");
    exit(1);
  }

  int welcoming_sockfd, portno, n;

  struct sockaddr_in serv_addr, cli_addr; // ipv4
  socklen_t clilen;                       // 32bit
  char buffer[1024];

  welcoming_sockfd =
      socket(AF_INET, SOCK_STREAM,
             0); // ipv4 , tcp , default protocol which is tcp for sock_stream
  if (welcoming_sockfd < 0)
    error("Error openning socket");

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;         // ipv4
  serv_addr.sin_addr.s_addr = INADDR_ANY; // like 127.0.0.1
  serv_addr.sin_port =
      htons(portno); // host to network short (port no. to network byte order)

  if (bind(welcoming_sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
      0) {
    error("Binding failed");
  }

  listen(welcoming_sockfd, 5);
  clilen = sizeof(cli_addr);
  int established_sockfd ; 
  established_sockfd =
      accept(welcoming_sockfd, (struct sockaddr *)&cli_addr, &clilen);

  if (established_sockfd < 0) {
    error("Error on Accept");
  }
   
  FILE *fp = fopen("received.txt", "a");
  if (fp == NULL) {
    error("Error opening file for writing");
  }

  long file_size;
  read(established_sockfd, &file_size, sizeof(file_size)); 

  long bytes_received = 0;
  size_t bytes_read;
  while (bytes_received < file_size) {
    bytes_read = read(established_sockfd, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
      break;
    }
    fwrite(buffer, 1, bytes_read, fp);
    bytes_received += bytes_read;
  }
   printf("The file has been received successfully .it's saved by the name received.txt "); 

   

  close(established_sockfd); 
  close(welcoming_sockfd);

  return 0;
}