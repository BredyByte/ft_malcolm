#include "malcolm.h"

static int resolve_ip(const char *hostname, char *ip_out) {
    struct addrinfo hints, *res;
    ft_memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        return 1; // Error in hostname resolution
    }

    struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
    ft_memcpy(ip_out, &ipv4->sin_addr, sizeof(struct in_addr));

    freeaddrinfo(res);
    return 0;
}

static int mac_str_to_bytes(const char *mac_str, uint8_t *mac_bytes) {
    if (sscanf(mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &mac_bytes[0], &mac_bytes[1], &mac_bytes[2],
               &mac_bytes[3], &mac_bytes[4], &mac_bytes[5]) != 6) {
        fprintf(stderr, "Error: Invalid MAC address format: %s\n", mac_str);
        return -1;
    }
    return 0;
}


static int is_valid_mac(const char *mac) {
    if (mac == NULL || *mac == '\0') {
        return 0;
    }

    int segments = 0;
    const char *ptr = mac;

    while (*ptr != '\0') {
        // Check first sigment
        if (!ft_isxdigit(*ptr)) {
            return 0;
        }
        ptr++;

        // Check second sigment
        if (!ft_isxdigit(*ptr)) {
            return 0;
        }
        ptr++;

        if (*ptr == ':') {
            ptr++;
            segments++;
        } else if (*ptr == '\0') {
            segments++;
        } else {
            return 0;
        }
    }

    // MAC has to have 6 segments
    return segments == 6;
}

int args_validate(const char **argv, t_network_data *data) {
    const char *source_ip = argv[0];
    const char *source_mac = argv[1];
    const char *target_ip = argv[2];
    const char *target_mac = argv[3];

    // Validate IP addresses based on active flags
    if (data->f_resolve) {
        // Hostname resolution and decimal notation for source and target IPs
        if (resolve_ip(source_ip, (char *)data->source_ip) != 0) {
            fprintf(stderr, "Error: Invalid resolution IP address for source IP: %s\n", source_ip);
            return 1;
        }
        if (resolve_ip(target_ip, (char *)data->target_ip) != 0) {
            fprintf(stderr, "Error: Invalid resolution IP address for target IP: %s\n", target_ip);
            return 1;
        }
    } else {
        // Standard IPv4 validation
        if (inet_pton(AF_INET, source_ip, data->source_ip) != 1) {
            fprintf(stderr, "Error: Invalid IPv4 source address: %s\n", source_ip);
            return 1;
        }
        if (inet_pton(AF_INET, target_ip, data->target_ip) != 1) {
            fprintf(stderr, "Error: Invalid IPv4 target address: %s\n", target_ip);
            return 1;
        }
    }

    // Validate MAC addresses
    if (!is_valid_mac(source_mac)) {
        fprintf(stderr, "Error: Invalid source MAC address: %s\n", source_mac);
        return 1;
    }
    if (!is_valid_mac(target_mac)) {
        fprintf(stderr, "Error: Invalid target MAC address: %s\n", target_mac);
        return 1;
    }
    if (mac_str_to_bytes(source_mac, data->source_mac) == -1 ||
        mac_str_to_bytes(target_mac, data->target_mac) == -1) {
        fprintf(stderr, "Error: Failed to convert MAC addresses.\n");
        return 1;
    }

    return 0;
}
