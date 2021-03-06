#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

#include "messaging.h"
#include "game.h"

void start_app(int socket_fd, t_game *game);
void bind_socket(struct sockaddr_in *server_addr, int socket_fd, long port);


#endif
