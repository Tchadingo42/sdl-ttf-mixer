#include "doom.h"

void			ft_set_ceiling_floor(t_thread_env *e)
{
	double	scale;

	scale = e->cam.proj_dist * WALL_SIZE / e->rc.distance_towall;
	e->rc.floor = (e->cam.proj_dist / e->rc.distance_towall) * (e->cam.pos_z)
		+ e->cam.angle_z;
	e->rc.ceiling = e->rc.floor - scale;
	e->rc.ceiling -= ((e->map.alt[e->rc.test_y * e->map.nbcol + e->rc.test_x]
		- 1) / e->rc.distance_towall) * WALL_SIZE;
}
