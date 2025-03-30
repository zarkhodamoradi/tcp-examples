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

int main(int argc, char *argv[]) {
  // argv[0] : filename
  // argv[1] : server_ipaddress
  // argv[2] : port number

  int portno, fd;
  struct sockaddr_in serv_addr;
  struct hostent *server;

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
  char buffer[255];

  int number1, number2, choice, answer;
  while (1) {
    bzero(buffer, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
      error("Error reading from socket . ");
    printf("Server - %s \n", buffer);
    scanf("%d", &number1);
    write(sockfd, &number1, sizeof(number1));

    bzero(buffer, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
      error("Error reading from socket . ");
    printf("Server - %s \n", buffer);
    scanf("%d", &number2);
    write(sockfd, &number2, sizeof(number2));

    bzero(buffer, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
      error("Error reading from socket . ");
    printf("Server - %s \n", buffer);
    scanf("%d", &choice);
    write(sockfd, &choice, sizeof(choice));

    bzero(buffer, sizeof(buffer));
    n = read(sockfd, &answer, sizeof(answer));
    if (n < 0)
      error("Error reading from socket . ");
    printf("Server - The answer is : %d \n-----------------------------\n",
           answer);

    bzero(buffer, sizeof(buffer));
    n = read(sockfd, buffer, sizeof(buffer));
    if (n < 0)
      error("Error reading from socket . ");
    printf("Server - %s \n", buffer);
    while ((getchar()) != '\n')
      ;
    char c = getchar();
    write(sockfd, &c, sizeof(c));

    if (c == 'y')
      break;
  }

  close(sockfd);
  printf("Connection closed");
  return 0;
}