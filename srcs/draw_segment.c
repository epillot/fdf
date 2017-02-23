/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 13:01:52 by epillot           #+#    #+#             */
/*   Updated: 2017/02/23 19:50:52 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_point(int x, int y, int color, t_param p)
{
	unsigned int	c;
	char			*tmp;
	int				i;
	void			*c2;

	i = 0;
	c2 = &c;
	tmp = p.data + x * p.bpp / 8 + y * p.sizeline;
	c = mlx_get_color_value(p.mlx, color);
	while (i < 4)
	{
		*tmp++ = *(char*)(c2)++;
		i++;
	}
}

void		draw_segment(t_map *p0, t_map *p1, t_param p)
{
	int dx = ft_abs(p1->X - p0->X);
	int dy = ft_abs(p1->Y - p0->Y);
	int e1 = (dx > dy ? dx : -dy) / 2;
	int e2;
	int xi = p0->X < p1->X ? 1 : -1;
	int yi = p0->Y < p1->Y ? 1 : -1;
	int x = p0->X;
	int y = p0->Y;
	//char *tmp;
	int zdiff = p0->z - p1->z;
	ft_printf("zdiff: %d\n", zdiff);
	while (x != p1->X || y != p1->Y)
	{
		/*tmp = p.data + x * p.bpp / 8 + y * p.sizeline;
		*(int*)tmp = mlx_get_color_value(p.mlx, color);*/
		draw_point(x, y, 0x00ffffff, p);
		e2 = e1;
		if (e2 > -dx)
		{
			e1 -= dy;
			x += xi;
		}
		if (e2 < dy)
		{
			e1 += dx;
			y += yi;
		}
	}
}
