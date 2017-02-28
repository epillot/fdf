/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iso_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:52:15 by epillot           #+#    #+#             */
/*   Updated: 2017/02/24 15:28:42 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_iso_coord(t_map *map, t_param *p, int proj)
{
	t_map	*line;

	while (map)
	{
		line = map;
		while (line)
		{
			if (proj == 0)
			{
				line->X = 2 * line->x - 2 * line->y;
				line->Y = line->x + line->y - line->z / p->r->ratio;
			}
			else
			{
				line->X = line->x + 2 * (int)(line->z / p->r->ratio);
				line->Y = line->y + line->z / p->r->ratio;
			}
			if (line->X > p->xmax)
				p->xmax = line->X;
			if (line->Y > p->ymax)
				p->ymax = line->Y;
			if (line->X < p->xmin)
				p->xmin = line->X;
			if (line->Y < p->ymin)
				p->ymin = line->Y;
			if (line->z / p->r->ratio > p->zmax)
				p->zmax = line->z / p->r->ratio;
			if (line->z / p->r->ratio < p->zmin)
				p->zmin = line->z / p->r->ratio;
			line = line->right;
		}
		map = map->down;
	}
}
