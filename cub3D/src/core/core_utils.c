/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:15:20 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 16:15:20 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* Inicializa el estado base y recuerda el directorio del mapa */
int	init_basics(t_cub *cub, const char *map_path)
{
	ft_bzero(cub, sizeof(t_cub));
	cub->map_dir = ft_dirname(map_path);
	if (!cub->map_dir)
		return (-1);
	return (0);
}

int	fail(t_cub *cub, const char *msg)
{
	cub_error(cub, msg);
	return (-1);
}

int	step_parse(t_cub *cub, const char *map_path)
{
	if (parse_scene(cub, map_path))
		return (fail(cub,
				"Invalid scene file: bad identifiers or map format"));
	return (0);
}
