#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "includes/map.h"

t_map		*init_map(int map_size) {
  t_map		*map;
  int		i;
  int		map_len;

  map_len = map_size * map_size;
  map = malloc(sizeof(char) * map_len);
  for (i = 0; i < map_len; i++)
    map[i] = EMPTY_BLOCK;

  return (map);
}

void	        fill_map(t_map *map) {
  int		i;
  int		map_len;
  int		map_size;

  map_len = strlen((char *)map);
  map_size = (int) sqrt((double) map_len);

  for (i = 0; i < map_len; i++) {
    map[i] = (block_is_border(map_size, i))
      ? INDESTRUCTIBLE_BLOCK
      : random_block();
    }
  }
}


t_map		random_block() {
  int		rand = rand() % 101;
  int		*other_blocks =
    [

     ];
  if (rand <= 50) return (t_map) EMPTY_BLOCK;
  else return
}

void		print_map(t_map *map) {
  int		i;
  int		map_size;
  int		map_len;

  map_len = strlen((char *) map);
  map_size = (int) sqrt((double) map_len);

  puts("\n");
  for (i = 0; i < map_len; i++) {
    if ((i+1) % map_size == 0) {
      printf("%c \n", map[i] + 48);
    } else {
      printf("%c ", map[i] + 48);
    }
  }
  puts("\n");

}


/* blockes (map cases) */

int		get_bit(int8_t byteFlag, int whichBit) {
  return (whichBit > 0 && whichBit <= 8)
    ? (byteFlag & (1<<(whichBit-1)))
    : 0;
}

int		block_is_border(int map_size, int pos) {
  if (pos < map_size
      || pos >= ((map_size * map_size) - map_size - 1)
      || (pos + 1) % map_size == 0
      || (pos + 1) % map_size == 1)
    return (1);
  return (0);
}

int	        block_is_in_flame(t_map block) {
  int		bit1;

  bit1 = get_bit((int8_t) block, 1);
  return (bit1 == 1);
}

field_type	block_field_type(t_map block) {
  int		bit2;
  int		bit3;

  bit2 = get_bit((int8_t) block, 2);
  bit3 = get_bit((int8_t) block, 3);

  if (bit2 == 0) {
    return bit3 == 0 ? EMPTY : UNDEFINED;
  } else {
    return bit3 == 0 ? INDESTRUCTIBLE : DESTRUCTIBLE;
  }
}

int		block_has_bomb(t_map block) {
  int		bit4;

  bit4 = get_bit((int8_t) block, 4);
  return (bit4 == 1);
}

block_content     block_get_content(t_map block) {
  char		bits678[3];

  if (get_bit((int8_t) block, 5) == 0)
    return CLEAR;

  sprintf(bits678, "%i%i%i", get_bit((int8_t) block, 6), get_bit((int8_t) block, 7), get_bit((int8_t) block, 8));

  if (strcmp(bits678, "000"))  return B_PBOMB;
  else if (strcmp(bits678, "001"))  return M_PBOMB;
  else if (strcmp(bits678, "010"))  return B_NBOMB;
  else if (strcmp(bits678, "011"))  return M_NBOMB;
  else if (strcmp(bits678, "100"))  return B_SPEED;
  else if (strcmp(bits678, "101"))  return M_SPEED;
  else return CLEAR;
}
