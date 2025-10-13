/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:02:24 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:02:24 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

void	*load_from_mapdir(t_cub *c, t_texture *tex,
		const char *orig, char **out_path)
{
	void	*img;

	*out_path = NULL;
	if (!orig || orig[0] == '/')
		return (NULL);
	*out_path = path_join(c->map_dir, orig);
	if (!*out_path)
		return (NULL);
	img = try_load(c->mlx, *out_path, &tex->img.w, &tex->img.h);
	return (img);
}
