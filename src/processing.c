#include "malcolm.h"

void wait_for_arp_request(t_network_data *data) {
    int sockfd;
    struct sockaddr_ll sa;
    socklen_t sa_len = sizeof(sa);
    unsigned char buffer[2048];

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    strncpy(ifr.ifr_name, data->interface_name, IFNAMSIZ-1);
    if (ioctl(sockfd, SIOCGIFINDEX, &ifr) == -1) {
        perror("IOCTL failed");
        close(sockfd);
        exit(1);
    }

    memset(&sa, 0, sizeof(struct sockaddr_ll));
    sa.sll_ifindex = ifr.ifr_ifindex;

    printf("Waiting for ARP request on interface: %s\n", data->interface_name);


    while (1) {
        ssize_t len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&sa, &sa_len);
        if (len < 0) {
            perror("Recvfrom failed");
            close(sockfd);
            exit(1);
        }

        t_ethernet_header *eth_header = (t_ethernet_header *)buffer;
        t_arp_header *arp_header = (t_arp_header *)(buffer + sizeof(t_ethernet_header));

        // if ARP && ARP-request == 1
        if (ntohs(eth_header->ethertype) == ETH_P_ARP && ntohs(arp_header->operation) == 1) {

            char sender_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, arp_header->sender_ip, sender_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, arp_header->target_ip, target_ip, INET_ADDRSTRLEN);

            printf("Sender: %s\nTarget: %s\n", sender_ip, target_ip);
            printf("Victim: %s\nRoutere: %s\n", data->target_ip, data->source_ip);

            if (strcmp(sender_ip, data->target_ip) != 0 && strcmp(target_ip, data->source_ip) != 0)
                continue;

            printf("HELLO\n");
            break;
        }
    }

    close(sockfd);
}
