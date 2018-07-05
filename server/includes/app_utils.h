#ifndef APP_UTILS_H
#define APP_UTILS_H

#define UNUSED(x) (void)(x)
#define MAX_BUFFER 1024
#define MAX_PLAYERS 4
#define MAX_PLAYER 4

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <netdb.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim);
#endif
