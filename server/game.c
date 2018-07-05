#include "includes/app_utils.h"
#include "includes/game.h"

char**                  str_split(char* a_str, const char a_delim) {
  char**                result    = 0;
  size_t                count     = 0;
  char*                 tmp        = a_str;
  char*                 last_comma = 0;
  char                  delim[2];
  delim[0] = a_delim;
  delim[1] = 0;

  while (*tmp) {
    if (a_delim == *tmp) {
      count++;
      last_comma = tmp;
    }
    tmp++;
  }
  count += last_comma < (a_str + strlen(a_str) - 1);
  count++;

  result = malloc(sizeof(char*) * count);

  if (result) {
      size_t idx  = 0;
      char* token = strtok(a_str, delim);

      while (token) {
        assert(idx < count);
        *(result + idx++) = strdup(token);
        token = strtok(0, delim);
      }
      assert(idx == count - 1);
      *(result + idx) = 0;
  }

  return result;
}

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

void			game_handle_message(char *msg, t_game *game) {
  char                  **split_msg = str_split(msg, ':');
  char                  *user = split_msg[0];
  char                  *cmd = split_msg[1];

  if (cmd[0] == 'd') { // change user  direction
    change_user_direction(user, cmd[1]);
  } else if (cmd[0] == 'm') {
    move_user_direction(user, cmd[1]);
  }

  UNUSED(split_msg);
  UNUSED(user);
  UNUSED(cmd);
  UNUSED(game);
}

void move_user_direction(char *user, char direction) {
  UNUSED(user);
  UNUSED(direction);
}

void change_user_direction(char *user, char direction) {
  UNUSED(user);
  UNUSED(direction);
}

t_player_infos          *get_player_by_name(t_game *game, char *name) {
    pthread_mutex_lock(game->game_mutex);
    for (int i = 0; i < MAX_PLAYERS; i++) {
      if (strcmp(name, game->player_infos[i].name) == 0)
        return &game->player_infos[i];
    }
    pthread_mutex_unlock(game->game_mutex);

    return NULL;
}
