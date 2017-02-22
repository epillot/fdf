/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_iso_coord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:52:15 by epillot           #+#    #+#             */
/*   Updated: 2017/02/22 18:47:16 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		get_iso_coord(t_map *map, t_param *p)
{
	t_map	*line;

	while (map)
	{
		line = map;
		while (line)
		{
			line->X = p->coeff * (line->x - line->y + p->offset + 1);
			line->Y = p->coeff * (line->x + line->y - line->z + p->offset + 1);
			if (line->X > p->xmax)
				p->xmax = line->X;
			if (line->Y > p->ymax)
				p->ymax = line->Y;
			if (line->X < p->xmin)
				p->xmin = line->X;
			if (line->Y < p->ymin)
				p->ymin = line->Y;
			line = line->right;
		}
		map = map->down;
	}
}
