#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
void error (const char * msg){
    perror(msg) ; 
    exit(0) ; 
}
int main(int argc  , char * argv []){
    int sockfd , portno , n ; 
    struct sockaddr_in serv_addr ; 
    struct hostnet * server ; 
    char buffer[256] ; 
    if (argc < 3) {
    fprintf(stderr, "usage %s hostname port\n", argv[0]) ; 
    exit(0); 
    }

}