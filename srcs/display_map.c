/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:05:51 by epillot           #+#    #+#             */
/*   Updated: 2017/02/22 19:07:14 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_function(int keycode, void *param)
{
	(void)param;
	if (keycode == 53)
		exit(EXIT_SUCCESS);
	return (0);
}

static void	get_screen_size(t_param *p)
{
	p->width = p->xmax - p->xmin + 2 * p->coeff;
	p->height = p->ymax - p->ymin + 2 * p->coeff;
	//if (p->width < WIDTH_MIN || p->height)
}

void		display_map(t_param *p)
{
	t_map	*map;
	t_map	*line;
//	char	*tmp;

	p->xmax = 0;
	p->ymax = 0;
	p->ymin = INT_MAX;
	p->xmin = INT_MAX;
	get_iso_coord(p->map, p);
	get_screen_size(p);
	ft_printf("xmax: %d, ymax: %d, xmin: %d, ymin: %d\n", p->xmax, p->ymax, p->xmin, p->ymin);
	ft_printf("width: %d, height: %d\n", p->width, p->height);
	p->win = mlx_new_window(p->mlx, p->width, p->height, "fdf");
	p->img = mlx_new_image(p->mlx, p->xmax, p->ymax);
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
	mlx_put_image_to_window(p->mlx, p->win, p->img, -(p->xmin) + p->coeff, -(p->ymin) + p->coeff);
	mlx_key_hook(p->win, &key_function, p);
	mlx_loop(p->mlx);
}
