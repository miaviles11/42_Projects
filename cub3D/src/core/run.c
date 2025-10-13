/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:35 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:35 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	step_init_mlx(t_cub *cub)
{
	if (init_mlx(cub))
		return (fail(cub,
				"Failed to initialize graphics (MiniLibX/display)"));
	return (0);
}

static int	step_init_textures(t_cub *cub)
{
	if (init_textures(cub))
		return (fail(cub,
				"Texture load failed: missing file or wrong size "
				"(64x64 required)"));
	return (0);
}

static int	step_init_player(t_cub *cub)
{
	if (init_player(cub))
		return (fail(cub,
				"Invalid map: missing or multiple player spawn"));
	return (0);
}

static int	step_set_hooks(t_cub *cub)
{
	if (set_hooks(cub))
		return (fail(cub, "Failed to install window hooks"));
	return (0);
}

int	cub3d_run(const char *map_path)
{
	t_cub	cub;

	if (init_basics(&cub, map_path))
		return (fail(&cub,
				"Out of memory while resolving map directory"));
	if (step_parse(&cub, map_path))
		return (-1);
	if (step_init_mlx(&cub))
		return (-1);
	if (step_init_textures(&cub))
		return (-1);
	if (step_init_player(&cub))
		return (-1);
	if (step_set_hooks(&cub))
		return (-1);
	mlx_loop(cub.mlx);
	cub_cleanup(&cub);
	return (0);
}
