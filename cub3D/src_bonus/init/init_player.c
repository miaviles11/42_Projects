/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:02:37 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:02:37 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	set_plane(t_player *p)
{
	if (p->dir.x == -1)
		p->plane = (t_vec){0, FOV};
	else if (p->dir.x == 1)
		p->plane = (t_vec){0, -FOV};
	else if (p->dir.y == -1)
		p->plane = (t_vec){FOV, 0};
	else
		p->plane = (t_vec){-FOV, 0};
}

static void	set_dir_from_char(t_vec *dir, char c)
{
	dir->x = 0;
	dir->y = 0;
	if (c == 'E')
		dir->x = 1;
	else if (c == 'W')
		dir->x = -1;
	else if (c == 'S')
		dir->y = 1;
	else if (c == 'N')
		dir->y = -1;
}

static void	init_bonus_features(t_cub *cub)
{
	init_jump(&cub->player);
	cub->door_flash_timer = 0;
	cub->door_flash_x = 0;
	cub->door_flash_y = 0;
}

static int	try_spawn(t_cub *cub, int y, int x)
{
	char	c;

	c = cub->map.grid[y][x];
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	cub->player.pos = (t_vec){x + 0.5, y + 0.5};
	cub->map.grid[y][x] = '0';
	set_dir_from_char(&cub->player.dir, c);
	set_plane(&cub->player);
	init_bonus_features(cub);
	return (1);
}

int	init_player(t_cub *cub)
{
	int	y;
	int	x;

	if (!cub)
		return (-1);
	y = 0;
	while (y < cub->map.h)
	{
		x = 0;
		while (x < cub->map.w)
		{
			if (try_spawn(cub, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (-1);
}
