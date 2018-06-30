#ifndef QUEUE_H
#define QUEUE_H

#include "app_utils.h"


typedef struct		s_queue {
  char			*buffer[MAX_BUFFER];
  int			head;
  int			tail;
  int			full;
  int			empty;
  pthread_mutex_t	*mutex;     // for locking the queue
  pthread_cond_t	*not_full;  // check if queue is full
  pthread_cond_t	*not_empty; // check if queue is empty
} t_queue; // queue


void		queue_destroy(t_queue *q);
t_queue*	queue_init();
void		queue_push(t_queue *q, char* msg);
char*		queue_pop(t_queue *q);

#endif
