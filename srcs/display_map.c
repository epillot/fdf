/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:51 by epillot           #+#    #+#             */
/*   Updated: 2017/02/24 19:14:17 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_function(int keycode, void *param)
{
	t_param	*p;

	p = (t_param*)param;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	else if (keycode == 126 && p->r->prev)
	{
		p->r = p->r->prev;
		mlx_destroy_image(p->mlx, p->img);
		mlx_clear_window(p->mlx, p->win);
		display_map(p, 0);
	}
	else if (keycode == 125 && p->r->next)
	{
		p->r = p->r->next;
		mlx_destroy_image(p->mlx, p->img);
		mlx_clear_window(p->mlx, p->win);
		display_map(p, 0);
	}
	else if (keycode == 49)
	{
		if (p->proj == 0)
			p->proj = 1;
		else
			p->proj = 0;
		mlx_destroy_image(p->mlx, p->img);
		mlx_clear_window(p->mlx, p->win);
		display_map(p, 0);
	}
	/*else if (keycode == 78)
	{
		p->ratio_z *= -1;
		mlx_destroy_window(p->mlx, p->win);
		display_map(p, 1);
	}*/
	return (1);
}

static void	adjust_new_coord(t_map *map, t_param *p)
{
	t_map   *line;

	while ((p->xmax - p->xmin + 1) * p->coeff_x + 40 > WIDTH_MAX)
		p->coeff_x--;
	p->width = (p->xmax - p->xmin + 1) * p->coeff_x;
	while ((p->ymax - p->ymin + 1) * p->coeff_y + 40 > HEIGHT_MAX)
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
	p->zmax = INT_MIN;
	p->xmin = INT_MAX;
	p->ymin = INT_MAX;
	p->zmin = INT_MAX;
	p->coeff_x = 30;
	p->coeff_y = 30;
}

void		display_map(t_param *p, int win)
{
	t_map	*map;
	t_map	*line;

	init_param(p);
	get_iso_coord(p->map, p, p->proj);
	ft_putchar('a');
	adjust_new_coord(p->map, p);
//	ft_printf("ratio_z: %d\n", p->ratio_z);
	if (p->width <= 0 || p->height <= 0)
	{
		ft_printf("width: %d, height: %d\n", p->width, p->height);
		ft_putendl("map error");
		exit(EXIT_FAILURE);
	}
	ft_printf("zmin: %d, zmax: %d\n", p->zmin, p->zmax);
	if (win)
		p->win = mlx_new_window(p->mlx, WIDTH_MAX, HEIGHT_MAX, "fdf");
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
	mlx_put_image_to_window(p->mlx, p->win, p->img, (WIDTH_MAX - p->width) / 2, (HEIGHT_MAX - p->height) / 2);
	mlx_key_hook(p->win, &key_function, p);
	mlx_loop(p->mlx);
}
