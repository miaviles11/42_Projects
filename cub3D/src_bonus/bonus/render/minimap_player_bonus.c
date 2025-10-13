/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:11:56 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	draw_player_on_minimap(t_cub *c)
{
	int	player_x;
	int	player_y;
	int	dx;
	int	dy;
	int	radius;

	player_x = MINIMAP_PADDING + (c->player.pos.x * MINIMAP_SIZE) / c->map.w;
	player_y = MINIMAP_PADDING + (c->player.pos.y * MINIMAP_SIZE) / c->map.h;
	radius = 2;
	dy = -radius;
	while (dy <= radius)
	{
		dx = -radius;
		while (dx <= radius)
		{
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel_minimap(c, player_x + dx, player_y
					+ dy, COLOR_PLAYER);
			dx++;
		}
		dy++;
	}
}
