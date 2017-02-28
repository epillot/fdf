/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:21:02 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 18:08:38 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_min_max(int x, int y, int z, t_param *p)
{
	if (x > p->xmax)
		p->xmax = x;
	if (x < p->xmin)
		p->xmin = x;
	if (y > p->ymax)
		p->ymax = y;
	if (y < p->ymin)
		p->ymin = y;
	if (z > p->zmax)
		p->zmax = z;
	if (z < p->zmin)
		p->zmin = z;
}

void		get_new_coord(t_map *map, t_param *p, int proj)
{
	t_map	*line;

	while (map)
	{
		line = map;
		while (line)
		{
			if (proj == 0)
			{
				line->xx = 2 * line->x - 2 * line->y;
				line->yy = line->x + line->y - (int)(line->z / p->r->ratio);
			}
			else
			{
				line->xx = line->x + 2 * (int)(line->z / p->r->ratio);
				line->yy = line->y + (int)(line->z / p->r->ratio);
			}
			get_min_max(line->xx, line->yy, line->z / p->r->ratio, p);
			line = line->right;
		}
		map = map->down;
	}
}
