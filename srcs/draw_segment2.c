/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 13:01:52 by epillot           #+#    #+#             */
/*   Updated: 2017/02/22 14:06:10 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_segment(t_map *point1, t_map *point2, t_param p)
{
	int x1 = point1->X;
	int x2 = point2->X;
	int y1 = point1->Y;
	int y2 = point2->Y;
	int ex = ft_abs(x2 - x1);
	int ey = ft_abs(y2 - y1);
	int dx = 2 * ex;
	int dy = 2 * ey;
	int Dx = ex;
	int Dy = ey;
	int i = 0;
	int xi = (x1 > x2 ? -1 : 1);
	int yi = (y1 > y2 ? -1 : 1);
	char *tmp;

	if (Dx > Dy)
	{
		while (i <= Dx)
		{
			tmp = p.data + x1 * p.bpp / 8 + y1 * p.sizeline;
			*(int*)tmp = mlx_get_color_value(p.mlx, 0x00ffffff);
			i++;
			x1 += xi;
			ex -= dy;
			if (ex < 0)
			{
				y1 += yi;
				ex += dx;
			}
		}
	}
	else
	{
		while (i <= Dy)
		{
			tmp = p.data + x1 * p.bpp / 8 + y1 * p.sizeline;
			*(int*)tmp = mlx_get_color_value(p.mlx, 0x00ffffff);
			i++;
			y1 += yi;
			ey -= dx;
			if (ey < 0)
			{
				x1 += xi;
				ey += dy;
			}
		}
	}
}
