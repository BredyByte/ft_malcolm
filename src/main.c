#include "malcolm.h"

volatile t_network_data *global_data = NULL;

static void handle_sigint(int sig) {
    (void) sig;

    if (global_data) {
        printf("\nCaught SIGINT (Ctrl+C). Cleaning up...\n");

        if (global_data->sockfd != -1)
            close(global_data->sockfd);

        exit(0);
    }
}

static int check_available_interface(t_network_data *data) {
    struct ifaddrs *ifaddr, *ifa;
    char ipstr[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) return -1;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {

        // Skiping interfaces without IPv4 addresses OR with disabled status. IFF_UP == active
        if (ifa->ifa_addr == NULL || (ifa->ifa_flags & IFF_UP) == 0 || ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }

        void *addr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
        inet_ntop(AF_INET, addr, ipstr, sizeof(ipstr));

        if (ft_strncmp(ipstr, "127.", 4) == 0) {
            continue;
        }


        ft_strncpy(data->interface_name, ifa->ifa_name, IF_NAMESIZE);

        data->interface_index = if_nametoindex(data->interface_name);
        if (data->interface_index == 0) {
            dprintf(STDERR_FILENO, "Fail to get interface index cause: %s\n", strerror(errno));
            freeifaddrs(ifaddr);
            return -1;
        }

        printf("\nFound active interface:\n");
        printf("  Interface Name: %s\n", ifa->ifa_name);
        printf("  IP: %s\n", ipstr);
        printf("*\n*\n");


        freeifaddrs(ifaddr);
        return 0;
    }

    freeifaddrs(ifaddr);
    return -1;
}

int main(int argc, char *argv[]) {
    t_network_data data;
    global_data = &data;

    ft_memset(&data, 0, sizeof(t_network_data));
    data.sockfd = -1;

    if (getuid() != 0) {
		fprintf(stderr,"Root privileges are required to run ft_malcolm.\n");
        return 1;
    }

    signal(SIGINT, handle_sigint);

    // Process options and arguments
    int opt;
    while ((opt = getopt(argc, argv, "vndh")) != -1) {
        switch (opt) {
            case 'v':
                data.f_verbo = true;
                break;
            case 'n':
                if (data.f_decim) {
                    fprintf(stderr, "Error: -n cannot be used with -d.\n");
                    return 1;
                }
                data.f_host = true;
                break;
            case 'd':
                if (data.f_host) {
                    fprintf(stderr, "Error: -d cannot be used with -n.\n");
                    return 1;
                }
                data.f_decim = true;
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
    if (args_validate(arguments, &data) != 0) {
        return 1;
    }

    if (check_available_interface(&data) != 0) {
        fprintf(stderr, "Error: Could not find a free network interface.\n");
        return 1;
    }

    if (data.f_verbo)
        print_arguments_data(&data);

    wait_for_arp_request(&data);

    return 0;
}
