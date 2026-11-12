#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 12345

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serveraddr;
    socklen_t len;

    sockfd=socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(PORT);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    char *msg="hello from client";

    sendto(sockfd,msg,strlen(msg)+1,0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));  //sendto() syntax is used to send data to the socket. It takes six arguments: the file descriptor of the socket, a pointer to the data to be sent, the number of bytes to send, flags (set to 0 for default behavior), a pointer to a structure that holds the address information of the destination, and the size of the address structure. It returns the number of bytes sent.

    len=sizeof(serveraddr);

    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr *)&serveraddr,&len); //recvform() syntax is used to receive data from the socket. It takes six arguments: the file descriptor of the socket, a pointer to a buffer where the data will be stored, the maximum number of bytes to read, flags (set to 0 for default behavior), a pointer to a structure that will hold the address information of the sending client, and a pointer to a variable that will hold the size of the address structure. It returns the number of bytes received.
    printf("message from server: %s\n",buffer);

    close(sockfd);
    return 0;
}