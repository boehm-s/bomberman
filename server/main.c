#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <pthread.h>

#include "includes/server.h"
#include "includes/map.h"
#include "includes/player.h"
#include "includes/game.h"


void			*connection_handler(void *_sock) {
  int			sock;
  int			read_size;
  char			*message;
  char			client_message[2000];

  sock = *(int*)_sock;

  message = "Greetings! I am your connection handler\n";
  write(sock, message, strlen(message));

  message = "Now type something and i shall repeat what you type \n";
  write(sock, message, strlen(message));

  //Receive a message from client and send it back
  while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
    write(sock , client_message , strlen(client_message));
  }

  if(read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  } else if(read_size == -1) {
    perror("recv failed");
  }

  //Free the socket pointer
  free(_sock);

  return (0);
}

int			create_socket(int port_number) {
  int			socket_desc;
  struct sockaddr_in	address;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1)
    perror("Create socket");

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_number);
  bind(socket_desc, (struct sockaddr *)&address, sizeof(address));

  return (socket_desc);
}

int			main (int argc, char *argv []) {
  UNUSED(argc);
  UNUSED(argv);

  t_game		*game;

  game = init_game();

  UNUSED(game);

  int sock, new_socket, c, *new_sock;
  struct sockaddr_in client;
  char *message;

  sock = create_socket(PORT_NUMBER);
  listen(sock, MAX_CONN);

  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);
  while( (new_socket = accept(sock, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
    puts("Connection accepted");

    //Reply to the client
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    write(new_socket , message , strlen(message));

    pthread_t sniffer_thread;
    new_sock = malloc(1);
    *new_sock = new_socket;

    if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) < 0) {
      perror("could not create thread");
      return 1;
    }

    //Now join the thread , so that we dont terminate before the thread
    //pthread_join( sniffer_thread , NULL);
    puts("Handler assigned");
  }

  if (new_socket < 0) {
    perror("accept failed");
    return 1;
  }


  return 0;
}
