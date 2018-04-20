#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "includes/player.h"
#include "includes/game.h"


t_player_infos		*init_players(t_map *map) {
  t_player_infos	*players;
  int			i;
  int			map_size;

  map_size = (int) sqrt((double) strlen((char *) map));
  players = malloc(sizeof(t_player_infos) * MAX_PLAYERS);

  for (i = 0; i < MAX_PLAYERS; i++) {
    players[i].connected = 1;
    players[i].alive = 0;
    players[i].x_pos = i % 2 == 0 ? 1 : (map_size - 2);
    players[i].y_pos = i < 2 ? 1 : (map_size - 2);
    players[i].current_dir = (i + 1) % 3;
    players[i].current_speed = START_SPEED;
    players[i].max_speed = MAX_SPEED;
    players[i].bombs_left = START_BOMB;
    players[i].bombs_capacity = MAX_BOMB;
    players[i].frags = 0;
  }

  return (players);
}

void		print_players(t_player_infos *players) {
  int		i;

  puts("/------------------------------------------------------\\");
  printf("|   NAME   |  X,Y  | DIRECTION | SPEED | BOMBS | FRAGS |\n");
  puts("|------------------------------------------------------|");
  for (i = 0; i < MAX_PLAYERS; i++) {
    printf("| player %i | %02d,%02d |     %i     |  %03d  | %02d/%02d |  %i    |\n", i, players[i].x_pos, players[i].y_pos, players[i].current_dir, players[i].current_speed, players[i].bombs_left, players[i].bombs_capacity, players[i].frags);
  }
  puts("\\------------------------------------------------------/\n");
}
