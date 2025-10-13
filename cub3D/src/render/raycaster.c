/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:08 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:08 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Compute step and initial side distances for DDA.
*/
static void	set_step_side(t_cub *c, t_ray *r)
{
	if (r->dir.x < 0.0)
	{
		r->step_x = -1;
		r->side.x = (c->player.pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->map_x + 1.0 - c->player.pos.x) * r->delta.x;
	}
	if (r->dir.y < 0.0)
	{
		r->step_y = -1;
		r->side.y = (c->player.pos.y - r->map_y) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->side.y = (r->map_y + 1.0 - c->player.pos.y) * r->delta.y;
	}
}

/*
** Initialize ray for column x, fixing near-zero directions with EPS.
*/
static void	ray_init(t_cub *c, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2.0 * (double)x / (double)WIN_W - 1.0;
	r->dir.x = c->player.dir.x + c->player.plane.x * camera_x;
	r->dir.y = c->player.dir.y + c->player.plane.y * camera_x;
	if (fabs(r->dir.x) < EPS)
	{
		if (r->dir.x < 0.0)
			r->dir.x = -EPS;
		else
			r->dir.x = EPS;
	}
	if (fabs(r->dir.y) < EPS)
	{
		if (r->dir.y < 0.0)
			r->dir.y = -EPS;
		else
			r->dir.y = EPS;
	}
	r->map_x = (int)c->player.pos.x;
	r->map_y = (int)c->player.pos.y;
	r->delta.x = fabs(1.0 / r->dir.x);
	r->delta.y = fabs(1.0 / r->dir.y);
	set_step_side(c, r);
}

/*
** DDA grid traversal; sets side_hit and final corrected distance.
*/
static void	dda(t_cub *c, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
		hit = dda_step(c, r);
	dda_distance(c, r);
}

/*
** Texture selection and X coordinate on the texture.
*/
static void	set_tex_info(t_cub *c, t_ray *r)
{
	double	wall_x;

	if (r->side_hit == 0)
		wall_x = c->player.pos.y + r->dist * r->dir.y;
	else
		wall_x = c->player.pos.x + r->dist * r->dir.x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * (double)TEX_SIZE);
	if (r->side_hit == 0 && r->dir.x > 0.0)
		r->tex_id = DIR_WEST;
	else if (r->side_hit == 0)
		r->tex_id = DIR_EAST;
	else if (r->dir.y > 0.0)
		r->tex_id = DIR_NORTH;
	else
		r->tex_id = DIR_SOUTH;
}

/*
** Raycast each column and draw walls.
*/
void	raycaster(t_cub *cub)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		ray_init(cub, &r, x);
		dda(cub, &r);
		set_tex_info(cub, &r);
		draw_walls(cub, x, &r);
		x++;
	}
}
