#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s_fd = socket(AF_INET, SOCK_STREAM, 0), c_fd;
    struct sockaddr_in addr = {AF_INET, htons(8080), {INADDR_ANY}};
    char fname[100], buf[1024];

    bind(s_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(s_fd, 5);
    printf("Concurrent File Server running...\n");

    while (1) {
        c_fd = accept(s_fd, NULL, NULL); // NULL works if you don't need client IP

        if (fork() == 0) { // Child process handles the client
            close(s_fd);   // Child doesn't need the listening socket
            
            int n = recv(c_fd, fname, sizeof(fname) - 1, 0);
            fname[n] = '\0';

            FILE *fp = fopen(fname, "r");
            if (!fp) {
                send(c_fd, "File not found\n", 15, 0);
            } else {
                sprintf(buf, "Handled by Server PID: %d\n", getpid());
                send(c_fd, buf, strlen(buf), 0);

                while (fgets(buf, sizeof(buf), fp))
                    send(c_fd, buf, strlen(buf), 0);
                fclose(fp);
            }
            close(c_fd);
            exit(0); // Kill child when done
        }
        close(c_fd); // Parent closes client socket and goes back to accept()
    }
    return 0;
}