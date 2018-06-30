#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include "messaging.h"

void start_app(int socket_fd);
void bind_socket(struct sockaddr_in *server_addr, int socket_fd, long port);


#endif
