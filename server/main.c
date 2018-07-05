#include "includes/app_utils.h"

#include "includes/socket_utils.h"
#include "includes/server.h"
#include "includes/map.h"
#include "includes/player.h"
#include "includes/game.h"


int			main (int argc, char *argv []) {
  t_game		*game;
  struct sockaddr_in	server_addr;
  long			port;
  int			socket_fd;

  UNUSED(argc);
  UNUSED(argv);
  UNUSED(game);

  game = init_game();
  /* --------------------------------------------------------------------------------------------------------------- */


  port = argc == 2 ? strtol(argv[1], NULL, 0) : PORT_NUMBER;

  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("Socket creation failed");
      exit(1);
  }

  bind_socket(&server_addr, socket_fd, port);
  if (listen(socket_fd, 1) == -1) {
    perror("listen failed: ");
    exit(1);
  }

  start_app(socket_fd);
  close(socket_fd);


  /* --------------------------------------------------------------------------------------------------------------- */
  return 0;
}


	  /* if (chat_data->client_count == MAX_PLAYER) { */
	  /*   start_game(chat_data); */
	  /* } */
