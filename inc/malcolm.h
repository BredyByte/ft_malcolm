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
#include <errno.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdint.h>
#include <ctype.h>

#include "../assets/libft/inc/libft.h"

#define INET4_LEN 4
#define BUFFER_SIZE 42
#define SO_BINDTODEVICE 25

// Ethernet header
typedef struct __attribute__((packed)) {
    uint8_t dest_mac[ETH_ALEN];     // Destination MAC address
    uint8_t src_mac[ETH_ALEN];      // Source MAC address
    uint16_t ethertype;      // Protocol type (e.g. 0x0806 for ARP)
} t_ethernet_header;

// ARP header
typedef struct __attribute__((packed)) {
    uint16_t htype;                 // Hardware Type (1 for Ethernet)
    uint16_t ptype;                 // Protocol Type (0x0800 for IPv4)
    uint8_t hlen;                   // MAC Address Length
    uint8_t plen;                   // IP Address Length
    uint16_t operation;             // Operation (1 for ARP Request, 2 for ARP Reply)
    uint8_t sender_mac[ETH_ALEN];   // Sender's MAC address
    uint8_t sender_ip[INET4_LEN];   // Sender's IP Address's
    uint8_t target_mac[ETH_ALEN];   // MAC Address recipient
    uint8_t target_ip[INET4_LEN];   // IP address of the recipient
} t_arp_header;

typedef struct {
    uint8_t source_ip[INET4_LEN];     // Source IP address
	uint8_t source_mac[ETH_ALEN];     // Source MAC in correct format for Ether and ARP headers
    uint8_t target_ip[INET4_LEN];     // Target IP address
	uint8_t target_mac[ETH_ALEN];     // Target MAC in correct format for Ether and ARP headers
    char interface_name[IF_NAMESIZE + 1]; // Network interface name
    uint32_t interface_index;            // Network interface index
    int  sockfd;
    bool f_verbo;                     // Flag for verbose mode [bonus]
    bool f_resolve;                      // Flag for hostname resolution and decimal notation for IPv4 [bonus]
} t_network_data;

// Data visualization
void print_arguments_data(const t_network_data *data);  // Print args. in correct format
void print_headers(const unsigned char *buffer);        // Print Eth/ARP headers
void print_usage();                                     // Print usage function

// Arguments validation and parse
int args_validate(const char** argv, t_network_data *data);

// ARP-request listening and response with headers preparation
void wait_for_arp_request(t_network_data *data);

#endif
