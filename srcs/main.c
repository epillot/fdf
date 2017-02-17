/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 12:27:29 by epillot           #+#    #+#             */
/*   Updated: 2017/02/17 19:50:03 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	void	*img;
	void	*win;
	t_map	*map;
	t_param	p;
	t_map	*line;

	if (ac != 2)
		return (1);
	p.mlx = mlx_init();
	win = mlx_new_window(p.mlx, 900, 900, "fdf");
	map = get_map(av[1]);
	img = mlx_new_image(p.mlx, 900, 900);
	p.data = mlx_get_data_addr(img, &p.bpp, &p.sizeline, &p.endian);
	ft_printf("bpp: %d\nsize_line: %d\nendian: %d\n", p.bpp, p.sizeline, p.endian);
	while (map)
	{
		line = map;
		while (line)
		{
			if (line->right)
				draw_segment(line, line->right, p);
			if (line->down)
				draw_segment(line, line->down, p);
			line = line->right;
		}
		map = map->down;
	}
	mlx_put_image_to_window(p.mlx, win, img, 0, 0);
	
	mlx_loop(p.mlx);
}
