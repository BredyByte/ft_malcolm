#include "malcolm.h"

static int is_valid_ip(const char *ip) {
    if (ip == NULL || *ip == '\0') {
        return 0;
    }


    // here this check
    // if (inet_pton(AF_INET, VICTIM_IP, victim_ip_bytes) != 1) {
    //     perror("inet_pton for VICTIM_IP failed");
    //     exit(1);
    // }

    struct sockaddr_in sa;
    return inet_pton(AF_INET, ip, &(sa.sin_addr)) != 0;
}

static int is_valid_mac(const char *mac) {
    if (mac == NULL || *mac == '\0') {
        return 0;
    }

    int i = 0;
    char *mac_dup = ft_strdup(mac);
    if (mac_dup == NULL) {
        return 0;
    }

    char *token = ft_strtok(mac_dup, ":");

    while (token != NULL) {
        if (ft_strlen(token) != 2 || ft_strtol(token, NULL, 16) == 0) {
            if (mac_dup) free(mac_dup);
            return 0;
        }
        token = ft_strtok(NULL, ":");
        i++;
    }

    if (mac_dup) free(mac_dup);
    return i == 6;
}

int validate(const char** argv) {
    const char **tmp = argv;
	const char *source_ip = tmp[1];
	const char *source_mac = tmp[2];
	const char *target_ip = tmp[3];
	const char *target_mac = tmp[4];

    if (!is_valid_ip(source_ip)) {
        fprintf(stderr, "Error: Invalid source IP address: %s\n", source_ip);
        return 1;
    }
    if (!is_valid_ip(target_ip)) {
        fprintf(stderr, "Error: Invalid target IP address: %s\n", target_ip);
        return 1;
    }

    if (!is_valid_mac(source_mac)) {
        fprintf(stderr, "Error: Invalid source MAC address: %s\n", source_mac);
        return 1;
    }
    if (!is_valid_mac(target_mac)) {
        fprintf(stderr, "Error: Invalid target MAC address: %s\n", target_mac);
        return 1;
    }

    return 0;
}
