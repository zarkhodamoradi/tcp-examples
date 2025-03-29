#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int establised_sockfd;

void error(const char *msg) {
  perror(msg);
  exit(0);
}
int running = 1 ; 
void *read_messages(void *arg) {
  char buffer[255];
  int n;
  while (running) {
    bzero(buffer, sizeof(buffer));
    n = read(establised_sockfd, buffer, 255);
    if (n < 0)
      error("Error on reading ");

    if (strlen(buffer) > 0) {
      printf("Client: %s\n", buffer);
      if (strncmp(buffer, "q", 1) == 0) {
        printf("Client has left the chat.\n");
        running =  0 ; 
        break;
      }
    }
  }

  return NULL;
}

void *write_messages(void *arg) {
  char buffer[255];
  int n;
  while (running) {
    bzero(buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);
    n = write(establised_sockfd, buffer, strlen(buffer));

    if (n < 0)
      error("Error on Writing .");

    if (strncmp(buffer, "q", 1) == 0) {
      printf("Closing connection...\n");
      running = 0  ; 
      break;
    }
  }

  return NULL;
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
  char buffer[255];

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

  establised_sockfd =
      accept(welcoming_sockfd, (struct sockaddr *)&cli_addr, &clilen);

  if (establised_sockfd < 0) {
    error("Error on Accept");
  }

  pthread_t read_thread, write_thread;
  pthread_create(&read_thread, NULL, read_messages, NULL);
  pthread_create(&write_thread, NULL, write_messages, NULL);
  pthread_join(read_thread, NULL);
  pthread_join(write_thread, NULL);
  close(establised_sockfd); 
  close(welcoming_sockfd);

  return 0;
}