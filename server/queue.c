#include "includes/app_utils.h"
#include "includes/queue.h"

t_queue*	queue_init() {
  t_queue	*q = (t_queue *)malloc(sizeof(t_queue));

  if(q == NULL) {
    perror("Couldn't allocate anymore memory!");
    exit(EXIT_FAILURE);
  }

  q->empty = 1;
  q->full = q->head = q->tail = 0;
  q->mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  if(q->mutex == NULL) {
    perror("Couldn't allocate anymore memory!");
    exit(EXIT_FAILURE);
  }
  pthread_mutex_init(q->mutex, NULL);

  q->not_full = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  if(q->not_full == NULL) {
    perror("Couldn't allocate anymore memory!");
    exit(EXIT_FAILURE);  }
  pthread_cond_init(q->not_full, NULL);

  q->not_empty = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
  if(q->not_empty == NULL) {
    perror("Couldn't allocate anymore memory!");
    exit(EXIT_FAILURE);
  }
  pthread_cond_init(q->not_empty, NULL);

  return (q);
}

//Frees a queue
void		queue_destroy(t_queue *q) {
  pthread_mutex_destroy(q->mutex);
  pthread_cond_destroy(q->not_full);
  pthread_cond_destroy(q->not_empty);
  free(q->mutex);
  free(q->not_full);
  free(q->not_empty);
  free(q);
}

//Push to end of queue
void		queue_push(t_queue *q, char* msg) {
  q->buffer[q->tail] = msg;
  q->tail++;

  if(q->tail == MAX_BUFFER)
    q->tail = 0;
  if(q->tail == q->head)
    q->full = 1;

  q->empty = 0;
}

//Pop front of queue
char		*queue_pop(t_queue *q) {
  char		*msg = q->buffer[q->head];

  q->head++;
  if(q->head == MAX_BUFFER)
    q->head = 0;
  if(q->head == q->tail)
    q->empty = 1;
  q->full = 0;

  return (msg);
}
