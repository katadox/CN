#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 12345

int main(){
    int sock=0;  //sock is a file descriptor for the socket
    struct sockaddr_in serv_addr; //serv_addr is a structure that holds the address information for the server socket
    char*msg="hello from client";
    char buffer[1024]={0}; //buffer is a character array that will hold the data received from the server

    sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0){
        printf("socket creation error\n");
        return -1;
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        printf("connection failed\n");
        return -1;
    }

    send(sock,msg,strlen(msg),0);
    printf("message sent to server: %s\n",msg);

    read(sock,buffer,1024);
    printf("message from server: %s\n",buffer);
    close(sock);
    return 0;


}