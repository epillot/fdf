/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:15:00 by epillot           #+#    #+#             */
/*   Updated: 2017/02/22 18:50:15 by epillot          ###   ########.fr       */
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

# define WIDTH_MIN 512
# define HEIGHT_MIN 512
# define WIDTH_MAX 2048
# define HEIGHT_MAX 2048

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
	int		offset;
	int		xmax;
	int		ymax;
	int		xmin;
	int		ymin;
	int		ratio_z;
	int		coeff;
	int		bpp;
	int		sizeline;
	int		endian;
}				t_param;

t_map			*get_map(char *file, t_param *p);
void			draw_segment(t_map *point1, t_map *point2, t_param p);
void			display_map(t_param *p);
void			get_iso_coord(t_map *map, t_param *p);

#endif
