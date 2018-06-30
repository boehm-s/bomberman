#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define MSG_SIZE 1024
#define LOCALHOST "127.0.0.1"
#define SERVER_PORT 4242
#define UNUSED(x) (void)(x)

typedef struct		s_client {
  int			socket;
  struct sockaddr_in	addr;
  char			recvBuff[MSG_SIZE];
} t_client;



void init_client(t_client *client) {
  char *test_co = "TEST_FROM_CLIENT\n";

  client->addr.sin_port        = htons(SERVER_PORT);
  client->addr.sin_family      = AF_INET;
  client->addr.sin_addr.s_addr = inet_addr(LOCALHOST);
  client->socket               = socket(AF_INET, SOCK_STREAM, 0);

  memset(client->recvBuff, '0', MSG_SIZE);

  if(client->socket < 0) {
    perror("\n SOCKET");
    exit(0);
  }

  if(connect(client->socket, (struct sockaddr*)&client->addr, sizeof(client->addr)) < 0) {
    perror("\n CONNECT");
    exit(0);
  }

  printf("client connected to %s", LOCALHOST);

  if(write(client->socket, test_co, MSG_SIZE) < 0) {
    printf("\n data could not be sent");
  }
}

int main(int argc, char *argv[]) {
  t_client *client = malloc(sizeof(t_client *));;
  int n;

  UNUSED(argc);
  UNUSED(argv);

  // init the client
  init_client(client);

  // wait messages from the server
  while ( (n = recv(client->socket, client->recvBuff, sizeof(client->recvBuff), MSG_WAITALL)) > 0) {
    client->recvBuff[n] = '\0';
    if(fputs(client->recvBuff, stdout) == EOF) {
	printf("\n Error : Fputs error\n");
    }
    memset(client->recvBuff, 0, MSG_SIZE);
  }
}
