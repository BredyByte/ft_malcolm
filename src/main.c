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

    if (getifaddrs(&ifaddr) == -1) return -1;

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

int is_valid_ip (const char *ip_addr) {
    if (inet_addr((const char*)ip_addr) == INADDR_NONE) {
    fprintf(stderr, "\n Invalid IP address format: %s\n\n", ( const char*)ip_addr);
        return 1;
    }
    return 0;
}

int is_valid_mac(const char *mac_addr) {
    if (mac_addr == NULL || *mac_addr == '\0') {
        return 0;
    }

    int segments = 0;
    const char *ptr = mac_addr;

    if (ft_strlen(ptr) != 17) {
        return 0;
    }

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
    return segments == ETH_ALEN;
}


int args_validate_and_assign(const char **arguments) {
    const char *source_ip = arguments[0];
    const char *target_ip = arguments[2];
    const char *source_mac = arguments[1];
    const char *target_mac = arguments[3];

    if (is_valid_ip(source_ip) != 0 || is_valid_ip(target_ip) != 0) return 1;

    if (!is_valid_mac(source_mac)) {
        fprintf(stderr, "\n Invalid source MAC address format: %s\n\n", (const char*)source_mac);
        return 1;
    }
    if (!is_valid_mac(target_mac)) {
        fprintf(stderr, "\n Invalid target MAC address format: %s\n\n", (const char*)target_mac);
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

    if (args_validate_and_assign(arguments) != 0) return 1;

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
        //print_arguments_data();

    signal(SIGINT, handle_sigint);

    //wait_for_arp_request(&data);

    return 0;
}
