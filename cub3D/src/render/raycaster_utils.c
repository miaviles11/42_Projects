/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:02:54 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 16:02:54 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Advance one DDA step; return 1 if wall hit.
*/
int	dda_step(t_cub *c, t_ray *r)
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
	if (c->map.grid[r->map_y][r->map_x] == '1')
		return (1);
	return (0);
}

/*
** Compute corrected distance after DDA traversal.
*/
void	dda_distance(t_cub *c, t_ray *r)
{
	if (r->side_hit == 0)
		r->dist = (r->map_x - c->player.pos.x
				+ (1 - r->step_x) * 0.5) / r->dir.x;
	else
		r->dist = (r->map_y - c->player.pos.y
				+ (1 - r->step_y) * 0.5) / r->dir.y;
	r->dist = fabs(r->dist);
	if (r->dist < EPS)
		r->dist = EPS;
}
