/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:58:58 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:58:58 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

double	non_zero(double v)
{
	if (fabs(v) < EPS)
	{
		if (v < 0)
			return (-EPS);
		return (EPS);
	}
	return (v);
}

void	set_step_side(t_cub *c, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step_x = -1;
		r->side.x = (c->player.pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->side.x = (r->map_x + 1.0 - c->player.pos.x) * r->delta.x;
	}
	if (r->dir.y < 0)
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

void	set_ray_dist(t_cub *c, t_ray *r)
{
	if (r->side_hit == 0)
		r->dist = (r->map_x - c->player.pos.x + (1 - r->step_x) * 0.5)
			/ r->dir.x;
	else
		r->dist = (r->map_y - c->player.pos.y + (1 - r->step_y) * 0.5)
			/ r->dir.y;
	r->dist = fabs(r->dist);
	if (r->dist < EPS)
		r->dist = EPS;
}

void	set_tex_info(t_cub *c, t_ray *r)
{
	double	wall_x;
	char	tile;

	if (r->side_hit == 0)
		wall_x = c->player.pos.y + r->dist * r->dir.y;
	else
		wall_x = c->player.pos.x + r->dist * r->dir.x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * (double)TEX_SIZE);
	tile = c->map.grid[r->map_y][r->map_x];
	if (tile == 'D')
	{
		r->tex_id = DIR_DOOR;
		return ;
	}
	if (r->side_hit == 0 && r->dir.x > 0)
		r->tex_id = DIR_WEST;
	else if (r->side_hit == 0)
		r->tex_id = DIR_EAST;
	else if (r->dir.y > 0)
		r->tex_id = DIR_NORTH;
	else
		r->tex_id = DIR_SOUTH;
}
