/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:50 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:50 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_floor_ceil(t_cub *cub)
{
	int	y;
	int	x;
	int	color;
	int	*dst;

	y = 0;
	while (y < WIN_H)
	{
		color = cub->ceil_color;
		if (y >= WIN_H / 2)
			color = cub->floor_color;
		x = 0;
		while (x < WIN_W)
		{
			dst = cub->screen.data
				+ y * (cub->screen.line_len / 4) + x;
			*dst = color;
			x++;
		}
		y++;
	}
}
