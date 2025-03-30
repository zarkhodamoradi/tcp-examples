#include <ctype.h>
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

int main(int argc, char *argv[]) {
  // argv[0] : filename
  // argv[1] : server_ipaddress
  // argv[2] : port number
  // argv[3] : name of the file 

  int portno, fd, sockfd ; 
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[1024];
  if (argc < 4) {
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
  bzero(buffer, sizeof(buffer)) ; 
  FILE * fp ; 


  fp = fopen(argv[3], "r") ; 

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  rewind(fp);

  // Send the file size to the server
  write(sockfd, &file_size, sizeof(file_size));

  // Send the file content in chunks
  size_t bytes_read;
  while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
    write(sockfd, buffer, bytes_read);
  }
  fclose(fp); 

  close(sockfd);
  printf("Connection closed"); 
  return 0;
}