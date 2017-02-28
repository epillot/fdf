#include "fdf.h"

void	add_ratio(t_ratio *r, int ra)
{
	t_ratio *new;
	t_ratio *tmp;

	new = ft_memalloc(sizeof(t_ratio));
	new->ratio = ra;
	while (r && r->ratio < ra)
	{
		tmp = r;
		r = r->next;
	}
	if (!r)
	{
		if (tmp->ratio != ra)
		{
			tmp->next = new;
			new->prev = tmp;
		}
		else
			free(new);
	}
	else
	{
		if (r->ratio != ra)
		{
			r->prev = new;
			new->next = r;
			tmp->next = new;
			new->prev = tmp;	
		}
		else
			free(new);
	}
}

void	get_ratio(int z, t_param *p)
{
	int r;
	int tmpz;
	int rmax;

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
