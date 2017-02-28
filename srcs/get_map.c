/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:21:32 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 19:24:07 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map	*new_point(char *param, int x, int y, t_param *p)
{
	t_map	*new;
	int		sign;

	sign = 0;
	if (*param == '-' || *param == '+')
		sign = 1;
	if (!ft_isdigit(param[sign]))
		fdf_error(1, NULL);
	if (!(new = ft_memalloc(sizeof(t_map))))
		fdf_error(2, NULL);
	new->x = x;
	new->y = y;
	new->z = ft_atoi(param);
	get_ratio(ft_abs(new->z), p);
	return (new);
}

static t_map	*create_line(char **param, int y, t_param *p)
{
	t_map	*line;
	t_map	*last;
	t_map	*elem;
	int		i;

	i = 0;
	line = NULL;
	while (param[i])
	{
		elem = new_point(param[i], i, y, p);
		if (line)
		{
			last = line;
			while (last->right)
				last = last->right;
			last->right = elem;
		}
		else
			line = elem;
		i++;
	}
	return (line);
}

static void		link_down(t_map *map, t_map *line)
{
	while (map->down)
		map = map->down;
	while (map)
	{
		if (!line)
			fdf_error(1, NULL);
		map->down = line;
		map = map->right;
		if (!map && line->right)
			fdf_error(1, NULL);
		line = line->right;
	}
}

static void		free_point(char **point)
{
	int		i;

	i = 0;
	while (point[i])
	{
		free(point[i]);
		i++;
	}
	free(point);
}

t_map			*get_map(int fd, t_param *p)
{
	t_map	*map;
	t_map	*line;
	char	*param;
	char	**point;
	int		y;

	map = NULL;
	y = 0;
	while (get_next_line(fd, &param) > 0)
	{
		if (!(point = ft_strsplit(param, ' ')))
			fdf_error(2, NULL);
		line = create_line(point, y, p);
		if (map)
			link_down(map, line);
		else
			map = line;
		free(param);
		free_point(point);
		y++;
	}
	close(fd);
	return (map);
}
