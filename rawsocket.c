#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>

int main()
{
    int sockfd;
    char buffer[65536];
    struct sockaddr addr;
    socklen_t addr_len = sizeof(addr);

    // struct iphdr - structure contains all the fields of an IP packet like Version, Header Length, TTL, Protocol, Source IP, Destination IP
    struct iphdr *ip;

    // Create raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sockfd < 0)
    {
        printf("Socket Creation Failed\n");
        return 1;
    }

    printf("Packet Capturing Started...\n");

    while (1)
    {
        // Receive packet
        recvfrom(sockfd, buffer, sizeof(buffer), 0, &addr, &addr_len);

        // Point to IP header
        ip = (struct iphdr *)buffer;

        printf("\nPacket Received\n");

        // inet_ntoa() - converts an IP address from binary format into human-readable dotted decimal format.
        printf("Source IP     : %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));
        printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
        printf("Protocol      : %d\n", ip->protocol);
    }

    close(sockfd);
    return 0;
}
