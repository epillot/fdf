/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:15:00 by epillot           #+#    #+#             */
/*   Updated: 2017/02/17 19:34:19 by epillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "libft.h"
# include "mlx.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_map
{
	int				x;
	int				y;
	int				z;
	int				X;
	int				Y;
	struct s_map	*right;
	struct s_map	*down;
}				t_map;

typedef struct	s_param
{
	void	*mlx;
	char	*data;
	int		bpp;
	int		sizeline;
	int		endian;
}				t_param;

t_map			*get_map(char *file);
void			draw_segment(t_map *point1, t_map *point2, t_param p);

#endif
