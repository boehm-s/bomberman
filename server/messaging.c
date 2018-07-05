#include "includes/app_utils.h"
#include "includes/messaging.h"

static int game_started = 0;

//Thread to handle new connections. Adds client's fd to list of client fds and spawns a new clientHandler thread for it
void		*new_client_handler(void *data) {
  t_msg_data	*msg_data = (t_msg_data *) data;
  int		*client_sockets = msg_data->client_sockets;

  while(42) {
    int client_socket_fd = accept(msg_data->socket_fd, NULL, NULL);
    if(client_socket_fd > 0) {
      fprintf(stderr, "Server accepted new client. Socket: %d\n", client_socket_fd);

      //Obtain lock on clients list and add new client in
      pthread_mutex_lock(msg_data->client_list_mutex);
      if(msg_data->client_count < MAX_BUFFER  && msg_data->client_count < MAX_PLAYER ) {
	//Add new client to list
	for(int i = 0; i < MAX_BUFFER; i++) {
	  if(!FD_ISSET(msg_data->client_sockets[i], &(msg_data->server_read_fds))) {
	    msg_data->client_sockets[i] = client_socket_fd;
	    i = MAX_BUFFER;
	  }
	}

	FD_SET(client_socket_fd, &(msg_data->server_read_fds));

	//Spawn new thread to handle client's messages
	t_client_handler c_h;
	c_h.client_socket_fd = client_socket_fd;
	c_h.data = msg_data;

	pthread_t client_thread;
	if((pthread_create(&client_thread, NULL, (void *)&client_handler, (void *)&c_h)) == 0) {
	  msg_data->client_count++;

          // 'ROOM' IS FULL
          if (msg_data->client_count == MAX_PLAYER && game_started == 0) {
            fprintf(stderr, "GAME JUST STARTED !!!\n");
            // Broadcast message to all connected clients
            for(int i = 0; i < msg_data->client_count; i++) {
              int socket = client_sockets[i];
              if(socket != 0 && write(socket, "GAME JUST STARTED !!!\n", 22 /* MAX_BUFFER - 1 */) == -1)
                perror("Socket write failed: ");
            }
            game_started = 1;
          }

          fprintf(stderr, "Client has joined chat. Socket: %d\n", client_socket_fd);
	}
	else
	  close(client_socket_fd);
      } else {
	fprintf(stderr, "CANNOT ACCEPT MORE CLIENTS ! \n");
	close(client_socket_fd);
	pthread_mutex_unlock(msg_data->client_list_mutex);
      }
      pthread_mutex_unlock(msg_data->client_list_mutex);
    }
  }
}


//The "producer" -- Listens for messages from client to add to message queue
void *client_handler(void *_c_h) {
  t_client_handler *c_h = (t_client_handler *)_c_h;
  t_msg_data *data = (t_msg_data *)c_h->data;

  t_queue *q = data->queue;
  int client_socket_fd = c_h->client_socket_fd;
  char msg_buffer[MAX_BUFFER];

  while(42) {
    int bytes_read_count = read(client_socket_fd, msg_buffer, MAX_BUFFER - 1);
    msg_buffer[bytes_read_count] = '\0';

    //If the client sent /exit\n, remove them from the client list and close their socket
    if(strcmp(msg_buffer, "/exit\n") == 0) {
      fprintf(stderr, "Client on socket %d has disconnected.\n", client_socket_fd);
      rm_client(data, client_socket_fd);
      return NULL;
    } else {
      //Wait for queue to not be full before pushing message
      while(q->full) {
	pthread_cond_wait(q->not_full, q->mutex);
      }

      //Obtain lock, push message to queue, unlock, set condition variable
      pthread_mutex_lock(q->mutex);
      fprintf(stderr, "Pushing message to queue: %s\n", msg_buffer);
      queue_push(q, msg_buffer);
      pthread_mutex_unlock(q->mutex);
      pthread_cond_signal(q->not_empty);
    }
  }
}

//The "consumer" -- waits for the queue to have messages then takes them out and broadcasts to clients
void		*message_handler(void *data) {
  t_msg_data	*msg_data = (t_msg_data *)data;
  t_queue       *q = msg_data->queue;
  /* int		*client_sockets = msg_data->client_sockets; */

  while(42) {
    //Obtain lock and pop message from queue when not empty
    pthread_mutex_lock(q->mutex);
    while(q->empty) {
      pthread_cond_wait(q->not_empty, q->mutex);
    }
    char* msg = queue_pop(q);
    pthread_mutex_unlock(q->mutex);
    pthread_cond_signal(q->not_full);


    fprintf(stderr, "msg received : %s\n", msg);

    if (game_started != 0) {
      /* game_handle_message(msg); */
    }
  }
}


//Removes the socket from the list of active client sockets and closes it
void rm_client(t_msg_data *data, int client_socket_fd) {
  pthread_mutex_lock(data->client_list_mutex);
  for(int i = 0; i < MAX_BUFFER; i++) {
    if(data->client_sockets[i] == client_socket_fd) {
      data->client_sockets[i] = 0;
      close(client_socket_fd);
      data->client_count--;
      i = MAX_BUFFER;
    }
  }
  pthread_mutex_unlock(data->client_list_mutex);
}
