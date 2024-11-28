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

void print_headers(const void *buffer) {
    const unsigned char *buf = (const unsigned char *)buffer;

    // Ethernet-header
    const struct ethhdr *eth_header = (const struct ethhdr *)buf;
    printf("Ethernet Header:\n");
    printf("  Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth_header->h_dest[0], eth_header->h_dest[1], eth_header->h_dest[2],
           eth_header->h_dest[3], eth_header->h_dest[4], eth_header->h_dest[5]);
    printf("  Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           eth_header->h_source[0], eth_header->h_source[1], eth_header->h_source[2],
           eth_header->h_source[3], eth_header->h_source[4], eth_header->h_source[5]);
    printf("  Ethertype: 0x%04x\n", ntohs(eth_header->h_proto));

    // ARP-header
    const struct ether_arp *arp_header = (const struct ether_arp *)(buf + sizeof(struct ethhdr));
    printf("ARP Header:\n");
    printf("  Hardware Type: 0x%04x\n", ntohs(arp_header->ea_hdr.ar_hrd));
    printf("  Protocol Type: 0x%04x\n", ntohs(arp_header->ea_hdr.ar_pro));
    printf("  Hardware Address Length: %u\n", arp_header->ea_hdr.ar_hln);
    printf("  Protocol Address Length: %u\n", arp_header->ea_hdr.ar_pln);
    printf("  Operation: 0x%04x\n", ntohs(arp_header->ea_hdr.ar_op));

    // Sender MAC and IP
    char sender_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, arp_header->arp_spa, sender_ip, sizeof(sender_ip));
    printf("  Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp_header->arp_sha[0], arp_header->arp_sha[1], arp_header->arp_sha[2],
           arp_header->arp_sha[3], arp_header->arp_sha[4], arp_header->arp_sha[5]);
    printf("  Sender IP: %s\n", sender_ip);

    // Target MAC and IP
    char target_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, arp_header->arp_tpa, target_ip, sizeof(target_ip));
    printf("  Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           arp_header->arp_tha[0], arp_header->arp_tha[1], arp_header->arp_tha[2],
           arp_header->arp_tha[3], arp_header->arp_tha[4], arp_header->arp_tha[5]);
    printf("  Target IP: %s\n", target_ip);

    printf("*\n*\n");
}

void print_usage() {
    printf("Usage: ./ft_malcolm [OPTIONS] <source_ip> <source_mac> <target_ip> <target_mac>\n");
    printf("\nOptions:\n");
    printf("  -v         Enable verbose mode\n");
    printf("  -h         Show this help message\n");
}

