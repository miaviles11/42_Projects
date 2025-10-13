/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_sampling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:10 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:10 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Return ARGB color from a 64x64 texture.
*/
int	tex_sample(t_cub *cub, int id, int x, int y)
{
	if (id < 0 || id >= 4)
		return (0);
	if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
		return (0);
	return (cub->textures[id].img.data[y * TEX_SIZE + x]);
}
