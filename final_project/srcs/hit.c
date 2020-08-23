#include "doom.h"

void		ft_hit_barrel(t_env *doom, int barrel_y, int barrel_x)
{
	t_object	*tmp;

	tmp = &doom->obj;
	while (tmp != NULL)
	{
		if (tmp->data.type == BARREL)
		{
			if ((int)tmp->data.pos.y == barrel_y &&
					(int)tmp->data.pos.x == barrel_x)
			{
				tmp->data.hp -= PROJECTILE_DAMAGE;
				if (tmp->data.hp < 0)
				{
					tmp->data.to_remove = TRUE;
					doom->map.data[barrel_y *
						doom->map.nbcol + barrel_x] = EMPTY;
				}
			}
		}
		tmp = tmp->next;
	}
}
