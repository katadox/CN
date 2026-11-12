#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 12345

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serveraddr, clientaddr; 
    socklen_t len;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    serveraddr.sin_port=htons(PORT);

    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));  //bind() syntax is used to bind the socket to the specified address and port number. It takes three arguments: the file descriptor of the socket, a pointer to the address structure, and the size of the address structure.

    printf("server is listening....\n");

    len=sizeof(clientaddr);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&clientaddr,&len); //recvform() syntax is used to receive data from the socket. It takes six arguments: the file descriptor of the socket, a pointer to a buffer where the data will be stored, the maximum number of bytes to read, flags (set to 0 for default behavior), a pointer to a structure that will hold the address information of the sending client, and a pointer to a variable that will hold the size of the address structure. It returns the number of bytes received.
    printf("message from client: %s\n",buffer);

    char *msg="hello from server";

    sendto(sockfd,msg,strlen(msg)+1,0,(struct sockaddr *)&clientaddr,sizeof(clientaddr));
    close(sockfd);
    return 0;

}