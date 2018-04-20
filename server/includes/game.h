#ifndef GAME_H
#define GAME_H

#include "./player.h"
#include "./map.h"


#define MAX_PLAYERS 4


typedef struct          s_game {
  t_player_infos      *player_infos;
  t_map               *map;
} t_game;


t_game			*init_game();

#endif
