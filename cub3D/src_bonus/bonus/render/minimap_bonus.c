/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:14:58 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:32 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	put_pixel_minimap(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		cub->screen.data[y * (cub->screen.line_len / 4) + x] = color;
	}
}

void	draw_minimap_border(t_cub *c)
{
	int	x;
	int	y;

	y = MINIMAP_PADDING - 1;
	while (y <= MINIMAP_PADDING + MINIMAP_SIZE)
	{
		x = MINIMAP_PADDING - 1;
		while (x <= MINIMAP_PADDING + MINIMAP_SIZE)
		{
			if (y == MINIMAP_PADDING - 1 || y == MINIMAP_PADDING + MINIMAP_SIZE
				|| x == MINIMAP_PADDING - 1 || x == MINIMAP_PADDING
				+ MINIMAP_SIZE)
				put_pixel_minimap(c, x, y, COLOR_BORDER);
			x++;
		}
		y++;
	}
}

void	draw_minimap_content(t_cub *c)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;
	int	color;

	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			map_x = (x * c->map.w) / MINIMAP_SIZE;
			map_y = (y * c->map.h) / MINIMAP_SIZE;
			color = get_tile_color(c, map_x, map_y);
			put_pixel_minimap(c, MINIMAP_PADDING + x, MINIMAP_PADDING + y,
				color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *c)
{
	if (!c || !c->screen.data)
		return ;
	draw_minimap_border(c);
	draw_minimap_content(c);
	draw_player_on_minimap(c);
}
