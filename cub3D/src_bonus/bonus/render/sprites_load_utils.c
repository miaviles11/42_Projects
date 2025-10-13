/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_load_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:00:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:48 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	init_fallback_sprite(t_sprite *sprite)
{
	int	j;

	j = 0;
	while (j < SPRITE_FRAMES)
	{
		sprite->texture_ids[j] = DIR_NORTH;
		j++;
	}
	sprite->frame_count = SPRITE_FRAMES;
	sprite->loaded = 1;
}

int	load_sprite_safe(t_cub *cub, t_sprite *sprite, int *tex_counter)
{
	if (load_sprite_frames(cub, sprite, tex_counter) == -1)
	{
		sprite->texture_ids = malloc(sizeof(int) * SPRITE_FRAMES);
		if (sprite->texture_ids)
			init_fallback_sprite(sprite);
		return (-1);
	}
	return (0);
}

int	sprites_load_all(t_cub *cub)
{
	int			i;
	int			tex_counter;
	t_sprite	*sprite;

	tex_counter = 10;
	i = 0;
	while (i < cub->sprites.count)
	{
		sprite = &cub->sprites.sprites[i];
		if (!sprite->loaded)
			load_sprite_safe(cub, sprite, &tex_counter);
		i++;
	}
	return (0);
}
