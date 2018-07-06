#include "includes/app_utils.h"
#include "includes/game.h"

/* Arrange the N elements of ARRAY in random order.
   Only effective if N is much smaller than RAND_MAX;
   if this may not be the case, use a better random
   number generator. */
void shuffle (int *array, size_t n) {
  if (n > 1)  {
    size_t i;
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}
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
  game->game_mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
  game->game_started = 0;

  pthread_mutex_init(game->game_mutex, NULL);


  print_map(game->map);
  print_players(game->player_infos);

  return (game);
}

void                    game_loop(void *data) {
  t_game                *game = (t_game *) data;

  while (42) {
    if (game->game_started == 1) {
      int player_indexes[4] = {0,1,2,3};
      shuffle(player_indexes, 4);

      pthread_mutex_lock(game->game_mutex);
      // exec each player last recieved command
      for (int i = 0; i < MAX_PLAYERS; i++) {
        exec_player_cmd(game, game->player_infos[player_indexes[i]]);
      }

      // broadcast the modified game info


      pthread_mutex_unlock(game->game_mutex);
    }
    usleep(GAME_LOOP_DELAY * 1000);
  }
}

void			game_handle_message(char *msg, t_game *game) {
  char                  **split_msg = str_split(msg, ':');
  char                  *user = split_msg[0];
  char                  *cmd = split_msg[1];
  t_player_infos        *player;

  pthread_mutex_lock(game->game_mutex);
  player = get_player_by_name(game, user);

  if (player != NULL) {
    player->last_cmd = cmd;
  }
  pthread_mutex_lock(game->game_mutex);
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


void                    exec_player_cmd(t_game *game, t_player_infos player) {
  UNUSED(game);
  UNUSED(player);
}
