/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 13:01:52 by epillot           #+#    #+#             */
/*   Updated: 2017/02/24 19:14:20 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_point(int x, int y, int color, t_param p)
{
	unsigned int	c;
	char			*tmp;
	int				i;

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

int			get_color(t_param p, int z)
{
	int c = 0x00ffffff;
	char *clr = (char*)&c;
	if (p.zmax && z >= 0)
		*clr = 255 - z * (255 / p.zmax);
	else if (p.zmin)
	{	
		*(clr + 1) = 255 - z * (255 / p.zmin);
		*(clr + 2) = 255 - z * (255 / p.zmin);
	}
	return (c);
}

int			*get_color_palette(int z_in, int z_fin, int nbpts, t_param p)
{
	int		*color;
	int		i;


	i = 0;
	if (!nbpts)
		return (NULL);
	int zdiff = z_fin - z_in;
	int varz = zdiff / nbpts;
	color = malloc(sizeof(int) * nbpts);
	while (i < nbpts)
	{
		color[i] = get_color(p, z_in);
		i++;
		z_in += varz;
	}
	return (color);
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
	int *color = get_color_palette(p0->z / p.r->ratio, p1->z / p.r->ratio, ft_max(dx, dy), p);
	while (x != p1->X || y != p1->Y)
	{
		draw_point(x, y, *color++, p);
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
