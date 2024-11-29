#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include <ctype.h>

#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/if_ether.h>
#include <errno.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>
#include <signal.h>

#define INET4_LEN 4
#define BUFFER_SIZE 42

// Ethernet header
typedef struct __attribute__((packed)) {
    uint8_t dest_mac[ETH_ALEN];     // Destination MAC address
    uint8_t src_mac[ETH_ALEN];      // Source MAC address
    uint16_t ethertype;             // Protocol type (e.g. 0x0806 for ARP)
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

typedef struct s_network_data {
    uint8_t source_ip[INET4_LEN];     // Source IP address
	uint8_t source_mac[ETH_ALEN];     // Source MAC in correct format for Ether and ARP headers
    uint8_t target_ip[INET4_LEN];     // Target IP address
	uint8_t target_mac[ETH_ALEN];     // Target MAC in correct format for Ether and ARP headers
    int  sockfd;
    bool f_verbo;                     // Flag for verbose mode [bonus]
} t_network_data;

extern t_network_data global_data;

// Data visualization
void print_arguments_data();                        // Print args. in correct format
void print_headers(const unsigned char *buffer);    // Print Eth/ARP headers
void print_usage();                                 // Print usage function

// Libft utils
void    *ft_memcpy(void *dest, const void *src, size_t n);
void    ft_bzero(void *s, size_t n);
void    *ft_memset(void *b, int c, size_t len);
int     ft_isxdigit(char c);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
size_t  ft_strlen(const char *s);


#endif
