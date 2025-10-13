/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:44 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:44 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	try_move_x(t_cub *c, double dx)
{
	double	nx;

	if (fabs(dx) < EPS)
		return ;
	nx = c->player.pos.x + dx;
	if (!is_wall(c, nx, c->player.pos.y))
		c->player.pos.x = nx;
}

static void	try_move_y(t_cub *c, double dy)
{
	double	ny;

	if (fabs(dy) < EPS)
		return ;
	ny = c->player.pos.y + dy;
	if (!is_wall(c, c->player.pos.x, ny))
		c->player.pos.y = ny;
}

/*
** Smooth axis-by-axis movement (for residuals after collision)
*/
void	try_smooth_move(t_cub *c, double dx, double dy)
{
	try_move_x(c, dx);
	try_move_y(c, dy);
}

int	check_collision_corners(t_cub *c, double x, double y, double r)
{
	if (is_point_wall(c, x - r, y - r)
		|| is_point_wall(c, x + r, y - r)
		|| is_point_wall(c, x - r, y + r)
		|| is_point_wall(c, x + r, y + r))
		return (1);
	return (0);
}
