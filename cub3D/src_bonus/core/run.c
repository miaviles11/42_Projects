/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:24 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:04:24 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	step_init_textures(t_cub *cub)
{
	if (init_textures(cub))
		return (fail(cub,
				"Texture load failed: missing file or wrong size "
				"(64x64 required)"));
	return (0);
}

static int	step_init_sprites(t_cub *cub)
{
	if (sprites_load_all(cub))
		return (fail(cub, "Sprite textures failed to load"));
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
		return (fail_and_cleanup(&cub,
				"Invalid scene file: bad identifiers or map format"));
	if (step_init_mlx(&cub))
		return (fail_and_cleanup(&cub,
				"Failed to initialize graphics (MiniLibX/display)"));
	if (step_init_textures(&cub))
		return (fail_and_cleanup(&cub,
				"Texture load failed: missing file or wrong size"));
	if (step_init_sprites(&cub))
		return (fail_and_cleanup(&cub, "Sprite textures failed to load"));
	if (step_init_player(&cub))
		return (fail_and_cleanup(&cub,
				"Invalid map: missing or multiple player spawn"));
	if (step_set_hooks(&cub))
		return (fail_and_cleanup(&cub, "Failed to install window hooks"));
	mlx_loop(cub.mlx);
	cub_cleanup(&cub);
	return (0);
}
