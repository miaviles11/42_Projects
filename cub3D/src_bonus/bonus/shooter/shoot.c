/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:57:41 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 11:18:29 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static int	sprite_at_cell(t_cub *c, int mx, int my)
{
	int	i;
	int	sx;
	int	sy;

	i = 0;
	while (i < c->sprites.count)
	{
		if (c->sprites.sprites[i].loaded)
		{
			sx = (int)c->sprites.sprites[i].pos.x;
			sy = (int)c->sprites.sprites[i].pos.y;
			if (sx == mx && sy == my)
				return (i);
		}
		i++;
	}
	return (-1);
}

static void	init_ray_direction(t_cub *c, t_ray *r)
{
	r->dir.x = c->player.dir.x;
	r->dir.y = c->player.dir.y;
	if (fabs(r->dir.x) < EPS)
	{
		if (r->dir.x < 0)
			r->dir.x = -EPS;
		else
			r->dir.x = EPS;
	}
	if (fabs(r->dir.y) < EPS)
	{
		if (r->dir.y < 0)
			r->dir.y = -EPS;
		else
			r->dir.y = EPS;
	}
	r->map_x = (int)c->player.pos.x;
	r->map_y = (int)c->player.pos.y;
	r->delta.x = fabs(1.0 / r->dir.x);
	r->delta.y = fabs(1.0 / r->dir.y);
}

static void	init_ray_steps(t_cub *c, t_ray *r)
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

void	ray_setup(t_cub *c, t_ray *r)
{
	init_ray_direction(c, r);
	init_ray_steps(c, r);
}

int	check_hit(t_cub *c, int mx, int my)
{
	int	idx;

	if (mx < 0 || my < 0 || mx >= c->map.w || my >= c->map.h)
		return (1);
	idx = sprite_at_cell(c, mx, my);
	if (idx >= 0)
	{
		c->sprites.sprites[idx].loaded = 0;
		c->enemies_alive--;
		if (c->enemies_alive <= 0)
			c->victory_timer = 20;
		return (1);
	}
	if (c->map.grid[my][mx] == '1' || c->map.grid[my][mx] == 'D')
		return (1);
	return (0);
}
