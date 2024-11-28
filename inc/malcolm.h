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

// /* Ethernet frame header */
// typedef struct {
//    uint8_t dest_addr[ETH_ALEN]; /* Destination hardware address */
//    uint8_t src_addr[ETH_ALEN];  /* Source hardware address */
//    uint16_t frame_type;   /* Ethernet frame type */
// } __attribute__((packed)) ether_hdr;

// /* Ethernet ARP packet from RFC 826 */
// typedef struct {
//    uint16_t htype;   /* Format of hardware address */
//    uint16_t ptype;   /* Format of protocol address */
//    uint8_t hlen;    /* Length of hardware address */
//    uint8_t plen;    /* Length of protocol address */
//    uint16_t op;    /* ARP opcode (command) */
//    uint8_t sha[ETH_ALEN];  /* Sender hardware address */
//    uint32_t spa;   /* Sender IP address */
//    uint8_t tha[ETH_ALEN];  /* Target hardware address */
//    uint32_t tpa;   /* Target IP address */
// } __attribute__((packed)) arp_ether_ipv4;

typedef struct  s_eth_packe {
    struct ethhdr           ethernet_header;
    struct ether_arp        arp_packet;
}   t_eth_packet;

typedef struct s_network_data {
    uint8_t             source_ip[INET4_LEN];   // Source IP address
	uint8_t             source_mac[ETH_ALEN];   // Source MAC in correct format for Ether and ARP headers
    uint8_t             target_ip[INET4_LEN];   // Target IP address
	uint8_t             target_mac[ETH_ALEN];   // Target MAC in correct format for Ether and ARP headers
    struct ethhdr       *ethernet_header;
	struct ether_arp    *arp_packet;
	struct arphdr		*arp_header;
    int                 sockfd;
    bool                f_verbo;                // Flag for verbose mode [bonus]
}   t_network_data;

extern t_network_data global_data;

// Data visualization
void print_arguments_data();                    // Print args. in correct format
void print_headers(const void *buffer);         // Print Eth/ARP headers
void print_usage();                             // Print usage function

// Libft utils
void    *ft_memcpy(void *dest, const void *src, size_t n);
void    ft_bzero(void *s, size_t n);
void    *ft_memset(void *b, int c, size_t len);
int     ft_isxdigit(char c);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
size_t  ft_strlen(const char *s);


#endif
