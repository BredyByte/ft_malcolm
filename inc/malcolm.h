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

typedef struct  s_eth_packe {
    struct ethhdr           ethernet_header;
    struct ether_arp        arp_packet;
}   t_eth_packet;

typedef struct s_network_data {
    uint8_t             source_ip[INET4_LEN];     // Source IP address
	uint8_t             source_mac[ETH_ALEN];     // Source MAC in correct format for Ether and ARP headers
    uint8_t             target_ip[INET4_LEN];     // Target IP address
	uint8_t             target_mac[ETH_ALEN];     // Target MAC in correct format for Ether and ARP headers
    struct ethhdr       *ethernet_header;
	struct ether_arp    *arp_packet;
	struct arphdr		*arp_header;
    int                 sockfd;
    bool                f_verbo;                     // Flag for verbose mode [bonus]
}   t_network_data;

extern t_network_data global_data;

// Data visualization
// void print_arguments_data(const t_network_data *data);  // Print args. in correct format
// void print_headers(const unsigned char *buffer);        // Print Eth/ARP headers
void print_usage();                                     // Print usage function

// // Arguments validation and parse
// int args_validate(const char** argv, t_network_data *data);

// // ARP-request listening and response with headers preparation
// void wait_for_arp_request(t_network_data *data);

// Libft utils
void    *ft_memcpy(void *dest, const void *src, size_t len);
void    ft_bzero(void *s, size_t n);
void    *ft_memset(void *b, int c, size_t len);
int     ft_isxdigit(char c);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
size_t  ft_strlen(const char *s);


#endif
