/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:15:00 by epillot           #+#    #+#             */
/*   Updated: 2017/02/24 15:29:30 by epillot          ###   ########.fr       */
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
# include <limits.h>

# define WIDTH_MAX 2048
# define HEIGHT_MAX 1024

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
	void	*win;
	void	*img;
	t_map	*map;
	char	*data;
	int		width;
	int		height;
	int		xmax;
	int		ymax;
	int		zmax;
	int		xmin;
	int		ymin;
	int		zmin;
	int		ratio_z;
	int		coeff_x;
	int		coeff_y;
	int		proj;
	int		bpp;
	int		sizeline;
	int		endian;
	int		local_endian;
}				t_param;

t_map			*get_map(char *file);
void			draw_segment(t_map *point1, t_map *point2, t_param p);
void			display_map(t_param *p);
void			get_iso_coord(t_map *map, t_param *p, int proj);

#endif
