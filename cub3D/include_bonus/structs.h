/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:55:21 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 10:58:54 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* ========================================================================== */
/*                          BASIC STRUCTURES                                  */
/* ========================================================================== */

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

/* ========================================================================== */
/*                          IMAGE & TEXTURE STRUCTURES                        */
/* ========================================================================== */

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

/* ========================================================================== */
/*                          MAP STRUCTURES                                    */
/* ========================================================================== */

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}	t_map;

typedef struct s_map_builder
{
	char	**grid;
	int		h;
	int		w;
	int		cap;
}	t_map_builder;

/* ========================================================================== */
/*                          PLAYER STRUCTURES                                 */
/* ========================================================================== */

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	double	z_offset;
	double	jump_speed;
	int		is_jumping;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	space;
	int	e;
}	t_keys;

/* ========================================================================== */
/*                          MOVEMENT STRUCTURES                               */
/* ========================================================================== */

typedef struct s_move_data
{
	double	start_x;
	double	start_y;
	double	dx;
	double	dy;
}	t_move_data;

/* ========================================================================== */
/*                          RAYCASTING STRUCTURES                             */
/* ========================================================================== */

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

typedef struct s_wall_draw
{
	int		x;
	t_ray	*r;
	int		start;
	int		end;
	double	step;
	double	tex_pos;
}	t_wall_draw;

/* ========================================================================== */
/*                          DOOR STRUCTURES                                   */
/* ========================================================================== */

typedef struct s_door
{
	t_vec	pos;
	int		is_open;
	char	original;
}	t_door;

typedef struct s_door_list
{
	t_door	*doors;
	int		count;
	int		capacity;
}	t_door_list;

/* ========================================================================== */
/*                          SPRITE STRUCTURES                                 */
/* ========================================================================== */

typedef struct s_sprite
{
	t_vec	pos;
	int		frame_current;
	int		frame_count;
	int		*texture_ids;
	double	distance;
	int		last_update;
	int		loaded;
}	t_sprite;

typedef struct s_sprite_list
{
	t_sprite	*sprites;
	int			count;
	int			capacity;
}	t_sprite_list;

/* ========================================================================== */
/*                          SPRITE RENDERING STRUCTURES                       */
/* ========================================================================== */

typedef struct s_sprite_params
{
	int		start_x;
	int		end_x;
	double	ty;
	int		jump_offset;
	int		v_move_screen;
	int		tex_x;
	double	v_step;
	double	v_pos;
	int		sprite_w;
	int		sprite_h;
	int		start_y;
	int		end_y;
}	t_sprite_params;

typedef struct s_draw_params
{
	int	sprite_w;
	int	sprite_h;
	int	start_y;
	int	end_y;
}	t_draw_params;

typedef struct s_render_params
{
	int	sprite_screen_x;
	int	sprite_h;
	int	sprite_w;
	int	jump_offset;
	int	v_move_screen;
}	t_render_params;

/* ========================================================================== */
/*                          WEAPON STRUCTURES                                 */
/* ========================================================================== */

typedef struct s_weapon
{
	t_img	idle;
	t_img	fire;
	int		fire_timer;
	int		initialized;
}	t_weapon;

typedef struct s_blit_data
{
	t_img	*dst;
	t_img	*src;
	int		ox;
	int		oy;
	int		sw;
	int		sh;
}	t_blit_data;

/* ========================================================================== */
/*                          MAIN STRUCTURE                                    */
/* ========================================================================== */

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			screen;
	t_texture		textures[MAX_TEXTURES];
	int				texture_count;
	t_map			map;
	t_player		player;
	t_keys			keys;
	t_door_list		doors;
	t_sprite_list	sprites;
	t_weapon		weapon;
	double			*z_buffer;
	int				floor_color;
	int				ceil_color;
	char			*map_dir;
	int				door_flash_timer;
	int				door_flash_x;
	int				door_flash_y;
	int				mouse_x;
	int				first_mouse;
	int				enemies_alive;
	int				victory;
	int				victory_timer;
}	t_cub;

#endif