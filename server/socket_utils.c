#include "includes/socket_utils.h"
#include "includes/app_utils.h"


//Sets up and binds the socket
void bind_socket(struct sockaddr_in *server_addr, int socket_fd, long port)
{
  memset(server_addr, 0, sizeof(*server_addr));
  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr->sin_port = htons(port);

  if(bind(socket_fd, (struct sockaddr *)server_addr, sizeof(struct sockaddr_in)) == -1) {
    perror("Socket bind failed: ");
    exit(1);
  }
}


void		start_app(int socket_fd, t_game *game) {
  t_msg_data	data;
  t_game_msg_wrapper game_msg_wrap;
  pthread_t	connection_thread;
  pthread_t	messages_thread;
  pthread_t     game_loop_thread;

  data.client_count = 0;
  data.socket_fd = socket_fd;
  data.queue = queue_init();
  data.client_list_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));

  game_msg_wrap.game = game;
  game_msg_wrap.msg_data = &data;

  pthread_mutex_init(data.client_list_mutex, NULL);

  //Start thread to handle new client connections
  if((pthread_create(&connection_thread, NULL, (void *)&new_client_handler, (void *)&game_msg_wrap)) == 0) {
      fprintf(stderr, "Connection handler started\n");
  }

  FD_ZERO(&(data.server_read_fds));
  FD_SET(socket_fd, &(data.server_read_fds));

  //Start thread to handle messages received
  if((pthread_create(&messages_thread, NULL, (void *)&message_handler, (void *)&game_msg_wrap)) == 0) {
    fprintf(stderr, "Message handler started\n");
  }

  //start the game loop thread
  if((pthread_create(&game_loop_thread, NULL, (void *)&game_loop , (void *)game)) == 0) {
    fprintf(stderr, "Game loop started\n");
  }

  pthread_join(connection_thread, NULL);
  pthread_join(messages_thread, NULL);

  queue_destroy(data.queue);
  pthread_mutex_destroy(data.client_list_mutex);
  free(data.client_list_mutex);
}
