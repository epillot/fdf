/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 12:27:29 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 19:25:03 by epillot          ###   ########.fr       */
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

static void	init_ratio(t_param *p)
{
	if (!(p->r = ft_memalloc(sizeof(t_ratio))))
		fdf_error(2, NULL);
	p->r->ratio = 1;
}

static void	get_full_ratio(t_ratio *r)
{
	t_ratio *tmp1;
	t_ratio *tmp2;
	t_ratio *new;

	tmp1 = r;
	while (tmp1->next)
		tmp1 = tmp1->next;
	tmp2 = tmp1->prev;
	while (tmp2)
	{
		if (!(new = ft_memalloc(sizeof(t_ratio))))
			fdf_error(2, NULL);
		new->ratio = -(tmp2->ratio);
		new->prev = tmp1;
		tmp1->next = new;
		tmp1 = tmp1->next;
		tmp2 = tmp2->prev;
	}
}

int			main(int ac, char **av)
{
	t_param	p;
	int		fd;

	if (ac != 2)
	{
		ft_putendl_fd("usage: ./fdf <filename>", 2);
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) <= 0)
		fdf_error(0, av[1]);
	init_ratio(&p);
	if (!(p.map = get_map(fd, &p)))
		fdf_error(1, NULL);
	get_full_ratio(p.r);
	p.proj = 0;
	p.local_endian = get_local_endian();
	p.mlx = mlx_init();
	display_map(&p, 1);
}
