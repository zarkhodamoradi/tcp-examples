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
int counter =0; 
void *handle_client(void *client_socket) {
  int established_sockfd = *(int *)client_socket;
  free(client_socket);

  int num1, num2, answer, choice, n;

  while (1) {
    n = write(established_sockfd, "Enter number 1 : ",
              strlen("Enter number 1 : ")); // ask for number 1
    if (n < 0)
      error("Erro writing to socket");
    read(established_sockfd, &num1, sizeof(int)); // read number 1
    printf("Clinet%d number 1 is : %d\n",counter,  num1);

    n = write(established_sockfd, "Enter number 2 : ",
              strlen("Enter number 2 : ")); // ask for number 2
    if (n < 0)
      error("Erro writing to socket");
    read(established_sockfd, &num2, sizeof(int)); // read number 2
    printf("Clinet%d number 2 is : %d\n", counter , num2);

    char *str = "Enter your choice : \n1.+\n2.-\n3.*\n4./\n";
    n = write(established_sockfd, str, strlen(str)); // ask for choice
    if (n < 0)
      error("Error writing to socket ");
    read(established_sockfd, &choice, sizeof(int)); // read choice
    printf("Client%d - Choice is : %d \n",counter , choice);

    switch (choice) {
    case 1:
      answer = num1 + num2;
      break;
    case 2:
      answer = num1 - num2;
      break;
    case 3:
      answer = num1 * num2;
      break;
    case 4:
      answer = num1 / num2;
      break;
    }
    write(established_sockfd, &answer, sizeof(answer));

    str = "Do you want to Exit ? y/n";
    n = write(established_sockfd, str, strlen(str)); // ask for choice
    if (n < 0)
      error("Error writing to socket ");
    char c;
    read(established_sockfd, &c, sizeof(c)); // read choice
    printf("Client%D - Exit : %c \n",counter ,  c);
    if (c == 'y') {
      break;
    }
  }

  close(established_sockfd);
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

  while (1) {


    int *established_sockfd = malloc(sizeof(int));
    clilen = sizeof(cli_addr);

    *established_sockfd =
        accept(welcoming_sockfd, (struct sockaddr *)&cli_addr, &clilen);
    counter ++ ; 
    if (established_sockfd < 0) {
      free(established_sockfd);
      error("Error on Accept");
    }

    printf("New client(%d) connected!\n", counter);

    pthread_t thread ; 
    if (pthread_create(&thread, NULL, handle_client, established_sockfd) != 0) {
        error("Error creating thread");
    }

    pthread_detach(thread); 
  }

  close(welcoming_sockfd);

  return 0;
}