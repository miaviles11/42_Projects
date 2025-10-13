/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:29:59 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 15:29:59 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <sys/time.h>
# include <mlx.h>
# include "libft.h"

# include "defines.h"
# include "enums.h"
# include "structs.h"
# include "loop.h"
# include "mlx_custom.h"
# include "path_utils.h"

/* -------------------------------------------------------------------------- */
/*  High-level                                                                */
/* -------------------------------------------------------------------------- */
int			cub3d_run(const char *map_path);
void		cub_cleanup(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Init                                                                      */
/* -------------------------------------------------------------------------- */
int			init_mlx(t_cub *cub);
int			init_textures(t_cub *cub);
int			init_player(t_cub *cub);
int			init_map(t_cub *cub, const char *path);

/* -------------------------------------------------------------------------- */
/*  Timing                                                                    */
/* -------------------------------------------------------------------------- */
double		timer_delta(void);
void		timer_sleep(long target_fps, double dt);

/* -------------------------------------------------------------------------- */
/*  Parsing                                                                   */
/* -------------------------------------------------------------------------- */
int			parse_scene(t_cub *cub, const char *path);
int			parse_color_line(int *dst, char *l);
int			parse_texture_line(t_cub *cub, char *l);
int			normalize_map(t_map *map);
int			check_map(t_cub *cub);
int			is_map_line(const char *s);

/* -------------------------------------------------------------------------- */
/*  Utils (parse)                                                             */
/* -------------------------------------------------------------------------- */
char		*skip_spaces(char *s);
int			parse_int(const char **str, int *out);
int			validate_header_complete(t_cub *cub,
				int node_exists, int floor_set, int ceil_set);
int			scan_header(t_cub *cub, t_list **node,
				int *floor_set, int *ceil_set);
int			handle_header_line(t_cub *cub, char *s,
				int *floor_set, int *ceil_set);
int			handle_color_line(int *dst, int *flag, char *s);
int			all_textures_set(t_cub *cub);

/* -------------------------------------------------------------------------- */
/*  Utils (map)                                                               */
/* -------------------------------------------------------------------------- */
int			is_walk(char c);
int			out_of_bounds(t_map *m, int y, int x);

/* -------------------------------------------------------------------------- */
/*  Game logic                                                                */
/* -------------------------------------------------------------------------- */
int			movement_update(t_cub *cub);
int			is_wall(t_cub *c, double x, double y);
void		wall_slide_move(t_cub *c, double dx, double dy);
void		try_smooth_move(t_cub *c, double dx, double dy);
void		apply_wall_sliding(t_cub *c, double dx, double dy);
void		subdiv_move(t_cub *c, double total_dx, double total_dy);
int			check_collision_corners(t_cub *c, double x, double y, double r);
int			touches_space_or_border(t_map *m, int y, int x);
int			is_walkable(char c);
void		dda_distance(t_cub *c, t_ray *r);
int			dda_step(t_cub *c, t_ray *r);
void		gnl_drain(int fd);
int			is_blank_line(const char *s);
int			skip_to_map(int fd, char **line);
int			is_nonempty_path(const char *s);
void		*try_load(void *mlx, const char *path, int *w, int *h);
void		*load_direct(t_cub *c, t_texture *tex, const char *orig);
int			step_parse(t_cub *cub, const char *map_path);
int			init_basics(t_cub *cub, const char *map_path);

/* -------------------------------------------------------------------------- */
/*  Rendering                                                                 */
/* -------------------------------------------------------------------------- */
void		draw_floor_ceil(t_cub *cub);
void		raycaster(t_cub *cub);
int			tex_sample(t_cub *cub, int id, int x, int y);
void		draw_walls(t_cub *c, int x, t_ray *r);

/* -------------------------------------------------------------------------- */
/*  Utils (error / free)                                                      */
/* -------------------------------------------------------------------------- */
int			cub_error(t_cub *cub, const char *msg);
void		free_arr(char **arr);
int			is_point_wall(t_cub *c, double x, double y);
int			fail(t_cub *cub, const char *msg);

/* -------------------------------------------------------------------------- */
/*  Vector operations                                                         */
/* -------------------------------------------------------------------------- */
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_mul(t_vec v, double s);
double		vec_len(t_vec v);
t_vec		vec_norm(t_vec v);

/* -------------------------------------------------------------------------- */
/*  Math helpers                                                              */
/* -------------------------------------------------------------------------- */
double		ft_abs_d(double v);
double		ft_max_d(double a, double b);
double		ft_min_d(double a, double b);

#endif
