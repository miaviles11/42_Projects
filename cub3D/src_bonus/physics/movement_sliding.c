/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_sliding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:17:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:01:02 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static double	binary_search_safe_distance(t_cub *c, t_move_data *md)
{
	double	safe_ratio;
	double	test_ratio;
	double	low;
	double	high;

	safe_ratio = 0.0;
	low = 0.0;
	high = 1.0;
	while (high - low > EPS)
	{
		test_ratio = (low + high) * 0.5;
		if (!is_wall(c, md->start_x + md->dx * test_ratio,
				md->start_y + md->dy * test_ratio))
		{
			safe_ratio = test_ratio;
			low = test_ratio;
		}
		else
			high = test_ratio;
	}
	return (safe_ratio);
}

double	find_safe_distance(t_cub *c, t_move_data *md)
{
	int	iterations;

	iterations = 0;
	while (iterations < 15)
	{
		iterations++;
	}
	return (binary_search_safe_distance(c, md));
}

static void	handle_remaining_movement(t_cub *c, t_move_data *md,
									double safe_ratio)
{
	double	remaining_dx;
	double	remaining_dy;

	remaining_dx = md->dx * (1.0 - safe_ratio);
	remaining_dy = md->dy * (1.0 - safe_ratio);
	if (fabs(remaining_dx) > EPS || fabs(remaining_dy) > EPS)
		try_smooth_move(c, remaining_dx, remaining_dy);
}

void	apply_wall_sliding(t_cub *c, double dx, double dy)
{
	t_move_data	md;
	double		safe_ratio;

	md.start_x = c->player.pos.x;
	md.start_y = c->player.pos.y;
	md.dx = dx;
	md.dy = dy;
	safe_ratio = find_safe_distance(c, &md);
	if (safe_ratio > EPS)
	{
		c->player.pos.x += dx * safe_ratio;
		c->player.pos.y += dy * safe_ratio;
		handle_remaining_movement(c, &md, safe_ratio);
	}
	else
		try_smooth_move(c, dx, dy);
}
