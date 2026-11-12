#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>

#define PORT 12345

int main(){
    int sock=0;
    struct sockaddr_in server_addrin;
    char buffer[1024];
    char *msg="hi from client";

    sock=socket(AF_INET,SOCK_STREAM,0);

    server_addrin.sin_family=AF_INET;
    server_addrin.sin_port=htons(PORT);
    server_addrin.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(sock,(struct sockaddr *)&server_addrin,sizeof(server_addrin));

    send(sock,msg,sizeof(msg),0);

    read(sock,buffer,1024);
    printf("msg from server:%s",buffer);

    close(sock);
    return 0;
}