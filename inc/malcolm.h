#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <sys/ioctl.h>
#include "../assets/libft/inc/libft.h"


// Ethernet header
typedef struct __attribute__((packed)) {
    uint8_t dest_mac[6];     // Destination MAC address
    uint8_t src_mac[6];      // Source MAC address
    uint16_t ethertype;      // Protocol type (e.g. 0x0806 for ARP)
} t_ethernet_header;

// ARP header
typedef struct __attribute__((packed)) {
    uint16_t htype;          // Hardware Type (1 for Ethernet)
    uint16_t ptype;          // Protocol Type (0x0800 for IPv4)
    uint8_t hlen;            // MAC Address Length
    uint8_t plen;            // IP Address Length
    uint16_t operation;      // Operation (1 for ARP Request, 2 for ARP Reply)
    uint8_t sender_mac[6];   // Sender's MAC address
    uint8_t sender_ip[4];    // Sender's IP Address's
    uint8_t target_mac[6];   // MAC Address recipient
    uint8_t target_ip[4];    // IP address of the recipient
} t_arp_header;

typedef struct {
    char source_ip[INET_ADDRSTRLEN];  // Source IP address
    char source_mac[18];              // Source MAC address
    char target_ip[INET_ADDRSTRLEN];  // Target IP address
    char target_mac[18];              // Target MAC address
    char interface_name[IF_NAMESIZE]; // Network interface name
} t_network_data;

int validate(const char** argv, t_network_data *data);
void wait_for_arp_request(t_network_data *data);

#endif
