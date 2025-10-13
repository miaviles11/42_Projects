/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:09 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/08 22:00:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S')
		return (1);
	if (c == 'E' || c == 'W' || c == 'D' || c == '2')
		return (1);
	return (0);
}

static int	scan_chars_and_spawn(t_map *m, int *spawn)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			c = m->grid[y][x];
			if (!is_valid_char(c))
				return (-1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				(*spawn)++;
			x++;
		}
		y++;
	}
	return (0);
}

static int	check_closure(t_map *m)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (is_walkable(m->grid[y][x])
				&& touches_space_or_border(m, y, x))
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map(t_cub *cub)
{
	int	spawn;

	spawn = 0;
	if (scan_chars_and_spawn(&cub->map, &spawn))
		return (-1);
	if (spawn != 1)
		return (-1);
	if (check_closure(&cub->map))
		return (-1);
	return (0);
}
