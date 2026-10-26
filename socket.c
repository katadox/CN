#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

int main()
{
    int sock;
    unsigned char buffer[65536];

    struct ethhdr *eth;
    struct iphdr *ip;

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

    if (sock < 0)
    {
        printf("Socket creation failed!\n");
        return 1;
    }

    printf("Capturing packets... Press Ctrl+C to stop.\n");

    while (1)
    {
        int len = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);

        if (len < 0)
            continue;

        eth = (struct ethhdr *)buffer;
        ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));

        printf("\nPacket Length: %d\n", len);

        printf("Source MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
               eth->h_source[0], eth->h_source[1], eth->h_source[2],
               eth->h_source[3], eth->h_source[4], eth->h_source[5]);

        printf("Destination MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
               eth->h_dest[0], eth->h_dest[1], eth->h_dest[2],
               eth->h_dest[3], eth->h_dest[4], eth->h_dest[5]);

        printf("Ethernet Protocol: 0x%04X\n", ntohs(eth->h_proto));

        if (ntohs(eth->h_proto) == ETH_P_IP && len >= sizeof(struct ethhdr) + sizeof(struct iphdr))
        {
            printf("Source IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->saddr));
            printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));

            if (ip->protocol == IPPROTO_TCP)
            {
                struct tcphdr *tcp = (struct tcphdr *)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);

                printf("Protocol: TCP\n");
                printf("Source Port: %d\n", ntohs(tcp->source));
                printf("Destination Port: %d\n", ntohs(tcp->dest));
            }
            else if (ip->protocol == IPPROTO_UDP)
            {
                struct udphdr *udp = (struct udphdr *)(buffer + sizeof(struct ethhdr) + ip->ihl * 4);

                printf("Protocol: UDP\n");
                printf("Source Port: %d\n", ntohs(udp->source));
                printf("Destination Port: %d\n", ntohs(udp->dest));
            }
            else if (ip->protocol == IPPROTO_ICMP)
            {
                printf("Protocol: ICMP\n");
            }
            else
            {
                printf("Other IP Protocol\n");
            }
        }
    }

    close(sock);
    return 0;
}