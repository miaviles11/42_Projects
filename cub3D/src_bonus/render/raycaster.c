/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:58:53 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:58:53 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	ray_init(t_cub *c, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIN_W - 1.0;
	r->dir.x = non_zero(c->player.dir.x + c->player.plane.x * camera_x);
	r->dir.y = non_zero(c->player.dir.y + c->player.plane.y * camera_x);
	r->map_x = (int)c->player.pos.x;
	r->map_y = (int)c->player.pos.y;
	r->delta.x = fabs(1.0 / r->dir.x);
	r->delta.y = fabs(1.0 / r->dir.y);
	set_step_side(c, r);
}

static void	dda(t_cub *c, t_ray *r)
{
	int		hit;
	char	tile;

	hit = 0;
	while (!hit)
	{
		if (r->side.x < r->side.y)
		{
			r->side.x += r->delta.x;
			r->map_x += r->step_x;
			r->side_hit = 0;
		}
		else
		{
			r->side.y += r->delta.y;
			r->map_y += r->step_y;
			r->side_hit = 1;
		}
		tile = c->map.grid[r->map_y][r->map_x];
		if (tile == '1' || tile == 'D')
			hit = 1;
	}
	set_ray_dist(c, r);
}

void	raycaster(t_cub *cub)
{
	t_ray	r;
	int		x;

	if (!cub->z_buffer)
		return ;
	x = 0;
	while (x < WIN_W)
	{
		cub->z_buffer[x] = 1000.0;
		x++;
	}
	x = 0;
	while (x < WIN_W)
	{
		ray_init(cub, &r, x);
		dda(cub, &r);
		set_tex_info(cub, &r);
		draw_walls(cub, x, &r);
		cub->z_buffer[x] = r.dist;
		++x;
	}
}
