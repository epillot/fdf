/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epillot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 16:15:00 by epillot           #+#    #+#             */
/*   Updated: 2017/02/28 18:48:51 by epillot          ###   ########.fr       */
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
# include <errno.h>

# define WIDTH 1024
# define HEIGHT 512

typedef struct	s_map
{
	int				x;
	int				y;
	int				z;
	int				xx;
	int				yy;
	struct s_map	*right;
	struct s_map	*down;
}				t_map;

typedef struct	s_ratio
{
	int				ratio;
	struct s_ratio	*prev;
	struct s_ratio	*next;
}				t_ratio;

typedef struct	s_segment
{
	int				dx;
	int				dy;
	int				e1;
	int				e2;
	int				xi;
	int				yi;
	double				zi;
	int				x;
	int				y;
	double				z;

}				t_segment;

typedef struct	s_param
{
	void			*mlx;
	void			*win;
	void			*img;
	t_map			*map;
	char			*data;
	int				width;
	int				height;
	int				xmax;
	int				ymax;
	int				zmax;
	int				xmin;
	int				ymin;
	int				zmin;
	int				coeff_x;
	int				coeff_y;
	int				proj;
	t_ratio			*r;
	int				bpp;
	int				sizeline;
	int				endian;
	int				local_endian;
}				t_param;

t_map			*get_map(int fd, t_param *p);
void			draw_map(t_param p);
void			display_map(t_param *p, int first);
void			get_new_coord(t_map *map, t_param *p, int proj);
void			get_ratio(int z, t_param *p);
void			fdf_error(int errnum, char *file);

#endif
