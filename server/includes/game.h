#ifndef GAME_H
#define GAME_H

#include "./player.h"
#include "./map.h"
#include "./messaging.h"


#define MAX_PLAYERS 4


// would have been better to have one mutex for the map and another one for the players infos, but right now changing the map's type (char *) is too much time consuming

typedef struct          s_game {
  pthread_mutex_t	*game_mutex;
  t_player_infos        *player_infos;
  t_map                 *map;
} t_game;

typedef struct          s_game_msg_wrapper {
  t_game                *game;
  t_msg_data            *msg_data;
} t_game_msg_wrapper;



t_game			*init_game();
void			game_handle_message(char *msg, t_game *game);
void                    move_user_direction(char *user, char direction);
void                    change_user_direction(char *user, char direction);
t_player_infos          *get_player_by_name(t_game *game, char *name);

#endif
