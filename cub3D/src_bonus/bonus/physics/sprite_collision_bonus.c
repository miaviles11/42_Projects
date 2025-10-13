/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_collision_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:08:41 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

int	check_sprite_collision(t_cub *c, double x, double y)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < c->sprites.count)
	{
		if (c->sprites.sprites[i].loaded)
		{
			dx = fabs(x - c->sprites.sprites[i].pos.x);
			dy = fabs(y - c->sprites.sprites[i].pos.y);
			if (dx < SPRITE_SIZE && dy < SPRITE_SIZE)
				return (1);
		}
		i++;
	}
	return (0);
}
