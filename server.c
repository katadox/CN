#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define PORT 12345

int main(){
    int server_fd,new_sock;
    struct sockaddr_in address;
    socklen_t addrlen=sizeof(address);
    char buffer[1024]={0};
    char *msg="from server hi";

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    listen(server_fd,3);

    printf("server is listening.....\n");

    new_sock=accept(server_fd,(struct sockaddr *)&address,&addrlen);

    read(new_sock,buffer,1024);
    printf("from client: %s",buffer);

    send(new_sock,msg,strlen(msg),0);

    close(new_sock);
    close(server_fd);
    return 0;



}