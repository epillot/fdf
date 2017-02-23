/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:21:32 by epillot           #+#    #+#             */
/*   Updated: 2017/02/23 15:56:41 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static t_map	*new_point(char *param, int x, int y)
{
	t_map	*new;

	if (!(new = ft_memalloc(sizeof(t_map))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = ft_atoi(param);
	return (new);
}

static t_map	*create_line(char **param, int y)
{
	t_map	*line;
	t_map	*last;
	t_map	*elem;
	int		i;

	i = 0;
	line = NULL;
	while (param[i])
	{
		if (!(elem = new_point(param[i], i, y)))
			exit(EXIT_FAILURE);
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
		{
			ft_putendl_fd("Found wrong line length. Exiting.", 2);
			exit(EXIT_FAILURE);
		}
		map->down = line;
		map = map->right;
		if (!map && line->right)
		{
			//have to free all excess elem
			line->right = NULL;
		}
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

t_map			*get_map(char *file)
{
	int		fd;
	t_map	*map;
	t_map	*line;
	char	*param;
	char	**point;
	int		y;

	map = NULL;
	y = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &param) > 0)
	{
		if (!(point = ft_strsplit(param, ' ')))
			exit(EXIT_FAILURE);
		line = create_line(point, y);
		if (map)
			link_down(map, line);
		else
			map = line;
		free(param);
		free_point(point);
		y++;
	}
	return (map);
}
