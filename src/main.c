#include "malcolm.h"

int get_free_interface(t_network_data *data) {
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

        printf("\nFound active interface: %s with IP %s\n", ifa->ifa_name, ipstr);
        printf("------------------------------------------\n\n");

        freeifaddrs(ifaddr);
        return 0;
    }

    freeifaddrs(ifaddr);
    return -1;
}

int main(int argc, const char **argv) {
    t_network_data data;

	// Arguments Validation
    if (argc != 5) {
        fprintf(stderr, "Usage: <source_ip> <source_mac> <target_ip> <target_mac>\n");
        return 1;
    }

    if (args_validate(argv, &data) != 0) {
        return 1;
    }

    // Initialization
    if (get_free_interface(&data) != 0) {
        fprintf(stderr, "Error: Could not find a free network interface.\n");
        return 1;
    }

    print_network_data(&data);

    wait_for_arp_request(&data);

	// Processing
	// Cleanup

    return 0;
}
