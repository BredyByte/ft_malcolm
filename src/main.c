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

int args_validate_and_assign() {
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

    //if (args_validate_and_assign(arguments) != 0) return 1;

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
