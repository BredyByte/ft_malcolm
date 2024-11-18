#include "malcolm.h"

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

    printf("Source IP: %s\n", data.source_ip);
    printf("Source MAC: %s\n", data.source_mac);
    printf("Target IP: %s\n", data.target_ip);
    printf("Target MAC: %s\n", data.target_mac);

	// Initialization
	// Processing
	// Cleanup

    return 0;
}
