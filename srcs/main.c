/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 12:27:29 by epillot           #+#    #+#             */
/*   Updated: 2017/02/22 19:07:12 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int ac, char **av)
{
	t_param	p;

	if (ac != 2)
		return (1);
	p.offset = 0;
	p.ratio_z = 1;
	p.map = get_map(av[1], &p);
	ft_printf("%d\n", p.offset);
	p.mlx = mlx_init();
	p.coeff = 5;
	display_map(&p);
	return (0);
}
