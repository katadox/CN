#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int s, n;
    struct sockaddr_in server;
    char file[100], buffer[1024];

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *)&server, sizeof(server));

    printf("Enter filename: ");
    scanf("%99s", file);

    send(s, file, strlen(file) + 1, 0);

    while ((n = recv(s, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        buffer[n] = '\0';
        printf("%s", buffer);
    }

    close(s);
    return 0;
}