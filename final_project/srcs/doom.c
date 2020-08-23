#include "doom.h"

void	ft_doom(char *mapfile)
{
	t_env	doom;

	ft_initialize(&doom, mapfile, FALSE);
	save_in_file(&doom);
	ft_sdl(&doom);
}
