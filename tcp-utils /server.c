#include "server.h"

int main(int argc, char *argv[]) {
  // argv[0] : file name
  // argv[1] : port number
  if (argc < 2) {
    fprintf(stderr, "port No. not provided . program terminated . \n");
    exit(1);
  }
  int welcoming_sockfd, established_sockfd;
  char buffer[255];

  // openning the tcp connection
  opening(atoi(argv[1]), 3, &welcoming_sockfd, &established_sockfd);

  // do whatever you want
  read(established_sockfd, &buffer, sizeof(buffer));
  printf("%s", buffer);

  // closing the tcp connection
  closing(welcoming_sockfd, established_sockfd);
}
