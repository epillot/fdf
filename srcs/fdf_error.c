/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 18:38:45 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 18:49:08 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error(int errnum, char *file)
{
	if (errnum == 0)
		ft_printf_fd(2, "fdf: %s: %s\n", file, strerror(errno));
	else if (errnum == 1)
		ft_putendl_fd("Not a valid file", 2);
	else
		ft_putendl_fd("A malloc error occured", 2);
	exit(EXIT_FAILURE);
}
