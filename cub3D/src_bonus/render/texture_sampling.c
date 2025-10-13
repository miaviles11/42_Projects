/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:58:49 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:58:49 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

/* -------------------------------------------------------------------------- */
/*	Return ARGB color from a 64×64 texture.									*/
/* -------------------------------------------------------------------------- */
int	tex_sample(t_cub *cub, int id, int x, int y)
{
	t_img	*im;
	int		sx;
	int		sy;

	if (id < 0 || id >= MAX_TEXTURES)
		return (0);
	im = &cub->textures[id].img;
	if (!im->data || im->w <= 0 || im->h <= 0)
		return (0);
	sx = x;
	if (im->w != TEX_SIZE)
		sx = (x * im->w) / TEX_SIZE;
	sy = y;
	if (im->h != TEX_SIZE)
		sy = (y * im->h) / TEX_SIZE;
	if (sx < 0 || sx >= im->w || sy < 0 || sy >= im->h)
		return (0);
	return (im->data[sy * (im->line_len / 4) + sx]);
}
