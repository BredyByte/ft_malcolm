#include "malcolm.h"

t_network_data global_data;

static void handle_sigint(int sig) {
    (void) sig;

    printf("\nCaught SIGINT (Ctrl+C). Cleaning up...\n");

    if (global_data.sockfd != -1)
        close(global_data.sockfd);

    exit(0);
}

static int check_available_interface(void) {
    struct ifaddrs *ifaddr, *ifa;
    char ipstr[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        return 1;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET && (ifa->ifa_flags & IFF_UP)
            && !(ifa->ifa_flags & IFF_LOOPBACK)
            && !(ifa->ifa_flags & IFF_NOARP)) {
            ft_memcpy(ipstr, ifa->ifa_name, IFNAMSIZ);
            break;
        }
    }

    if (ft_strlen(ipstr) > 0) {
        printf("\nFound active interface:\n");
        printf("  Interface Name: %s\n", ifa->ifa_name);
        printf("  IP: %s\n", ipstr);
        printf("*\n*\n");
    }
    else {
    	freeifaddrs(ifaddr);
		return 1;
    }

    freeifaddrs(ifaddr);
    return 0;
}

int is_valid_ip(const char *ip_addr) {
    if (inet_addr((const char*)ip_addr) == INADDR_NONE) {
        return 0;
    }
    return 1;
}

int is_valid_mac(const char *mac_addr) {
    if (mac_addr == NULL || *mac_addr == '\0') {
        return 1;
    }

    int segments = 0;
    const char *ptr = mac_addr;

    if (ft_strlen(ptr) != 17) {
        return 1;
    }

    while (*ptr != '\0') {
        // Check first sigment
        if (!ft_isxdigit(*ptr)) {
            return 1;
        }
        ptr++;

        // Check second sigment
        if (!ft_isxdigit(*ptr)) {
            return 1;
        }
        ptr++;

        if (*ptr == ':') {
            ptr++;
            segments++;
        } else if (*ptr == '\0') {
            segments++;
        } else {
            return 1;
        }
    }

    // MAC has to have 6 segments
    return (segments == ETH_ALEN) ? 0 : 1;
}

int convert_ip_to_byte(const char *ip_str, uint8_t *ip_bytes) {
    if (ip_str == NULL) {
        fprintf(stderr, "\nInvalid IP address format: input is NULL\n\n");
        return 1;
    }

    if (ft_strlen(ip_str) == 0) {
        fprintf(stderr, "\nInvalid IP address format: input is an empty string\n\n");
        return 1;
    }

    in_addr_t ip = inet_addr(ip_str);
    if (ip == INADDR_NONE) {
        fprintf(stderr, "\nInvalid IP address format: %s\n\n", ip_str);
        return 1;
    }

    uint8_t *ptr = (uint8_t *)&ip;
    for (int i = 0; i < 4; i++) {
        ip_bytes[i] = ptr[i];
    }

    return 0;
}

unsigned char hex_char_to_byte(char c, int *error) {
    if (c >= '0' && c <= '9') {
        return (unsigned char)(c - '0');
    } else if (c >= 'a' && c <= 'f') {
        return (unsigned char)(c - 'a' + 10);
    } else if (c >= 'A' && c <= 'F') {
        return (unsigned char)(c - 'A' + 10);
    } else {
        *error = 1;
        return 0;
    }
}

int convert_mac_to_byte(const char *mac_str, unsigned char *mac_bytes) {
    if (mac_str == NULL || mac_bytes == NULL) {
        fprintf(stderr, "\nInvalid input: NULL pointer provided\n");
        return 1;
    }

    int byte_index = 0;
    int str_index = 0;
    int error = 0;


    if (strlen(mac_str) < 17) {
        fprintf(stderr, "\nInvalid MAC address format: %s\n", mac_str);
        return 1;
    }

    while (mac_str[str_index] && byte_index < 6) {
        if (mac_str[str_index] == ':') {
            str_index++;
            continue;
        }

        unsigned char high_nibble = hex_char_to_byte(mac_str[str_index], &error);
        unsigned char low_nibble = hex_char_to_byte(mac_str[str_index + 1], &error);

        if (error) {
            fprintf(stderr, "\nInvalid character in MAC address: %c\n", mac_str[str_index]);
            return 1;
        }

        if (mac_str[str_index + 1] == '\0') {
            fprintf(stderr, "\nIncomplete MAC address at index %d\n", str_index);
            return 1;
        }

        mac_bytes[byte_index++] = (high_nibble << 4) | low_nibble;
        str_index += 2;
    }

    if (byte_index != 6) {
        fprintf(stderr, "\nInvalid MAC address format: not enough bytes\n");
        return 1;
    }

    return 0;
}

int args_validate_and_assign(const char **arguments) {
    const char *source_ip = arguments[0];
    const char *target_ip = arguments[2];
    const char *source_mac = arguments[1];
    const char *target_mac = arguments[3];

    // Check ip's validation
    if (!is_valid_ip(source_ip)) {
        fprintf(stderr, "\n Error on check: Invalid source IP address format: %s\n\n", (const char*)source_ip);
        return 1;
    }
    if (!is_valid_ip(target_ip)) {
        fprintf(stderr, "\n Error on check: Invalid target IP address format: %s\n\n", (const char*)target_ip);
        return 1;
    }
    // Check mac's validation
    if (is_valid_mac(source_mac) != 0) {
        fprintf(stderr, "\n Error on check: Invalid source MAC address format: %s\n\n", (const char*)source_mac);
        return 1;
    }
    if (is_valid_mac(target_mac) != 0) {
        fprintf(stderr, "\n Error on check: Invalid target MAC address format: %s\n\n", (const char*)target_mac);
        return 1;
    }

    // Changing IPs to bytes and assigning to global structure
    if (convert_ip_to_byte(source_ip, global_data.source_ip) != 0
        || convert_ip_to_byte(target_ip, global_data.target_ip) != 0) {
        return 1;
    }

    // Changing IPs to bytes and assigning to global structure
    if (convert_mac_to_byte(source_mac, global_data.source_mac) != 0
        || convert_mac_to_byte(target_mac, global_data.target_mac) != 0) {
        return 1;
    }

    return 0;
}

int check_args(int argc, char *argv[]) {
    // Process options and arguments
    int opt;
    while ((opt = getopt(argc, argv, "vh")) != -1) {
        switch (opt) {
            case 'v':
                global_data.f_verbo = true;
                break;
            case 'h':
            default:
                print_usage();
                return 1;
        }
    }

    // Ensure remaining arguments match the required format
    if (argc - optind != 4) {
        print_usage();
        return 1;
    }

    // Extract and validate the remaining arguments
    const char **arguments = (const char **)&argv[optind];

    for (int i = 0; arguments[i] != NULL; i++) {
        printf("arg: %s\n", arguments[i]);
    }

    if (args_validate_and_assign(arguments) != 0) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (getuid() != 0) {
		fprintf(stderr,"Root privileges are required to run ft_malcolm.\n");
        return 1;
    }

    if (check_args(argc, argv) != 0) return 1;

    if (check_available_interface() != 0) {
        fprintf(stderr, "Error: Could not find a free network interface.\n");
        return 1;
    }

    if (global_data.f_verbo)
        print_arguments_data();

    signal(SIGINT, handle_sigint);

    //wait_for_arp_request(&data);

    return 0;
}
