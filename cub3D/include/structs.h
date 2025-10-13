/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:15 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 15:30:15 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_ray
{
	t_vec	dir;
	t_vec	side;
	t_vec	delta;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side_hit;
	double	dist;
	int		tex_id;
	int		tex_x;
}	t_ray;

typedef struct s_grid_ctx
{
	char	***g;
	int		*h;
	int		*cap;
	int		*w;
}	t_grid_ctx;

typedef struct s_slice
{
	int		x;
	int		start;
	int		end;
	double	step;
	double	tex_pos;
}	t_slice;

typedef struct s_img
{
	void	*ptr;
	int		*data;
	int		w;
	int		h;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	t_img	img;
	char	*path;
}	t_texture;

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_texture	textures[4];
	t_map		map;
	t_player	player;
	t_keys		keys;
	int			floor_color;
	int			ceil_color;
	char		*map_dir;
}	t_cub;

#endif
