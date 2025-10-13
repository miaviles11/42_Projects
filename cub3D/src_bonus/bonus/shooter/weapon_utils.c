/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:45:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/10 13:01:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	blit_scaled(t_blit_data *bd)
{
	int	y;

	if (!bd->dst || !bd->src || !bd->dst->data || !bd->src->data)
		return ;
	y = 0;
	while (y < bd->sh)
	{
		blit_row(bd, y);
		y++;
	}
}

void	weapon_draw(t_cub *c)
{
	t_blit_data	bd;
	t_img		*frame;

	if (init_weapon(c) != 0)
		return ;
	frame = &c->weapon.idle;
	if (c->weapon.fire_timer > 0)
		frame = &c->weapon.fire;
	ft_bzero(&bd, sizeof(t_blit_data));
	bd.dst = &c->screen;
	bd.src = frame;
	bd.sw = frame->w * WEAPON_SCALE;
	bd.sh = frame->h * WEAPON_SCALE;
	bd.ox = c->screen.w - bd.sw;
	bd.oy = c->screen.h - bd.sh;
	blit_scaled(&bd);
	if (c->weapon.fire_timer > 0)
		c->weapon.fire_timer--;
}
