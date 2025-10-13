/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:31:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/10 13:21:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ========================================================================== */
/*                                INCLUDES                                    */
/* ========================================================================== */

# include "defines.h"
# include "enums.h"
# include "libft.h"
# include "loop.h"
# include "mlx_custom.h"
# include "path_utils.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* ========================================================================== */
/*                          MAIN & CLEANUP                                    */
/* ========================================================================== */

/*run.c*/
int				cub3d_run(const char *map_path);

/*core_utils.c*/
int				init_basics(t_cub *cub, const char *map_path);
int				fail(t_cub *cub, const char *msg);
int				step_init_mlx(t_cub *cub);
int				step_parse(t_cub *cub, const char *map_path);
int				fail_and_cleanup(t_cub *cub, const char *msg);

/* cleanup_utils.c */
void			free_grid(char **grid, int height);
void			free_textures(t_cub *cub);
void			free_sprites(t_cub *cub);
void			free_weapon(t_cub *cub);

/* cleanup.c */
void			cub_cleanup(t_cub *cub);
void			cleanup_game_resources(t_cub *cub);
void			cleanup_memory_resources(t_cub *cub);
void			cleanup_graphics_resources(t_cub *cub);

/*loop.c*/
int				loop_hook(void *param);

/* victory_display.c */
void			draw_enemy_counter_box(t_cub *cub);
void			draw_enemy_counter_text(t_cub *cub);

/* victory_display_utils.c */
void			draw_victory_box(t_cub *cub);
void			draw_victory_text(t_cub *cub);

/* ========================================================================== */
/*                          INITIALIZATION                                    */
/* ========================================================================== */

/* init_mlx.c / init_player.c */
int				init_mlx(t_cub *cub);
int				init_player(t_cub *cub);

/* init_textures.c */
int				load_tex(t_cub *c, t_texture *tex, char *orig);
int				init_textures(t_cub *cub);

/* init_textures_utils_1.c */
int				is_nonempty_path(const char *s);
void			*try_load(void *mlx, const char *path, int *w, int *h);
void			*load_direct(t_cub *c, t_texture *tex, const char *orig);
int				skip_to_map(int fd, char **line);
void			gnl_drain(int fd);
int				is_blank_line(const char *s);

/* init_textures_utils_2.c */
void			*load_from_mapdir(t_cub *c, t_texture *tex, const char *orig,
					char **out_path);

/* init_map.c */
int				grow_grid(char ***grid, int *cap);
char			*trim_line(char *dup);
int				push_line(char *src, t_map_builder *mb);
int				skip_to_map(int fd, char **line);
int				read_map(int fd, t_map_builder *mb);

/* init_map_utils.c */
int				init_map(t_cub *cub, const char *path);

/* ========================================================================== */
/*                          PARSING                                           */
/* ========================================================================== */

/* parse_scene.c */
int				parse_scene(t_cub *cub, const char *path);
int				parse_color_line(int *dst, char *l);
int				parse_texture_line(t_cub *cub, char *l);

/* parse_map.c */
int				normalize_map(t_map *map);
int				check_map(t_cub *cub);
int				is_map_line(const char *s);

/* parse_objects.c */
int				parse_doors(t_cub *cub);
int				parse_sprites(t_cub *cub);

/* parse_utils.c */
char			*skip_spaces(char *s);
int				parse_int(const char **str, int *out);

/*process_meta_helpers.c*/
int				scan_header(t_cub *cub, t_list **node, int *floor_set,
					int *ceil_set);
int				validate_header_complete(t_cub *cub, int node_exists,
					int floor_set, int ceil_set);

/* ========================================================================== */
/*                          MAP UTILITIES                                     */
/* ========================================================================== */

int				is_walk(char c);
int				out_of_bounds(t_map *m, int y, int x);
int				is_walkable(char c);
int				touches_space_or_border(t_map *m, int y, int x);

/* ========================================================================== */
/*                          TEXTURE MANAGEMENT                                */
/* ========================================================================== */

int				init_texture_array(t_cub *cub);
int				add_texture_to_array(t_cub *cub, t_texture *tex);
int				tex_sample(t_cub *cub, int id, int x, int y);

/* ========================================================================== */
/*                          PHYSICS & MOVEMENT                                */
/* ========================================================================== */

/* movement.c */
void			rotate_player(t_player *p, double angle);
void			move(t_cub *c, double dx, double dy);
int				movement_update(t_cub *c);

/* movement_jump.c */
void			init_jump(t_player *player);
void			update_jump(t_cub *c);

/* movement_collision.c */
int				is_wall(t_cub *c, double x, double y);
void			wall_slide_move(t_cub *c, double dx, double dy);

/*sprite_collision_bonus.c*/
int				check_sprite_collision(t_cub *c, double x, double y);

/* movement_smooth.c */
void			subdivide_movement_steps(t_cub *c, double total_dx,
					double total_dy, int steps);
void			subdiv_move(t_cub *c, double total_dx, double total_dy);

/*movement_utils.c*/
void			try_smooth_move(t_cub *c, double dx, double dy);

/* movement_sliding.c */
double			find_safe_distance(t_cub *c, t_move_data *md);
void			apply_wall_sliding(t_cub *c, double dx, double dy);

/* ========================================================================== */
/*                          DOORS SYSTEM                                      */
/* ========================================================================== */

void			handle_door_interaction(t_cub *cub);
int				is_door_position(t_cub *c, int x, int y);

/* ========================================================================== */
/*                          SPRITES SYSTEM                                    */
/* ========================================================================== */

/* sprites_load.c */
int				load_texture_image(t_cub *cub, const char *path, int index);
char			*create_sprite_path(int frame_index);
int				load_single_frame(t_cub *cub, t_sprite *sprite, int i,
					int *counter);
void			init_sprite_data(t_sprite *sprite);
int				load_sprite_frames(t_cub *cub, t_sprite *sprite,
					int *tex_counter);

/* sprites_load_utils.c */
void			init_fallback_sprite(t_sprite *sprite);
int				load_sprite_safe(t_cub *cub, t_sprite *sprite,
					int *tex_counter);
int				sprites_load_all(t_cub *cub);

/* sprites_draw_bonus.c */
void			draw_sprites(t_cub *cub, int frame);

/* sprites_render_bonus.c */
void			put_pixel_sprite(t_cub *cub, int x, int y, int color);
void			init_sprite_params(t_sprite_params *p, t_cub *c, t_sprite *sp,
					int screen_x);
void			draw_vertical_line(t_cub *c, t_sprite *sp, t_sprite_params *p,
					int x);
void			process_stripe_column(t_cub *c, t_sprite *sp,
					t_sprite_params *p, int x);
void			draw_sprite_stripe(t_cub *c, t_sprite *sp, int screen_x,
					t_draw_params dp);

/* sprites_render_utils_bonus.c */
void			init_render_params(t_render_params *rp, t_cub *cub,
					double transform_x, double transform_y);
void			init_draw_params(t_draw_params *dp, t_render_params *rp);
void			render_sprite_column(t_cub *cub, t_sprite *sprite,
					double transform_x, double transform_y);

/* ========================================================================== */
/*                          SPRITE ORDERING STRUCTURES                        */
/* ========================================================================== */
typedef struct s_sprite_order
{
	t_sprite	*sprite;
	double		distance;
	double		transform_x;
	double		transform_y;
}				t_sprite_order;

/* ========================================================================== */
/*                          SHOOTING SYSTEM                                   */
/* ========================================================================== */

/* shoot.c */
void			ray_setup(t_cub *c, t_ray *r);
int				check_hit(t_cub *c, int mx, int my);

/* shoot_utils.c */
void			shoot_try(t_cub *c);

/* crosshair_bonus.c */
void			draw_crosshair(t_cub *c);

/* ========================================================================== */
/*                          WEAPON SYSTEM                                     */
/* ========================================================================== */

/* weapon.c */
int				load_weapon_img(void *mlx, const char *path, t_img *out);
int				init_weapon(t_cub *c);
void			weapon_on_click(t_cub *c);
void			draw_pixel_scaled(t_blit_data *bd, int x, int y);
void			blit_row(t_blit_data *bd, int y);

/* weapon_utils.c */
void			blit_scaled(t_blit_data *bd);
void			weapon_draw(t_cub *c);

/* ========================================================================== */
/*                          INPUT HANDLING                                    */
/* ========================================================================== */

/* mouse_bonus.c */
int				set_hooks(t_cub *cub);
int				mouse_move(int x, int y, void *param);
int				mouse_press(int button, int x, int y, void *param);

/* ========================================================================== */
/*                          RENDERING - CORE                                  */
/* ========================================================================== */

/* raycaster.c */
void			raycaster(t_cub *cub);
double			non_zero(double v);
void			set_step_side(t_cub *c, t_ray *r);
void			set_ray_dist(t_cub *c, t_ray *r);
void			set_tex_info(t_cub *c, t_ray *r);

/* draw_walls.c */
void			draw_walls(t_cub *c, int x, t_ray *r);

/* draw_floor_ceil.c */
void			draw_floor_ceil(t_cub *cub);

/* ========================================================================== */
/*                          RENDERING - MINIMAP                               */
/* ========================================================================== */

void			put_pixel_minimap(t_cub *cub, int x, int y, int color);
void			draw_minimap_border(t_cub *c);
int				get_tile_color(t_cub *c, int map_x, int map_y);
void			draw_minimap_content(t_cub *c);
void			draw_minimap(t_cub *c);
void			draw_player_on_minimap(t_cub *c);

/* ========================================================================== */
/*                          TIMING                                            */
/* ========================================================================== */

/* core */
double			timer_delta(void);
void			timer_sleep(long target_fps, double dt);

/* ========================================================================== */
/*                          UTILITIES - MATH                                  */
/* ========================================================================== */

/* vector_ops.c */
t_vec			vec_add(t_vec a, t_vec b);
t_vec			vec_mul(t_vec v, double s);
double			vec_len(t_vec v);
t_vec			vec_norm(t_vec v);

/* math_utils.c */
double			ft_abs_d(double v);
double			ft_max_d(double a, double b);
double			ft_min_d(double a, double b);

/* ========================================================================== */
/*                          UTILITIES - ERROR & MEMORY                        */
/* ========================================================================== */

int				cub_error(t_cub *cub, const char *msg);
void			free_arr(char **arr);

#endif