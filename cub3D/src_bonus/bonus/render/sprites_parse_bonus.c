/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:15:47 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 11:00:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static int	init_sprite_list(t_sprite_list *sprites)
{
	sprites->capacity = 20;
	sprites->sprites = malloc(sizeof(t_sprite) * sprites->capacity);
	if (!sprites->sprites)
		return (-1);
	sprites->count = 0;
	return (0);
}

static int	add_sprite(t_cub *cub, int x, int y)
{
	t_sprite	*new_sprites;
	t_sprite	*sprite;

	if (cub->sprites.count >= cub->sprites.capacity)
	{
		cub->sprites.capacity *= 2;
		new_sprites = malloc(sizeof(t_sprite) * cub->sprites.capacity);
		if (!new_sprites)
			return (-1);
		ft_memcpy(new_sprites, cub->sprites.sprites,
			sizeof(t_sprite) * cub->sprites.count);
		free(cub->sprites.sprites);
		cub->sprites.sprites = new_sprites;
	}
	sprite = &cub->sprites.sprites[cub->sprites.count];
	sprite->pos.x = x + 0.5;
	sprite->pos.y = y + 0.5;
	sprite->texture_ids = NULL;
	sprite->frame_count = 0;
	sprite->frame_current = 0;
	sprite->last_update = 0;
	sprite->loaded = 0;
	cub->sprites.count++;
	return (0);
}

int	parse_sprites(t_cub *cub)
{
	int	y;
	int	x;

	if (init_sprite_list(&cub->sprites) == -1)
		return (-1);
	y = 0;
	while (y < cub->map.h)
	{
		x = 0;
		while (x < cub->map.w)
		{
			if (cub->map.grid[y][x] == '2')
			{
				if (add_sprite(cub, x, y) == -1)
					return (-1);
				cub->map.grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	cub->enemies_alive = cub->sprites.count;
	cub->victory = 0;
	cub->victory_timer = 0;
	return (0);
}
