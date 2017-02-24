/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 12:27:29 by epillot           #+#    #+#             */
/*   Updated: 2017/02/24 15:11:25 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_local_endian(void)
{
	int		n;
	char	*ptr;

	n = 1;
	ptr = (char*)&n;
	if (*ptr == 1)
		return (0);
	return (1);
}

int			main(int ac, char **av)
{
	t_param	p;

	if (ac != 2)
		return (1);
	p.mlx = mlx_init();
	p.map = get_map(av[1]);
	p.ratio_z = 3;
	p.proj = 0;
	p.local_endian = get_local_endian();
	display_map(&p);
	return (0);
}
