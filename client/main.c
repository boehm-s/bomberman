#include "./includes/server.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int init_server(char *address, int *_sockfd, struct sockaddr_in *_serv_addr) {
  int sockfd = *(_sockfd);
  struct sockaddr_in serv_addr = *(_serv_addr);

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Error : Could not create socket \n");
    return 1;
  }

  memset(&serv_addr, '0', sizeof(serv_addr));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(4242);

  if (inet_pton(AF_INET, address, &serv_addr.sin_addr) <= 0) {
    printf("\n inet_pton error occured\n");
    return 1;
  }

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\n Error : Connect Failed \n");
    return 1;
  }

  printf("Init server successfully !\n");

  return 0;
}

void handle_message(char *message, int *_sockfd) {
  int sockfd = *(_sockfd);
  char user_msg[1024];
  int msg_length;

  puts("------------------------------MESSAGE------------------------------");
  puts(message);
  puts("----------------------------MESSAGE_END------------------------------");

  msg_length = scanf("Enter a message : %s", user_msg);
  write(sockfd, user_msg, msg_length);
}

int main(int argc, char *argv[]) {
  UNUSED(argc);
  UNUSED(argv);

  int sockfd = 0;
  int n = 0;
  char recvBuff[1024];
  struct sockaddr_in serv_addr;

  memset(recvBuff, '0', sizeof(recvBuff));

  if (init_server("127.0.0.1", &sockfd, &serv_addr) != 0) {
    return 1;
  }


  while ((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0) {
    recvBuff[n] = '\0';
    if(fputs(recvBuff, stdout) == EOF) {
      printf("\n Error : Fputs error\n");
    } else {
      handle_message(recvBuff, &sockfd);
    }
  }

  if (n < 0) {
    printf("\n Read error \n");
  }

  return 0;
}
