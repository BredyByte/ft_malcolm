#include "libft.h"

long int ft_strtol(const char *str, char **endptr, int base) {
    const char *s = str;
    long int result = 0;

    while (ft_isspace((unsigned char)*s)) {
        s++;
    }

    if (base == 0) {
        if (*s == '0') {
            if (s[1] == 'x' || s[1] == 'X') {
                base = 16;
                s += 2;
            } else {
                base = 8;
            }
        } else {
            base = 10;
        }
    }

    while (1) {
        int digit;
        if (*s >= '0' && *s <= '9') {
            digit = *s - '0';
        } else if (*s >= 'a' && *s <= 'f') {
            digit = *s - 'a' + 10;
        } else if (*s >= 'A' && *s <= 'F') {
            digit = *s - 'A' + 10;
        } else {
            break;
        }

        if (digit >= base) {
            break;
        }

        if (result > (LONG_MAX - digit) / base) {
            if (endptr) {
                *endptr = (char *)s;
            }
            return base == 10 ? LONG_MAX : LONG_MIN;
        }

		result = result * base + digit;
        s++;
    }

    if (endptr) {
        *endptr = (char *)s;
    }

    return result;
}
