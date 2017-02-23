/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:51 by epillot           #+#    #+#             */
/*   Updated: 2017/02/23 19:50:54 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_function(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	else if (keycode == 126)
	{
		if (p->ratio_z > 1)
		{
			p->ratio_z--;
			mlx_destroy_window(p->mlx, p->win);
			display_map(p);
		}
	}
	else if (keycode == 125)
	{
		if (p->ratio_z < 10)
		{
			p->ratio_z++;
			mlx_destroy_window(p->mlx, p->win);
			display_map(p);
		}
	}
	else if (keycode == 49)
	{
		if (p->proj == 0)
			p->proj = 1;
		else
			p->proj = 0;
		mlx_destroy_window(p->mlx, p->win);
		display_map(p);
	}
	return (1);
}

static void	adjust_new_coord(t_map *map, t_param *p)
{
	t_map   *line;

	while ((p->xmax - p->xmin) * p->coeff_x > WIDTH_MAX)
		p->coeff_x--;
	p->width = (p->xmax - p->xmin + 1) * p->coeff_x;
	while ((p->ymax - p->ymin) * p->coeff_y > HEIGHT_MAX)
		p->coeff_y--;
	p->height = (p->ymax - p->ymin + 1) * p->coeff_y;
	while (map)
	{
		line = map;
		while (line)
		{
			line->X = (line->X - p->xmin) * p->coeff_x;
			line->Y = (line->Y - p->ymin) * p->coeff_y;
			line = line->right;
		}
		map = map->down;
	}
}

static void	init_param(t_param *p)
{
	p->xmax = 0;
	p->ymax = 0;
	p->xmin = INT_MAX;
	p->ymin = INT_MAX;
	p->coeff_x = 20;
	p->coeff_y = 20;
}

void		display_map(t_param *p)
{
	t_map	*map;
	t_map	*line;

	init_param(p);
	get_iso_coord(p->map, p, p->proj);
	adjust_new_coord(p->map, p);
//	ft_printf("zmin: %d, zmax: %d\n", p->zmin, p->zmax);
	p->win = mlx_new_window(p->mlx, p->width + p->coeff_x, p->height + p->coeff_y, "fdf");
	p->img = mlx_new_image(p->mlx, p->width, p->height);
	p->data = mlx_get_data_addr(p->img, &p->bpp, &p->sizeline, &p->endian);
	map = p->map;
	while (map)
	{
		line = map;
		while (line)
		{
			if (line->right)
				draw_segment(line, line->right, *p);
			if (line->down)
				draw_segment(line, line->down, *p);
			line = line->right;
		}
		map = map->down;
	}
	mlx_put_image_to_window(p->mlx, p->win, p->img, p->coeff_x, p->coeff_y);
	mlx_key_hook(p->win, &key_function, p);
	mlx_loop(p->mlx);
}
