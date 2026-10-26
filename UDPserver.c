#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345

int main() {
    int s;
    char buffer[1024];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server running...\n");

    recvfrom(s, buffer, sizeof(buffer), 0,
             (struct sockaddr *)&client, &len);

    printf("Client: %s\n", buffer);

    char *msg = "Hello from UDP Server";

    sendto(s, msg, strlen(msg) + 1, 0,
           (struct sockaddr *)&client, len);

    close(s);
    return 0;
}