/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ratio.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 19:06:43 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 19:20:54 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_ratio	*new_ratio(int ra)
{
	t_ratio		*new;

	if (!(new = ft_memalloc(sizeof(t_ratio))))
		fdf_error(2, NULL);
	new->ratio = ra;
	return (new);
}

static void		go_to_good_pos(t_ratio **r, t_ratio **rprev, int ra)
{
	while (*r && (*r)->ratio < ra)
	{
		*rprev = *r;
		*r = (*r)->next;
	}
}

static void		add_ratio(t_ratio *r, int ra)
{
	t_ratio	*new;
	t_ratio	*tmp;

	go_to_good_pos(&r, &tmp, ra);
	if (!r)
	{
		if (tmp->ratio != ra)
		{
			new = new_ratio(ra);
			tmp->next = new;
			new->prev = tmp;
		}
	}
	else
	{
		if (r->ratio != ra)
		{
			new = new_ratio(ra);
			r->prev = new;
			new->next = r;
			tmp->next = new;
			new->prev = tmp;
		}
	}
}

void			get_ratio(int z, t_param *p)
{
	int		r;
	int		tmpz;
	int		rmax;

	r = 1;
	rmax = z + 1;
	tmpz = z;
	while (r != rmax)
	{
		r++;
		if ((int)(z / r) != tmpz)
		{
			add_ratio(p->r, r);
			tmpz = z / r;
		}
	}
}
