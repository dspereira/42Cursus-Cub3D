#include "cube3d.h"

#define TRUE	1
#define FALSE	0

static int	door_check_interaction(t_ray ray, char **map);

void	doors_interaction(t_map map, t_player *player)
{
	t_ray	view;
	t_pos	door;

	view = player->rays[NUMBER_RAYS/2];
	if (!door_check_interaction(view, map.content))
		return ;
	door = view.door_pos;
	if (map.content[door.y][door.x] == D_FRAME_OPEN_0)
		map.content[door.y][door.x] = D_FRAME_OPEN_1;
	else if (map.content[door.y][door.x] == D_FRAME_CLOSE_0)
		map.content[door.y][door.x] = D_FRAME_CLOSE_7;
	else if (map.content[door.y][door.x] > D_FRAME_CLOSE_1 && map.content[door.y][door.x] <= D_FRAME_CLOSE_7)
		map.content[door.y][door.x] -= 1;
	else if (map.content[door.y][door.x] >= D_FRAME_OPEN_1 && map.content[door.y][door.x] < D_FRAME_OPEN_7)
		map.content[door.y][door.x] += 1;
	else if (map.content[door.y][door.x] == D_FRAME_OPEN_7)
		map.content[door.y][door.x] = D_FRAME_CLOSE_0;
	else if (map.content[door.y][door.x] == D_FRAME_CLOSE_1)
		map.content[door.y][door.x] = D_FRAME_OPEN_0;
}

static int	door_check_interaction(t_ray ray, char **map)
{
	if (!ray.is_door)
		return (FALSE);
	else if (ray.door_dist > 1)
		return (FALSE);
	else if (ray.door_pos.x < 0 || ray.door_pos.y < 0)
		return (FALSE);
	return (TRUE);
}
