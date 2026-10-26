#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int s;
    char buffer[1024];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    char *msg = "Hello from UDP Client";

    sendto(s, msg, strlen(msg) + 1, 0,
           (struct sockaddr *)&server, len);

    recvfrom(s, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&server, &len);

    printf("Server: %s\n", buffer);

    close(s);
    return 0;
}