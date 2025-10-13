/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_collision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:09:49 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:00:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	is_point_wall(t_cub *c, double x, double y)
{
	char	tile;

	if (y < 0 || y >= c->map.h || x < 0 || x >= c->map.w)
		return (1);
	tile = c->map.grid[(int)y][(int)x];
	if (tile == '1' || tile == 'D')
		return (1);
	return (check_sprite_collision(c, x, y));
}

static int	check_collision_corners(t_cub *c, double x, double y, double radius)
{
	if (is_point_wall(c, x - radius, y - radius) || is_point_wall(c, x + radius,
			y - radius) || is_point_wall(c, x - radius, y + radius)
		|| is_point_wall(c, x + radius, y + radius))
		return (1);
	return (0);
}

static int	check_collision_edges(t_cub *c, double x, double y, double radius)
{
	if (is_point_wall(c, x, y - radius) || is_point_wall(c, x, y + radius)
		|| is_point_wall(c, x - radius, y) || is_point_wall(c, x + radius, y))
		return (1);
	return (0);
}

int	is_wall(t_cub *c, double x, double y)
{
	double	radius;

	radius = COLLISION_RADIUS;
	if (x - radius < 0 || x + radius >= c->map.w || y - radius < 0 || y
		+ radius >= c->map.h)
		return (1);
	if (is_point_wall(c, x, y))
		return (1);
	if (check_collision_edges(c, x, y, radius))
		return (1);
	if (check_collision_corners(c, x, y, radius))
		return (1);
	return (0);
}

void	wall_slide_move(t_cub *c, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = c->player.pos.x + dx;
	ny = c->player.pos.y + dy;
	if (!is_wall(c, nx, ny))
	{
		c->player.pos.x = nx;
		c->player.pos.y = ny;
		return ;
	}
	if (!is_wall(c, nx, c->player.pos.y))
		c->player.pos.x = nx;
	else if (!is_wall(c, c->player.pos.x, ny))
		c->player.pos.y = ny;
}
