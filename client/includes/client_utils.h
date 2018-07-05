#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include "app_utils.h"

void game_loop(char *name, int socket_fd);
void build_message(char *result, char *name, char *msg);
void setup_and_connect(struct sockaddr_in *server_addr, struct hostent *host, int socket_fd, long port);
void set_NONBLOCK(int fd);
void interrupt_handler(int sig);


#endif
