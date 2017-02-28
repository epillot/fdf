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

static void init_ratio(t_param *p)
{
	p->r = ft_memalloc(sizeof(t_ratio));
	p->r->ratio = 1;
}

static void get_full_ratio(t_ratio *r)
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
		new = ft_memalloc(sizeof(t_ratio));
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

	if (ac != 2)
		return (1);
	p.mlx = mlx_init();
	init_ratio(&p);
	p.ratio_z_max = 1;
	p.map = get_map(av[1], &p);
	get_full_ratio(p.r);
	ft_putstr("ratio:");
/*	while (p.r->next)
	{
		ft_printf("%d ", p.r->ratio);
		p.r = (p.r)->next;
	}
	while (p.r)
	{
		ft_printf("%d ", p.r->ratio);
		p.r = (p.r)->prev;
	}*/
	ft_putchar('\n');
	p.ratio_z_min = -(p.ratio_z_max);
	//p.ratio_z = 1;
//	ft_printf("ratio_z: %d, ratiozmin: %d, ratiozmax: %d\n", p.r->ratio, p.ratio_z_min, p.ratio_z_max);
	p.proj = 0;
	p.local_endian = get_local_endian();
	display_map(&p, 1);
	return (0);
}
