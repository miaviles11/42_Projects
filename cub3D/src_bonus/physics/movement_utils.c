/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:59:33 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:59:33 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

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

void	try_smooth_move(t_cub *c, double dx, double dy)
{
	try_move_x(c, dx);
	try_move_y(c, dy);
}
