#include "client.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    // argv[0] : filename
    // argv[1] : server_ipaddress
    // argv[2] : port number
    int sockfd ; 
    char buffer[255] ; 
    //connection the tcp connection 
    opening(argv[1],atoi(argv[2]),&sockfd ) ; 

    // here do whatever you want 
    printf("Enter a string : ") ; 
    fgets(buffer, sizeof(buffer), stdin);
    write(sockfd, buffer, sizeof(buffer)); 


    // closing the tcp connection 
    closing(sockfd); 
  
  
    return 0;
  }