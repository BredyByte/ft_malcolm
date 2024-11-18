#include <stdint.h>
#include <stdio.h>

#define BUF_SIZE 42
#define ETH_ARP 0x0806

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

int main(void) {
	printf("Size ethernet_header: %zu\n", sizeof(t_ethernet_header));
	printf("Size arp_header: %zu\n", sizeof(t_arp_header));
	return 0;
}
