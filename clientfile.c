#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 12345

int main(){
    int sockfd,n;
    struct sockaddr_in server;

    char filename[100];
    char buffer[1024];

    sockfd=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    printf("filename:");
    scanf("%s",filename);

    send(sockfd,filename,strlen(filename)+1,0);

    while((n=recv(sockfd,buffer,sizeof(buffer)-1,0))>0){
        buffer[n]='\0';
        printf("%s",buffer);
    }
    close(sockfd);
    return 0;
}