/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:59:03 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:59:03 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	img->data[y * (img->line_len / 4) + x] = color;
}

static void	draw_slice(t_cub *c, t_wall_draw *wd)
{
	int	y;
	int	tex_y;
	int	color;

	y = wd->start;
	while (y < wd->end)
	{
		tex_y = (int)wd->tex_pos & (TEX_SIZE - 1);
		color = tex_sample(c, wd->r->tex_id, wd->r->tex_x, tex_y);
		if (wd->r->side_hit == 1)
			color = (color >> 1) & 8355711;
		put_pixel(&c->screen, wd->x, y, color);
		wd->tex_pos += wd->step;
		++y;
	}
}

static void	init_wall_draw(t_wall_draw *wd, t_cub *c, int x, t_ray *r)
{
	int	line_h;
	int	jump_offset;

	wd->x = x;
	wd->r = r;
	line_h = (int)(WIN_H / r->dist);
	if (line_h < 1)
		line_h = 1;
	jump_offset = (int)(c->player.z_offset * JUMP_VISUAL_MULTIPLIER);
	wd->start = -line_h / 2 + WIN_H / 2 + jump_offset;
	if (wd->start < 0)
		wd->start = 0;
	wd->end = line_h / 2 + WIN_H / 2 + jump_offset;
	if (wd->end >= WIN_H)
		wd->end = WIN_H - 1;
	wd->step = (double)TEX_SIZE / line_h;
	wd->tex_pos = (wd->start - WIN_H / 2 - jump_offset + line_h / 2)
		* wd->step;
}

void	draw_walls(t_cub *c, int x, t_ray *r)
{
	t_wall_draw	wd;

	init_wall_draw(&wd, c, x, r);
	draw_slice(c, &wd);
}
