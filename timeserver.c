#include <stdio.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), {INADDR_ANY}};
    socklen_t len = sizeof(addr);
    char buf[64];

    bind(sock, (struct sockaddr*)&addr, len);
    printf("UDP Time Server running on port 8080...\n");

    while (1) {
        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
        
        time_t now = time(NULL);
        strcpy(buf, ctime(&now)); // Get current readable time
        
        sendto(sock, buf, strlen(buf) + 1, 0, (struct sockaddr*)&addr, len);
    }
    return 0;
}