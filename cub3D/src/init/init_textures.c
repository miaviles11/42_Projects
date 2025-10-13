/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:02 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:40:02 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	*load_from_mapdir(t_cub *c, t_texture *tex,
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

static void	*load_from_parent(t_cub *c, t_texture *tex,
		const char *orig, char **out_path)
{
	char	*parent;
	void	*img;

	*out_path = NULL;
	if (!orig || orig[0] == '/')
		return (NULL);
	parent = ft_path_parent(c->map_dir);
	if (!parent)
		return (NULL);
	*out_path = path_join(parent, orig);
	free(parent);
	if (!*out_path)
		return (NULL);
	img = try_load(c->mlx, *out_path, &tex->img.w, &tex->img.h);
	return (img);
}

static int	store_texture(t_texture *tex, void *img)
{
	tex->img.ptr = img;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.data)
		return (-1);
	return (0);
}

/* --- carga una textura ---------------------------------------------------- */
static int	load_tex(t_cub *c, t_texture *tex, char *orig)
{
	void	*img;
	char	*p_mapdir;
	char	*p_parent;

	img = NULL;
	p_mapdir = NULL;
	p_parent = NULL;
	if (!c || !tex || !is_nonempty_path(orig))
		return (-1);
	if (!img)
		img = load_direct(c, tex, orig);
	if (!img)
		img = load_from_mapdir(c, tex, orig, &p_mapdir);
	if (!img)
		img = load_from_parent(c, tex, orig, &p_parent);
	free(p_mapdir);
	free(p_parent);
	if (!img || tex->img.w != TEX_SIZE || tex->img.h != TEX_SIZE)
	{
		if (img)
			mlx_destroy_image(c->mlx, img);
		return (-1);
	}
	return (store_texture(tex, img));
}

/* --- público -------------------------------------------------------------- */
int	init_textures(t_cub *cub)
{
	int	i;

	if (!cub)
		return (-1);
	i = 0;
	while (i < 4)
	{
		if (load_tex(cub, &cub->textures[i], cub->textures[i].path))
			return (-1);
		i++;
	}
	return (0);
}
