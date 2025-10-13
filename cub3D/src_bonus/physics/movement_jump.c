/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_jump.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 20:15:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 22:00:50 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	init_jump(t_player *player)
{
	player->z_offset = 0.0;
	player->jump_speed = 0.0;
	player->is_jumping = 0;
}

static void	start_jump(t_player *player)
{
	if (!player->is_jumping)
	{
		player->jump_speed = JUMP_INITIAL_SPEED;
		player->is_jumping = 1;
	}
}

static void	apply_gravity(t_player *player)
{
	player->z_offset += player->jump_speed;
	player->jump_speed -= GRAVITY;
	if (player->z_offset <= 0.0)
	{
		player->z_offset = 0.0;
		player->jump_speed = 0.0;
		player->is_jumping = 0;
	}
}

void	update_jump(t_cub *c)
{
	if (c->keys.space)
		start_jump(&c->player);
	if (c->player.is_jumping)
		apply_gravity(&c->player);
}
