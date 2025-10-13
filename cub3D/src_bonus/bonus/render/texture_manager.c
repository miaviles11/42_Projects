/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:05:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:59:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

int	init_texture_array(t_cub *cub)
{
	cub->texture_count = 0;
	return (0);
}

int	add_texture_to_array(t_cub *cub, t_texture *tex)
{
	if (cub->texture_count >= MAX_TEXTURES)
		return (-1);
	cub->textures[cub->texture_count] = *tex;
	cub->texture_count++;
	return (cub->texture_count - 1);
}
