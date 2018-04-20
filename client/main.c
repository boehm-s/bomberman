#include <czmq.h>
#include "includes/server.h"

int main (int argc, char *argv []) {
  UNUSED(argc);
  UNUSED(argv);

  zsock_t *socket = zsock_new_sub("tcp://127.0.0.1:4242", "TOPIC");
  assert(socket);

  char *topic;
  char *frame;
  zmsg_t *msg;
  int rc = zsock_recv(socket, "sm", &topic, &msg);
  assert(rc == 0);

  zsys_info("Recv on %s", topic);

  while((frame = zmsg_popstr(msg))) {
    zsys_info("> %s", frame);
    free(frame);
  }
  free(topic);
  zmsg_destroy(&msg);

  zsock_destroy(&socket);
  return 0;
}
