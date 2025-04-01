#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int client_sockets[MAX_CLIENTS]; // for client_fd , 0 if thre is no client
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void error(const char *msg) {
  perror(msg);
  exit(0);
}

void broadcast_messages(char *message, int sender_fd) {
  pthread_mutex_lock(&clients_mutex);

  for (int i = 0; i < MAX_CLIENTS; i++) {
    if (client_sockets[i] != 0 && client_sockets[i] != sender_fd) {
      send(client_sockets[i], message, strlen(message), 0);
    }
  }

  pthread_mutex_unlock(&clients_mutex);


}

void *handle_client(void *arg) {
  int client_fd = *(int *)arg;
  char buffer[BUFFER_SIZE];
  while (1) {
    bzero(buffer, sizeof(buffer));
    int n = recv(client_fd, buffer, sizeof(buffer), 0);
    if (n <= 0) {
      printf("Client disconnected: %d\n", client_fd);
      close(client_fd);

      pthread_mutex_lock(&clients_mutex);
      for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client_sockets[i] == client_fd) {
          client_sockets[i] = 0;
          break;
        }
      }
      pthread_mutex_unlock(&clients_mutex);
      pthread_exit(NULL);
    }
    printf("Client %d: %s", client_fd, buffer);
    broadcast_messages(buffer, client_fd);
  }
}

int main(int argc, char *argv[]) {
  // argv[0] : file name
  // argv[1] : port number
  if (argc < 2) {
    fprintf(stderr, "port No. not provided . program terminated . \n");
    exit(1);
  }

  int welcoming_sockfd, portno, n;
  bzero(client_sockets, sizeof(client_sockets));

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

  listen(welcoming_sockfd, MAX_CLIENTS);
  clilen = sizeof(cli_addr);
  int established_client_fd;
  while (1) {
    established_client_fd =
        accept(welcoming_sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if(established_client_fd < 0 ){
        error("Error on accept . ") ; 
    }

    printf("New client connected: %d\n", established_client_fd);

    pthread_mutex_lock(&clients_mutex) ; 
    int added = 0 ; 
    for (int i = 0 ; i < MAX_CLIENTS; i++) {
    if (client_sockets[i] == 0 ) {
    client_sockets[i]  = established_client_fd ; 
    added = 1 ; 
    break;
    }
    }
    if(!added){
        printf("Server full! Rejecting client: %d\n", established_client_fd);
            close(established_client_fd);
            continue;
    }
    pthread_mutex_unlock(&clients_mutex) ; 
    pthread_t thread;
    pthread_create(&thread, NULL, handle_client, &established_client_fd);
    pthread_detach(thread);

  }

  close(welcoming_sockfd) ; 

  return 0;
}