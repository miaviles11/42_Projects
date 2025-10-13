/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_parse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:42:52 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:28 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

int	is_door_position(t_cub *c, int x, int y)
{
	int	i;

	i = 0;
	while (i < c->doors.count)
	{
		if ((int)c->doors.doors[i].pos.x == x
			&& (int)c->doors.doors[i].pos.y == y)
			return (1);
		i++;
	}
	return (0);
}

static int	init_door_list(t_door_list *doors)
{
	doors->capacity = 10;
	doors->doors = malloc(sizeof(t_door) * doors->capacity);
	if (!doors->doors)
		return (-1);
	doors->count = 0;
	return (0);
}

static int	add_door(t_door_list *doors, int x, int y)
{
	t_door	*new_doors;

	if (doors->count >= doors->capacity)
	{
		doors->capacity *= 2;
		new_doors = malloc(sizeof(t_door) * doors->capacity);
		if (!new_doors)
			return (-1);
		ft_memcpy(new_doors, doors->doors, sizeof(t_door) * doors->count);
		free(doors->doors);
		doors->doors = new_doors;
	}
	doors->doors[doors->count].pos.x = x;
	doors->doors[doors->count].pos.y = y;
	doors->doors[doors->count].is_open = 0;
	doors->doors[doors->count].original = 'D';
	doors->count++;
	return (0);
}

int	parse_doors(t_cub *cub)
{
	int	y;
	int	x;

	if (init_door_list(&cub->doors) == -1)
		return (-1);
	y = 0;
	while (y < cub->map.h)
	{
		x = 0;
		while (x < cub->map.w)
		{
			if (cub->map.grid[y][x] == 'D')
			{
				if (add_door(&cub->doors, x, y) == -1)
					return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
