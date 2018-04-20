#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "includes/game.h"


t_game			*init_game() {
  t_game		*game;
  t_map			*map;

  map = init_map(16);
  fill_map(map);

  game = malloc(sizeof(t_game));
  game->map = map;
  game->player_infos = init_players(game->map);

  print_map(game->map);
  print_players(game->player_infos);

  return (game);
}
