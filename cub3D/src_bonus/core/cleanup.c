/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:51 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/10 13:10:33 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	cleanup_memory_resources(t_cub *cub)
{
	if (cub->z_buffer)
	{
		free(cub->z_buffer);
		cub->z_buffer = NULL;
	}
	if (cub->doors.doors)
	{
		free(cub->doors.doors);
		cub->doors.doors = NULL;
	}
	if (cub->map.grid)
	{
		free_grid(cub->map.grid, cub->map.h);
		cub->map.grid = NULL;
	}
	if (cub->map_dir)
	{
		free(cub->map_dir);
		cub->map_dir = NULL;
	}
}

void	cleanup_graphics_resources(t_cub *cub)
{
	free_sprites(cub);
	free_weapon(cub);
	free_textures(cub);
	if (cub->screen.ptr && cub->mlx)
	{
		mlx_destroy_image(cub->mlx, cub->screen.ptr);
		cub->screen.ptr = NULL;
	}
}

void	cleanup_game_resources(t_cub *cub)
{
	if (!cub)
		return ;
	cleanup_memory_resources(cub);
	cleanup_graphics_resources(cub);
}

void	cub_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	cleanup_game_resources(cub);
	if (cub->mlx)
	{
		if (cub->win)
			mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
}

int	fail_and_cleanup(t_cub *cub, const char *msg)
{
	int	ret;

	ret = fail(cub, msg);
	cub_cleanup(cub);
	return (ret);
}
