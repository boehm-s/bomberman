#ifndef MAP_H
#define MAP_H

#define INDESTRUCTIBLE_BLOCK 71
#define EMPTY_BLOCK 7
#define EMPTY_BLOCK_WITH_BOMB 23
#define DESTRUCTIBLE_BLOCK 103
#define DESTRUCTIBLE_BLOCK_WITH_BOMB 119

typedef enum e_field_type {EMPTY,
			   INDESTRUCTIBLE,
			   DESTRUCTIBLE,
			   UNDEFINED} field_type;

typedef enum e_block_content {CLEAR,
			      B_PBOMB,
			      M_PBOMB,
			      B_NBOMB,
			      M_NBOMB,
			      B_SPEED,
			      M_SPEED} block_content;
typedef char	t_map;

t_map		*init_map(int map_size);
t_map		*init_map(int map_size);
void	        fill_map(t_map *map);
void		print_map(t_map *map);

/* blocks */

int		get_bit(int8_t byteFlag, int whichBit);
int	        block_is_border(int map_size, int pos);
int	        block_is_in_flame(t_map block);
field_type      block_field_type(t_map block);
int	        block_has_bomb(t_map block);
block_content	block_get_content(t_map block);

t_map		random_block();

#endif
