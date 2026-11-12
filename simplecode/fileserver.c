#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0), n;
    struct sockaddr_in addr = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    char fname[100], buf[1024];

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Enter filename: ");
    scanf("%s", fname);
    send(sock, fname, strlen(fname), 0);

    while ((n = recv(sock, buf, sizeof(buf) - 1, 0)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    close(sock);
    return 0;
}