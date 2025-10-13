/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:02:57 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:02:57 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	init_map_builder(t_map_builder *mb, t_cub *cub, int cap)
{
	mb->grid = cub->map.grid;
	mb->h = 0;
	mb->w = 0;
	mb->cap = cap;
}

static void	finalize_map(t_cub *cub, t_map_builder *mb)
{
	cub->map.grid = mb->grid;
	cub->map.h = mb->h;
	cub->map.w = mb->w;
	cub->map.grid[cub->map.h] = NULL;
}

int	init_map(t_cub *cub, const char *path)
{
	int				fd;
	t_map_builder	mb;

	mb.cap = 16;
	cub->map.grid = (char **)malloc(sizeof(char *) * (mb.cap + 1));
	if (!cub->map.grid)
		return (-1);
	init_map_builder(&mb, cub, mb.cap);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read_map(fd, &mb))
		return (close(fd), -1);
	finalize_map(cub, &mb);
	close(fd);
	return (normalize_map(&cub->map));
}
