/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:26 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:26 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* ------------------------------------------------------------------------ */
static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/* ------------------------------------------------------------------------ */
static void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->textures[i].img.ptr)
			mlx_destroy_image(cub->mlx, cub->textures[i].img.ptr);
		free(cub->textures[i].path);
		i++;
	}
}

/* ------------------------------------------------------------------------ */
void	cub_cleanup(t_cub *cub)
{
	if (!cub)
		return ;
	free(cub->map_dir);
	free_grid(cub->map.grid);
	free_textures(cub);
	if (cub->screen.ptr)
		mlx_destroy_image(cub->mlx, cub->screen.ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}
