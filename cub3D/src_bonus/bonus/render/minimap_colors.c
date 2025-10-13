/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:39 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static int	get_base_tile_color(char tile)
{
	if (tile == '1')
		return (COLOR_WALL);
	else if (tile == 'D')
		return (COLOR_DOOR);
	else if (tile == 'S' || tile == 'T' || tile == 'E')
		return (COLOR_SPRITE);
	return (COLOR_SPACE);
}

static int	handle_empty_tile(t_cub *c, int map_x, int map_y)
{
	if (is_door_position(c, map_x, map_y))
		return (COLOR_DOOR_OPEN);
	return (COLOR_SPACE);
}

static int	check_sprite_at_position(t_cub *c, int map_x, int map_y)
{
	int	i;

	i = 0;
	while (i < c->sprites.count)
	{
		if (c->sprites.sprites[i].loaded
			&& (int)c->sprites.sprites[i].pos.x == map_x
			&& (int)c->sprites.sprites[i].pos.y == map_y)
			return (1);
		i++;
	}
	return (0);
}

int	get_tile_color(t_cub *c, int map_x, int map_y)
{
	char	tile;
	int		base_color;

	if (map_x < 0 || map_x >= c->map.w || map_y < 0 || map_y >= c->map.h)
		return (COLOR_WALL);
	if (check_sprite_at_position(c, map_x, map_y))
		return (COLOR_SPRITE);
	tile = c->map.grid[map_y][map_x];
	if (tile == '0')
		base_color = handle_empty_tile(c, map_x, map_y);
	else
		base_color = get_base_tile_color(tile);
	if (c->door_flash_timer > 0 && map_x == c->door_flash_x
		&& map_y == c->door_flash_y)
		return (0xFFFFFF);
	return (base_color);
}
