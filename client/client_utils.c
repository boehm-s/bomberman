#include "includes/app_utils.h"

//Concatenates the name with the message and puts it into result
void build_message(char *result, char *name, char *msg) {
  memset(result, 0, MAX_BUFFER);
  strcpy(result, name);
  strcat(result, ": ");
  strcat(result, msg);
}

//Sets up the socket and connects
void setup_and_connect(struct sockaddr_in *server_addr, struct hostent *host, int socket_fd, long port) {
  memset(server_addr, 0, sizeof(server_addr));
  server_addr->sin_family = AF_INET;
  server_addr->sin_addr = *((struct in_addr *)host->h_addr_list[0]);
  server_addr->sin_port = htons(port);
  if(connect(socket_fd, (struct sockaddr *) server_addr, sizeof(struct sockaddr)) < 0) {
    perror("Couldn't connect to server");
    exit(1);
  }
}

//Sets the fd to nonblocking
void set_NONBLOCK(int fd) {
  int flags = fcntl(fd, F_GETFL);
  if(flags < 0)
    perror("fcntl failed");

  flags |= O_NONBLOCK;
  fcntl(fd, F_SETFL, flags);
}

//Notify the server when the client exits by sending "/exit"
void interrupt_handler(int sig_unused) {
  UNUSED(sig_unused);
  if(write(socket_fd, "/exit\n", MAX_BUFFER - 1) == -1)
    perror("write failed: ");

  close(socket_fd);
  exit(1);
}
