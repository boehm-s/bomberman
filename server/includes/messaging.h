#ifndef MESSAGING_H
#define MESSAGING_H

#include "queue.h"

typedef struct		s_msg_data {
  fd_set		server_read_fds;
  int			socket_fd;  // server socket for new connections
  int			client_count;
  int			client_sockets[MAX_BUFFER];
  pthread_mutex_t	*client_list_mutex;
  t_queue	        *queue;
} t_msg_data;

typedef struct		s_client_handler {
  t_msg_data		*data;
  int			client_socket_fd;
} t_client_handler;


void			*new_client_handler(void *data);
void		        rm_client(t_msg_data *data, int client_socket_fd);
void			*client_handler(void *chv);
void			*message_handler(void *data);

#endif
