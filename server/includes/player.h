#ifndef PLAYER_H
#define PLAYER_H

#include "./map.h"

#define DIRECTION_TOP 0
#define DIRECTION_BOTTOM 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3
#define START_SPEED 50
#define MAX_SPEED 250
#define START_BOMB 3
#define MAX_BOMB 10

typedef struct 	s_player_infos {
  char  		connected;
  char  		alive;
  int   		x_pos;
  int   		y_pos;
  int   		current_dir;
  int   		current_speed;
  int   		max_speed;
  int   		bombs_left;
  int   		bombs_capacity;
  int   		frags;
} t_player_infos;

t_player_infos  *init_players(t_map *map);
void		print_players(t_player_infos *players);

#endif
