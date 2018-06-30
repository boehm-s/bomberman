#ifndef CLIENT_H
#define CLIENT_H

#define MSG_SIZE 1024
#define LOCALHOST "127.0.0.1"

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct		s_client {
  int			socket;
  struct sockaddr_in	*addr;
  char			recvBuff[MSG_SIZE];
} t_client;

#endif
