#include "malcolm.h"

int main(int argc, const char **argv) {

	// Arguments Validation
    if (argc != 5) {
        fprintf(stderr, "Usage: <source_ip> <source_mac> <target_ip> <target_mac>\n");
        return 1;
    }

    if (validate(argv) != 0) {
        return 1;
    }

	// Initialization
	// Processing
	// Cleanup

    return 0;
}
