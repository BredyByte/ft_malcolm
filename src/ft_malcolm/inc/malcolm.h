#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../assets/libft/inc/libft.h"

int validate(const char** argv);

#endif
