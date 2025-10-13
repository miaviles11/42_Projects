/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:59:08 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:59:08 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	draw_floor_ceil(t_cub *cub)
{
	int	y;
	int	x;
	int	color;
	int	*dst;
	int	horizon_line;

	horizon_line = WIN_H / 2 + (int)(cub->player.z_offset
			* JUMP_VISUAL_MULTIPLIER);
	y = 0;
	while (y < WIN_H)
	{
		color = cub->ceil_color;
		if (y >= horizon_line)
			color = cub->floor_color;
		x = 0;
		while (x < WIN_W)
		{
			dst = cub->screen.data + y * (cub->screen.line_len / 4) + x;
			*dst = color;
			++x;
		}
		++y;
	}
}
