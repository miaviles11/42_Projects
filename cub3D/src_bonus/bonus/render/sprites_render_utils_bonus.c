/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:50:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:59:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	init_render_params(t_render_params *rp, t_cub *cub,
		double transform_x, double transform_y)
{
	rp->sprite_screen_x = (int)((WIN_W / 2.0) * (1.0 + transform_x
				/ transform_y));
	rp->sprite_h = (int)fabs((WIN_H / transform_y) * SPRITE_SCALE);
	if (rp->sprite_h < 1)
		rp->sprite_h = 1;
	rp->sprite_w = rp->sprite_h;
	rp->jump_offset = (int)(cub->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	rp->v_move_screen = (int)(SPRITE_VMOVE / transform_y);
}

void	init_draw_params(t_draw_params *dp, t_render_params *rp)
{
	dp->start_y = -rp->sprite_h / 2 + WIN_H / 2 + rp->jump_offset
		+ rp->v_move_screen;
	if (dp->start_y < 0)
		dp->start_y = 0;
	dp->end_y = rp->sprite_h / 2 + WIN_H / 2 + rp->jump_offset
		+ rp->v_move_screen;
	if (dp->end_y >= WIN_H)
		dp->end_y = WIN_H - 1;
	dp->sprite_w = rp->sprite_w;
	dp->sprite_h = rp->sprite_h;
}

void	render_sprite_column(t_cub *cub, t_sprite *sprite, double transform_x,
		double transform_y)
{
	t_render_params	rp;
	t_draw_params	dp;

	sprite->distance = transform_y;
	init_render_params(&rp, cub, transform_x, transform_y);
	init_draw_params(&dp, &rp);
	draw_sprite_stripe(cub, sprite, rp.sprite_screen_x, dp);
}
