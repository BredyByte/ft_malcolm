#include "malcolm.h"

void print_arguments_data() {
    char source_ip_str[INET_ADDRSTRLEN];
    char target_ip_str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, global_data.source_ip, source_ip_str, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, global_data.target_ip, target_ip_str, INET_ADDRSTRLEN);

    printf("Parsed Argument Data:\n");
    printf("  Source IP: %s\n", source_ip_str);
    printf("  Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           global_data.source_mac[0], global_data.source_mac[1], global_data.source_mac[2],
           global_data.source_mac[3], global_data.source_mac[4], global_data.source_mac[5]);
    printf("  Target IP: %s\n", target_ip_str);
    printf("  Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           global_data.target_mac[0], global_data.target_mac[1], global_data.target_mac[2],
           global_data.target_mac[3], global_data.target_mac[4], global_data.target_mac[5]);

    printf("*\n*\n");
}

// void print_headers(const unsigned char *buffer) {
//     // Ethernet-header
//     const t_ethernet_header *eth_header = (const t_ethernet_header *)buffer;
//     printf("Ethernet Header:\n");
//     printf("  Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
//            eth_header->dest_mac[0], eth_header->dest_mac[1], eth_header->dest_mac[2],
//            eth_header->dest_mac[3], eth_header->dest_mac[4], eth_header->dest_mac[5]);
//     printf("  Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
//            eth_header->src_mac[0], eth_header->src_mac[1], eth_header->src_mac[2],
//            eth_header->src_mac[3], eth_header->src_mac[4], eth_header->src_mac[5]);
//     printf("  Ethertype: 0x%04x\n", ntohs(eth_header->ethertype));

//     // ARP-header
//     const t_arp_header *arp_header = (const t_arp_header *)(buffer + sizeof(t_ethernet_header));
//     printf("ARP Header:\n");
//     printf("  Hardware Type: 0x%04x\n", ntohs(arp_header->htype));
//     printf("  Protocol Type: 0x%04x\n", ntohs(arp_header->ptype));
//     printf("  Hardware Address Length: %u\n", arp_header->hlen);
//     printf("  Protocol Address Length: %u\n", arp_header->plen);
//     printf("  Operation: 0x%04x\n", ntohs(arp_header->operation));

//     // MAC и IP of sender
//     char sender_ip[INET_ADDRSTRLEN];
//     inet_ntop(AF_INET, arp_header->sender_ip, sender_ip, sizeof(sender_ip));
//     printf("  Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
//            arp_header->sender_mac[0], arp_header->sender_mac[1], arp_header->sender_mac[2],
//            arp_header->sender_mac[3], arp_header->sender_mac[4], arp_header->sender_mac[5]);
//     printf("  Sender IP: %s\n", sender_ip);

//     // MAC and IP of receiver
//     char target_ip[INET_ADDRSTRLEN];
//     inet_ntop(AF_INET, arp_header->target_ip, target_ip, sizeof(target_ip));
//     printf("  Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
//            arp_header->target_mac[0], arp_header->target_mac[1], arp_header->target_mac[2],
//            arp_header->target_mac[3], arp_header->target_mac[4], arp_header->target_mac[5]);
//     printf("  Target IP: %s\n", target_ip);

//     printf("*\n*\n");
// }

void print_usage() {
    printf("Usage: ./ft_malcolm [OPTIONS] <source_ip> <source_mac> <target_ip> <target_mac>\n");
    printf("\nOptions:\n");
    printf("  -v         Enable verbose mode\n");
    printf("  -h         Show this help message\n");
}

