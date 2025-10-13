/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static void	put_crosshair_pixel(t_cub *c, int x, int y)
{
	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
		c->screen.data[y * (c->screen.line_len / 4) + x] = CROSSHAIR_COLOR;
}

static void	draw_crosshair_center(t_cub *c, int cx, int cy)
{
	put_crosshair_pixel(c, cx, cy);
	put_crosshair_pixel(c, cx - 1, cy);
	put_crosshair_pixel(c, cx + 1, cy);
	put_crosshair_pixel(c, cx, cy - 1);
	put_crosshair_pixel(c, cx, cy + 1);
}

static void	draw_crosshair_lines(t_cub *c, int cx, int cy)
{
	int	i;
	int	gap;
	int	length;

	gap = CROSSHAIR_GAP;
	length = CROSSHAIR_LENGTH;
	i = 0;
	while (i < length)
	{
		put_crosshair_pixel(c, cx - gap - length + i, cy);
		put_crosshair_pixel(c, cx + gap + i, cy);
		put_crosshair_pixel(c, cx, cy - gap - length + i);
		put_crosshair_pixel(c, cx, cy + gap + i);
		i++;
	}
}

void	draw_crosshair(t_cub *c)
{
	int	center_x;
	int	center_y;

	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	draw_crosshair_center(c, center_x, center_y);
	draw_crosshair_lines(c, center_x, center_y);
}
