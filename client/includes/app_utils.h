#ifndef APP_UTILS_H
#define APP_UTILS_H

#define UNUSED(x) (void)(x)
#define MAX_BUFFER 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>


static int socket_fd;

#endif
