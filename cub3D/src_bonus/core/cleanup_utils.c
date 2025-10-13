/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:56 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:04:56 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	free_grid(char **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		if (grid[i])
			free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_textures(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (cub->mlx && cub->textures[i].img.ptr)
		{
			mlx_destroy_image(cub->mlx, cub->textures[i].img.ptr);
			cub->textures[i].img.ptr = NULL;
		}
		if (cub->textures[i].path)
		{
			free(cub->textures[i].path);
			cub->textures[i].path = NULL;
		}
		i++;
	}
	cub->texture_count = 0;
}

void	free_sprites(t_cub *cub)
{
	int	i;

	if (!cub || !cub->sprites.sprites)
		return ;
	i = 0;
	while (i < cub->sprites.count)
	{
		if (cub->sprites.sprites[i].texture_ids)
		{
			free(cub->sprites.sprites[i].texture_ids);
			cub->sprites.sprites[i].texture_ids = NULL;
		}
		i++;
	}
	free(cub->sprites.sprites);
	cub->sprites.sprites = NULL;
	cub->sprites.count = 0;
}

void	free_weapon(t_cub *cub)
{
	if (!cub || !cub->mlx || !cub->weapon.initialized)
		return ;
	if (cub->weapon.idle.ptr)
		mlx_destroy_image(cub->mlx, cub->weapon.idle.ptr);
	if (cub->weapon.fire.ptr)
		mlx_destroy_image(cub->mlx, cub->weapon.fire.ptr);
}
