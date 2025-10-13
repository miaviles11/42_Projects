/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_physics_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:46:58 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:20 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static double	distance_to_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

static int	is_door_in_direction(t_cub *cub, t_door *door)
{
	double	dx;
	double	dy;
	double	dot;
	double	dist;

	dx = door->pos.x + 0.5 - cub->player.pos.x;
	dy = door->pos.y + 0.5 - cub->player.pos.y;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 1.5)
		return (0);
	dot = dx * cub->player.dir.x + dy * cub->player.dir.y;
	return (dot > 0.5);
}

static t_door	*find_closest_door(t_cub *cub)
{
	t_door	*closest;
	double	min_dist;
	double	dist;
	int		i;

	closest = NULL;
	min_dist = 2.0;
	i = 0;
	while (i < cub->doors.count)
	{
		if (is_door_in_direction(cub, &cub->doors.doors[i]))
		{
			dist = distance_to_point(cub->player.pos.x, cub->player.pos.y,
					cub->doors.doors[i].pos.x + 0.5, cub->doors.doors[i].pos.y
					+ 0.5);
			if (dist < min_dist)
			{
				min_dist = dist;
				closest = &cub->doors.doors[i];
			}
		}
		i++;
	}
	return (closest);
}

static void	toggle_door(t_cub *cub, t_door *door)
{
	int	player_x;
	int	player_y;

	if (door->is_open)
	{
		player_x = (int)cub->player.pos.x;
		player_y = (int)cub->player.pos.y;
		if (player_x == (int)door->pos.x && player_y == (int)door->pos.y)
			return ;
	}
	door->is_open = !door->is_open;
	if (door->is_open)
		cub->map.grid[(int)door->pos.y][(int)door->pos.x] = '0';
	else
		cub->map.grid[(int)door->pos.y][(int)door->pos.x] = 'D';
	cub->door_flash_timer = 15;
	cub->door_flash_x = (int)door->pos.x;
	cub->door_flash_y = (int)door->pos.y;
}

void	handle_door_interaction(t_cub *cub)
{
	t_door	*door;

	door = find_closest_door(cub);
	if (door)
		toggle_door(cub, door);
}
