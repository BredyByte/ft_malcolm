// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <netinet/in.h>
// #include <netinet/ether.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <unistd.h>
// #include <net/if.h>
// #include <linux/if_packet.h>

// #define BUF_SIZE 2048

// // ARP Header
// struct ether_arp {
//     uint16_t arp_hrd;     // hardware type
//     uint16_t arp_pro;     // protocol type
//     uint8_t  arp_hln;     // hardware address length
//     uint8_t  arp_pln;     // protocol address length
//     uint16_t arp_op;      // operation (1 - request, 2 - reply)
//     uint8_t  arp_sha[6];  // sender hardware address (MAC)
//     uint8_t  arp_spa[4];  // sender protocol address (IP)
//     uint8_t  arpTha[6];   // target hardware address (MAC)
//     uint8_t  arp_tpa[4];  // target protocol address (IP)
// };

// // Main function
// int main() {
//     int sock;
//     struct sockaddr_ll sa;
//     unsigned char buffer[BUF_SIZE];
//     struct ether_header *eth_header;
//     struct ether_arp *arp_header;

//     // create raw-socket to intercept
//     sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
//     if (sock < 0) {
//         perror("Socket creation failed");
//         return 1;
//     }

//     while (1) {
//         // getting package
//         int n = recvfrom(sock, buffer, BUF_SIZE, 0, NULL, NULL);
//         if (n < 0) {
//             perror("Recvfrom failed");
//             close(sock);
//             return 1;
//         }

//         eth_header = (struct ether_header *)buffer;
//         arp_header = (struct ether_arp *)(buffer + sizeof(struct ether_header));

//         // check if the type if ARP
//         if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
//             // Check request - 1 or response - 2 type
//             if (ntohs(arp_header->arp_op) == 1) {
//                 printf("Received ARP Request\n");
//                 printf("Sender MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
//                         arp_header->arp_sha[0], arp_header->arp_sha[1],
//                         arp_header->arp_sha[2], arp_header->arp_sha[3],
//                         arp_header->arp_sha[4], arp_header->arp_sha[5]);
//                 printf("Sender IP: %d.%d.%d.%d\n",
//                         arp_header->arp_spa[0], arp_header->arp_spa[1],
//                         arp_header->arp_spa[2], arp_header->arp_spa[3]);
//             }
//         }
//     }

//     close(sock);
//     return 0;
// }
