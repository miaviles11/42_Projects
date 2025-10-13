/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:30:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:59:13 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static int	step_and_check_hit(t_cub *c, t_ray *r)
{
	int	mx;
	int	my;

	if (r->side.x < r->side.y)
	{
		r->side.x += r->delta.x;
		r->map_x += r->step_x;
	}
	else
	{
		r->side.y += r->delta.y;
		r->map_y += r->step_y;
	}
	mx = r->map_x;
	my = r->map_y;
	return (check_hit(c, mx, my));
}

void	shoot_try(t_cub *c)
{
	t_ray	r;
	int		stop;

	ray_setup(c, &r);
	stop = 0;
	while (!stop)
		stop = step_and_check_hit(c, &r);
}
