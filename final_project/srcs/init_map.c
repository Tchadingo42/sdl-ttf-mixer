#include "doom.h"

int			ft_malloc_tab(t_map *m)
{
	if (!(m->data = (char*)ft_memalloc(sizeof(char) * (m->nbl * m->nbcol + 1))))
		return (-1);
	m->data[m->nbl * m->nbcol] = '\0';
	if (!(m->bright = (int *)ft_memalloc(sizeof(int) * m->nbl * m->nbcol)))
		return (-1);
	if (!(m->alt = (int *)ft_memalloc(sizeof(int) * m->nbl * m->nbcol)))
		return (-1);
	return (1);
}

static int	get_tabvalues(t_map *m, int col, char *line, int prev_pos)
{
	char	*str;
	int		pos;

	str = line + prev_pos;
	pos = 0;
	m->data[m->cur_line * m->nbcol + col] = str[pos];
	pos += 2;
	m->bright[m->cur_line * m->nbcol + col] = ft_atoi(str + pos);
	while (ft_isdigit(str[pos]))
		pos++;
	pos++;
	m->alt[m->cur_line * m->nbcol + col] = ft_atoi(str + pos);
	while (ft_isdigit(str[pos]))
		pos++;
	if (!str[pos])
		return (0);
	else if (str[pos] == '\t')
		pos++;
	return (pos);
}

static int	ft_retrieve_data(t_map *m, char *line)
{
	int		col;
	int		pos;
	int		pos_val;

	if (m->data == NULL)
		if (ft_malloc_tab(m) == -1)
			return (-1);
	col = 0;
	pos = 0;
	while (col < m->nbcol && (pos_val = get_tabvalues(m, col, line, pos)) > 0)
	{
		col++;
		pos += pos_val;
	}
	if (m->cur_line == 0 && m->cur_line == (size_t)m->nbl)
		if (ft_check_borders(m) == -1)
			return (-1);
	if (ft_check_line(m) < 0)
		return (-1);
	m->cur_line++;
	return (0);
}

static void	ft_fill_map(t_map *m, int fd)
{
	char	*line;
	char	ret;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_retrieve_data(m, line) == -1)
			ft_error(m, 1, line);
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	if (m->nbl < 3 || m->nbcol < 3)
	{
		ft_putendl_fd("wrong map format", 2);
		exit(EXIT_FAILURE);
	}
}

void		ft_init_map(t_env *doom, char *mapfile)
{
	int fd;

	fd = 0;
	ft_count_lines_columns(&doom->map, mapfile, fd);
	if ((fd = open(mapfile, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error during open() ", 2);
		exit(EXIT_FAILURE);
	}
	ft_fill_map(&doom->map, fd);
	if (close(fd) < 0)
	{
		ft_putendl_fd("Error during close() ", 2);
		exit(EXIT_FAILURE);
	}
}
