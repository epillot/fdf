/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:06:59 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 18:35:10 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_point(int x, int y, int color, t_param p)
{
	unsigned int	c;
	char			*tmp;
	int				i;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	i = 0;
	tmp = p.data + x * p.bpp / 8 + y * p.sizeline;
	c = mlx_get_color_value(p.mlx, color);
	while (i < p.bpp / 8)
	{
		if (p.endian == p.local_endian)
			*(tmp + i) = *(((char*)&c) + i);
		else
			*(tmp + i) = *(((char*)(&c) + p.bpp / 8 - i - 1));
		i++;
	}
}

static int	get_color(t_param p, int z)
{
	int		c;
	char	*clr;

	c = 0x00ffffff;
	clr = (char*)&c;
	if (p.zmax && z >= 0)
		*clr = 255 - z * (255 / p.zmax);
	else if (p.zmin)
	{
		*(clr + 1) = 255 - z * (255 / p.zmin);
		*(clr + 2) = 255 - z * (255 / p.zmin);
	}
	return (c);
}

static void	init_segment_param(t_map *p0, t_map *p1, t_param p, t_segment *s)
{
	s->dx = ft_abs(p1->xx - p0->xx);
	s->dy = ft_abs(p1->yy - p0->yy);
	s->e1 = (s->dx > s->dy ? s->dx : -(s->dy)) / 2;
	s->xi = p0->xx < p1->xx ? 1 : -1;
	s->yi = p0->yy < p1->yy ? 1 : -1;
	s->x = p0->xx;
	s->y = p0->yy;
	s->z = p0->z / p.r->ratio;
	s->zi = (p1->z / p.r->ratio - p0->z / p.r->ratio) / ft_max(s->dx, s->dy);
}

static void	draw_segment(t_map *p0, t_map *p1, t_param p)
{
	t_segment	s;

	init_segment_param(p0, p1, p, &s);
	while (s.x != p1->xx || s.y != p1->yy)
	{
		draw_point(s.x, s.y, get_color(p, s.z), p);
		s.e2 = s.e1;
		if (s.e2 > -(s.dx))
		{
			s.e1 -= s.dy;
			s.x += s.xi;
		}
		if (s.e2 < s.dy)
		{
			s.e1 += s.dx;
			s.y += s.yi;
		}
		s.z += s.zi;
	}
}

void		draw_map(t_param p)
{
	t_map	*line;

	while (p.map)
	{
		line = p.map;
		while (line)
		{
			if (line->right)
				draw_segment(line, line->right, p);
			if (line->down)
				draw_segment(line, line->down, p);
			line = line->right;
		}
		p.map = p.map->down;
	}
}
