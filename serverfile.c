#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 12345

int main(){
    int server_fd,Client_fd;
    struct  sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char filename[100];
    char buffer[1024];
    FILE *fp;

    server_fd=socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    bind(server_fd,(struct sockaddr *)&server,sizeof(server));

    listen(server_fd,1); //listen() syntax is used to listen for incoming connections on the socket. It takes two arguments: the file descriptor of the socket and the maximum number of pending connections that can be queued. It returns 0 on success and -1 on failure.
    printf("file server is runnig\n");

    Client_fd=accept(server_fd,(struct sockaddr *)&client,&len); //accept() syntax is used to accept an incoming connection on the socket. It takes three arguments: the file descriptor of the socket, a pointer to a structure that will hold the address information of the connecting client, and a pointer to a variable that will hold the size of the address structure. It returns a new file descriptor for the accepted connection.
    printf("client connected\n");

    recv(Client_fd,filename,sizeof(filename),0); //recv() syntax is used to receive data from the socket. It takes four arguments: the file descriptor of the socket, a pointer to a buffer where the data will be stored, the maximum number of bytes to read, and flags (set to 0 for default behavior). It returns the number of bytes received.
    printf("file name is %s\n",filename);
    fp=fopen(filename,"r");

    if(fp==NULL){
        printf("file not found\n");
        send(Client_fd,"file not found",sizeof("file not found"),0);
    }else{
        snprintf(buffer,sizeof(buffer),"server PID%d\n",getpid());
        send(Client_fd,buffer,strlen(buffer),0);

        while(fgets(buffer,sizeof(buffer),fp)!=NULL){  //fget() syntax is used to read a line from the file. It takes three arguments: a pointer to a buffer where the line will be stored, the maximum number of bytes to read, and a pointer to the file stream. It returns a pointer to the buffer on success and NULL on failure or end of file.
        send(Client_fd,buffer,sizeof(buffer),0);
        }
        fclose(fp);
    }

    close(Client_fd);
    close(server_fd);

    return 0;
}