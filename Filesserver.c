#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main()
{
    int s, c;
    struct sockaddr_in a, b;
    socklen_t l = sizeof(b);
    char f[100], buf[1024];
    FILE *fp;

    s = socket(AF_INET, SOCK_STREAM, 0);
    a.sin_family = AF_INET;
    a.sin_port = htons(8080);
    a.sin_addr.s_addr = INADDR_ANY;

    bind(s, (void *)&a, sizeof(a));
    listen(s, 5);

    while (1)
    {
        c = accept(s, (void *)&b, &l);

        if (fork() == 0)
        {
            close(s);
            recv(c, f, sizeof(f), 0);
            fp = fopen(f, "r");

            sprintf(buf, "PID: %d\n", getpid());
            send(c, buf, strlen(buf), 0);

            if (fp == NULL)
                send(c, "File not found\n", 15, 0);
            else
            {
                while (fgets(buf, sizeof(buf), fp))
                    send(c, buf, strlen(buf), 0);
                fclose(fp);
            }

            close(c);
            return 0;
        }
        close(c);
        waitpid(-1, NULL, WNOHANG);
    }
}