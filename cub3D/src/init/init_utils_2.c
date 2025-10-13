/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:23:25 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 16:23:25 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/* --- utils locales -------------------------------------------------------- */
int	is_nonempty_path(const char *s)
{
	return (s && s[0] != '\0');
}

void	*try_load(void *mlx, const char *path, int *w, int *h)
{
	if (!is_nonempty_path(path))
		return (NULL);
	if (!file_exists(path))
		return (NULL);
	return (mlx_xpm_file_to_image(mlx, (char *)path, w, h));
}

void	*load_direct(t_cub *c, t_texture *tex, const char *orig)
{
	return (try_load(c->mlx, orig, &tex->img.w, &tex->img.h));
}
