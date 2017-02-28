/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:51 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 19:06:04 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	process_key(int keycode, int *display, t_param *p)
{
	if (keycode == 126 && p->r->prev)
	{
		p->r = p->r->prev;
		*display = 1;
	}
	else if (keycode == 125 && p->r->next)
	{
		p->r = p->r->next;
		*display = 1;
	}
	else if (keycode == 49)
	{
		if (p->proj == 0)
			p->proj = 1;
		else
			p->proj = 0;
		*display = 1;
	}
}

static int	key_function(int keycode, void *param)
{
	t_param	*p;
	int		display;

	display = 0;
	p = (t_param*)param;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	process_key(keycode, &display, p);
	if (display)
	{
		mlx_destroy_image(p->mlx, p->img);
		mlx_clear_window(p->mlx, p->win);
		display_map(p, 0);
	}
	return (1);
}

static void	get_new_size(t_map *map, t_param *p)
{
	t_map	*line;

	while ((p->xmax - p->xmin + 1) * p->coeff_x + 40 > WIDTH)
		p->coeff_x--;
	p->width = (p->xmax - p->xmin + 1) * p->coeff_x;
	while ((p->ymax - p->ymin + 1) * p->coeff_y + 40 > HEIGHT)
		p->coeff_y--;
	p->height = (p->ymax - p->ymin + 1) * p->coeff_y;
	while (map)
	{
		line = map;
		while (line)
		{
			line->xx = (line->xx - p->xmin) * p->coeff_x;
			line->yy = (line->yy - p->ymin) * p->coeff_y;
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
	init_param(p);
	get_new_coord(p->map, p, p->proj);
	get_new_size(p->map, p);
	if (p->width <= 0 || p->height <= 0)
		fdf_error(1, NULL);
	if (win)
		p->win = mlx_new_window(p->mlx, WIDTH, HEIGHT, "fdf");
	p->img = mlx_new_image(p->mlx, p->width, p->height);
	p->data = mlx_get_data_addr(p->img, &p->bpp, &p->sizeline, &p->endian);
	draw_map(*p);
	mlx_put_image_to_window(p->mlx, p->win, p->img, (WIDTH - p->width) / 2,
			(HEIGHT - p->height) / 2);
	mlx_key_hook(p->win, &key_function, p);
	mlx_loop(p->mlx);
}
