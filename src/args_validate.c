#include "malcolm.h"

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

    int i = 0;
    char *mac_dup = ft_strdup(mac);
    if (mac_dup == NULL) {
        return 0;
    }

    char *token = ft_strtok(mac_dup, ":");

    while (token != NULL) {
        if (ft_strlen(token) != 2 || ft_strtol(token, NULL, 16) == LONG_MIN) {
            if (mac_dup) free(mac_dup);
            return 0;
        }
        token = ft_strtok(NULL, ":");
        i++;
    }

    if (mac_dup) free(mac_dup);
    return i == 6;
}

int args_validate(const char** argv, t_network_data *data) {
    const char **tmp = argv;
	const char *source_ip = tmp[1];
	const char *source_mac = tmp[2];
	const char *target_ip = tmp[3];
	const char *target_mac = tmp[4];

    if (inet_pton(AF_INET, source_ip, data->source_ip) != 1) {
        fprintf(stderr, "Error: Invalid source IP address: %s\n", source_ip);
        return 1;
    }
    if (inet_pton(AF_INET, target_ip, data->target_ip) != 1) {
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
    if (mac_str_to_bytes(target_mac, data->target_mac) == -1 ||
        mac_str_to_bytes(source_mac, data->source_mac) == -1) {
        fprintf(stderr, "Error: Failed to convert MAC addresses.\n");
        return 1;
    }

    return 0;
}
