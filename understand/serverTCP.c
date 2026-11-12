#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 12345

int main() {
    int server_fd,new_socket;  //server_fd,new_socket are file descriptors for the server and client sockets
    struct sockaddr_in address; //address is a structure that holds the address information for the server socket
    int addrlen=sizeof(address);
    char buffer[1024]={0};  //buffer is a character array that will hold the data received from the client
    char *msg="hello from server";

    //reate a socket
    server_fd=socket(AF_INET,SOCK_STREAM,0);   //AF_INET,SOCK_STREAM,0 are parameters for the socket function that specify the address family(ipv4), socket type(tcp), and protocol 0-> for default protocol
    if(server_fd<0){     
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set the address information for the server socket
    memset(&address, 0, sizeof(address)); //memset is used to initialize the address structure to zero. It takes three arguments: a pointer to the memory block to be filled, the value to be set (0 in this case), and the number of bytes to be set (the size of the address structure).
    address.sin_family=AF_INET;  //specifies ipv4
    address.sin_addr.s_addr=INADDR_ANY;  //Means the server accepts connections through any available local network interface.
    address.sin_port=htons(PORT);  //htons converts the port number from host byte order to network byte order htons stands for "host to network short" and is used to ensure that the port number is in the correct byte order for network communication.

    //bind the socket to the address
    if(bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0){ //bind will bimd the socket to the specified address and port number. It takes three arguments: the file descriptor of the socket, a pointer to the address structure, and the size of the address structure.
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,3)<0){ //listen() is a system call that makes the socket ready to accept incoming connections. 3 represent it is the backlog value.It specifies the maximum number of pending connections that can be queued for acceptance.
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    printf("server is listening....\n");

    new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen);  //accept() is a system call that blocks the server until a client connects to the server. It takes three arguments: the file descriptor of the listening socket, a pointer to a structure that will hold the address information of the connecting client, and a pointer to a variable that will hold the size of the address structure. It returns a new file descriptor for the accepted connection.
    //erver_fd: Used for listening for connections.
    //new_socket: Used for actual communication with the connected client.

    read(new_socket,buffer,1024); //read() is a system call that reads data from the socket. It takes three arguments: the file descriptor of the socket, a pointer to a buffer where the data will be stored, and the maximum number of bytes to read. It returns the number of bytes read.
    printf("message from client: %s\n",buffer);

    send(new_socket,msg,strlen(msg),0); //send() is a system call that sends data to the socket. It takes four arguments: the file descriptor of the socket, a pointer to the data to be sent, the number of bytes to send, and flags (set to 0 for default behavior). It returns the number of bytes sent.
    close(new_socket);
    close(server_fd);
    return 0;
}