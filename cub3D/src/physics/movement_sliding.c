/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_sliding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:33 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:33 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Binary search for the largest safe fraction of the displacement.
*/
static double	binary_search_safe_distance(t_cub *c, t_vec pos, t_vec d)
{
	double	low;
	double	high;
	double	safe;
	double	mid;

	low = 0.0;
	high = 1.0;
	safe = 0.0;
	while (high - low > EPS)
	{
		mid = 0.5 * (low + high);
		if (!is_wall(c, pos.x + d.x * mid, pos.y + d.y * mid))
		{
			safe = mid;
			low = mid;
		}
		else
			high = mid;
	}
	return (safe);
}

/*
** Extension point;
*/
static double	find_safe_distance(t_cub *c, t_vec pos, t_vec d)
{
	return (binary_search_safe_distance(c, pos, d));
}

static void	handle_remaining_movement(t_cub *c, double dx, double dy, double t)
{
	double	rx;
	double	ry;

	rx = dx * (1.0 - t);
	ry = dy * (1.0 - t);
	if (fabs(rx) > EPS || fabs(ry) > EPS)
		try_smooth_move(c, rx, ry);
}

/*
** PUBLIC: apply smooth wall sliding on partial collision.
*/
void	apply_wall_sliding(t_cub *c, double dx, double dy)
{
	t_vec	pos;
	t_vec	d;
	double	t;

	pos = c->player.pos;
	d.x = dx;
	d.y = dy;
	t = find_safe_distance(c, pos, d);
	if (t > EPS)
	{
		c->player.pos.x += dx * t;
		c->player.pos.y += dy * t;
		handle_remaining_movement(c, dx, dy, t);
	}
	else
		try_smooth_move(c, dx, dy);
}
