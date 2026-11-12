#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    socklen_t len = sizeof(addr);
    char buf[64] = "TIME";

    sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr*)&addr, len);
    recvfrom(sock, buf, sizeof(buf), 0, NULL, NULL);
    
    printf("Server Time: %s", buf);
    return 0;
}