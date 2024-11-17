#include "libft.h"

// Original function
// char *ft_strtok(char *str, const char *delim) {
//     static char *last = NULL;
//     char *start;

//     if (str) {
//         last = str;
//     }

//     if (!last) {
//         return NULL;
//     }

//     while (*last && ft_strchr(delim, *last)) {
//         last++;
//     }

//     start = last;

//     if (!*last) {
//         last = NULL;
//         return NULL;
//     }

// 	while (*last && !ft_strchr(delim, *last)) {
//         last++;
//     }

//     if (*last) {
//         *last = '\0';
//         last++;
//     }

//     return start;
// }

// Cutom one for ft_malcolm and mac parsing
char *ft_strtok(char *str, const char *delim) {
    static char *last = NULL;
    char *start;

    if (str) {
        last = str;
    }

    if (!last) {
        return NULL;
    }

    if (ft_strchr(delim, *last)) {
        return NULL;
    }

    start = last;

    while (*last && !ft_strchr(delim, *last)) {
        last++;
    }

    if (*last) {
        *last = '\0';
        last++;

        if (ft_strchr(delim, *last)) {
            last = NULL;
            return NULL;
        }
    }

    return start;
}
