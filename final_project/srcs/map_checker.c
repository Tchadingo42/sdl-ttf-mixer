#include "doom.h"

int		ft_check_borders(t_map *map)
{
	int		i;
	char	*line;

	line = map->data + map->cur_line * map->nbcol;
	i = 0;
	while (i < map->nbcol)
	{
		if (line[i] != '#')
			return (-1);
		i++;
	}
	return (0);
}

int		ft_check_line(t_map *m)
{
	int		i;
	char	*l;

	l = m->data + m->cur_line * m->nbcol;
	i = 0;
	if (l[i++] != '#')
		return (-2);
	while (i < m->nbcol)
	{
		if (ft_check_line_2(l, i) == -1)
			return (-1);
		i++;
	}
	if (l[--i] != '#')
		return (-2);
	i = -1;
	while (++i < m->nbcol)
		if (m->bright[m->cur_line * m->nbcol + i] < 0
				|| m->bright[m->cur_line * m->nbcol + i] > 3)
			return (-3);
	return (0);
}

int		precheck_one(char *l, int p)
{
	int		i;

	i = 0;
	if (precheck_one_2(l, p, i) == -1)
		return (-1);
	i++;
	if (l[p + i] != ' ')
		return (-2);
	i++;
	if (!ft_isdigit(l[p + i]) || ft_atoi(l + p + i) < 0)
		return (-3);
	while (ft_isdigit(l[p + i]))
		i++;
	if (l[p + i++] != ' ')
		return (-2);
	if (!ft_isdigit(l[p + i]) || ft_atoi(l + p + i) < 0)
		return (-3);
	while (ft_isdigit(l[p + i]))
		i++;
	if (l[p + i] == '\0')
		return (0);
	else if (l[p + i] != '\t')
		return (-2);
	i++;
	return (i);
}

int		precheck_line(char *line)
{
	size_t	nbcol;
	int		pos;
	int		pos_one;

	nbcol = 1;
	pos = 0;
	while (nbcol < 100 && (pos_one = precheck_one(line, pos)) > 0)
	{
		nbcol++;
		pos += pos_one;
	}
	if (pos_one == 0)
		return (nbcol);
	return (-1);
}

void	ft_count_lines_columns(t_map *m, char *mapfile, int fd)
{
	char	*line;

	if ((fd = open(mapfile, O_RDONLY)) < 0)
		ft_norme(5);
	line = NULL;
	if ((get_next_line(fd, &line)) <= 0)
		ft_error(m, 6, line);
	if ((m->nbcol = precheck_line(line)) == -1)
		ft_error(m, 3, line);
	ft_memdel((void **)&line);
	m->nbl++;
	while (get_next_line(fd, &line) > 0)
	{
		if (m->nbcol != precheck_line(line))
		{
			close(fd);
			ft_error(m, 2, line);
		}
		m->nbl++;
		ft_memdel((void **)&line);
	}
	if (close(fd) < 0)
		ft_error(m, 7, line);
}
