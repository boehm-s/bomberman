#include "includes/app_utils.h"
#include "includes/client_utils.h"

int			main(int argc, char *argv[]) {
  char			*name;
  struct sockaddr_in	server_addr;
  struct hostent	*host;
  long			port;

  if(argc != 4) {
    fprintf(stderr, "./client [username] [host] [port]\n");
    exit(1);
  }
  name = argv[1];
  if((host = gethostbyname(argv[2])) == NULL) {
    fprintf(stderr, "Couldn't get host name\n");
    exit(1);
  }
  port = strtol(argv[3], NULL, 0);
  if((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
    fprintf(stderr, "Couldn't create socket\n");
    exit(1);
  }

  setup_and_connect(&server_addr, host, socket_fd, port);
  set_NONBLOCK(socket_fd);
  set_NONBLOCK(0);

  //Set a handler for the interrupt signal
  signal(SIGINT, interrupt_handler);

  game_loop(name, socket_fd);
}

//Main loop to take in chat input and display output
void			game_loop(char *name, int socket_fd) {
  fd_set	        client_fds;
  char			chat_msg[MAX_BUFFER];
  char			chat_buffer[MAX_BUFFER];
  char			msg_buffer[MAX_BUFFER];

  while(1) {
    //Reset the fd set each time since select() modifies it
    FD_ZERO(&client_fds);
    FD_SET(socket_fd, &client_fds);
    FD_SET(0, &client_fds);
    if (select(FD_SETSIZE, &client_fds, NULL, NULL, NULL) != -1) { // wait for an available fd
      for (int fd = 0; fd < FD_SETSIZE; fd++) {
	if (FD_ISSET(fd, &client_fds)) {
	  if (fd == socket_fd) { //receive data from server
	    int numBytesRead = read(socket_fd, msg_buffer, MAX_BUFFER - 1);
	    msg_buffer[numBytesRead] = '\0';
	    printf("%s", msg_buffer);
	    memset(&msg_buffer, 0, sizeof(msg_buffer));
	  }
	  else if(fd == 0) {  //read from keyboard (stdin) and send to server
	    fgets(chat_buffer, MAX_BUFFER - 1, stdin);
	    if(strcmp(chat_buffer, "/exit\n") == 0)
	      interrupt_handler(-1); //Reuse the interrupt_handler function to disconnect the client
	    else {
	      build_message(chat_msg, name, chat_buffer);
	      if(write(socket_fd, chat_msg, MAX_BUFFER - 1) == -1) perror("write failed: ");
	      //printf("%s", chat_msg);
	      memset(&chat_buffer, 0, sizeof(chat_buffer));
	    }
	  }
	}
      }
    }
  }
}
