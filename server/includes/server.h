#ifndef SERVER_H
#define SERVER_H

#define UNUSED(x) (void)(x)
#define PORT_NUMBER 4242
#define MAX_CONN 100

int			create_socket(int port_number);
void			*connection_handler(void *_sock);

#endif
