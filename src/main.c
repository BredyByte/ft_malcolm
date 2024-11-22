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

int main(int argc, const char **argv) {
    t_network_data data;
    global_data = &data;

    ft_memset(&data, 0, sizeof(t_network_data));
    data.sockfd = -1;

    signal(SIGINT, handle_sigint);

	// Arguments Validation
    if (argc != 5) {
        fprintf(stderr, "Usage: <source_ip> <source_mac> <target_ip> <target_mac>\n");
        return 1;
    }

    if (args_validate(argv, &data) != 0) {
        return 1;
    }

    if (check_available_interface(&data) != 0) {
        fprintf(stderr, "Error: Could not find a free network interface.\n");
        return 1;
    }

    wait_for_arp_request(&data);

    return 0;
}
