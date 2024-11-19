#include "malcolm.h"

void print_network_data(const t_network_data *data) {
    char source_ip_str[INET_ADDRSTRLEN];
    char target_ip_str[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, data->source_ip, source_ip_str, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, data->target_ip, target_ip_str, INET_ADDRSTRLEN);

    printf("Network Data:\n");
    printf("----------------------------\n");
    printf("Source IP: %s\n", source_ip_str);
    printf("Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           data->source_mac[0], data->source_mac[1], data->source_mac[2],
           data->source_mac[3], data->source_mac[4], data->source_mac[5]);
    printf("Target IP: %s\n", target_ip_str);
    printf("Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           data->target_mac[0], data->target_mac[1], data->target_mac[2],
           data->target_mac[3], data->target_mac[4], data->target_mac[5]);
    printf("Interface Name: %s\n", data->interface_name);
    printf("----------------------------\n");
}

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

        printf("Found active interface: %s with IP %s\n", ifa->ifa_name, ipstr);
        printf("________________________________________________________________\n");

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

    if (validate(argv, &data) != 0) {
        return 1;
    }

    // Initialization
    if (get_free_interface(&data) != 0) {
        fprintf(stderr, "Error: Could not find a free network interface.\n");
        return 1;
    }

    print_network_data(&data);

    printf("________________________________________________________________\n");

    //wait_for_arp_request(&data);

	// Processing
	// Cleanup

    return 0;
}
