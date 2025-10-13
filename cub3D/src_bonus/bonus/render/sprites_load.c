/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:15:47 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

int	load_texture_image(t_cub *cub, const char *path, int index)
{
	t_texture	*tex;
	void		*img;
	int			w;
	int			h;

	if (index >= MAX_TEXTURES)
		return (-1);
	tex = &cub->textures[index];
	img = mlx_xpm_file_to_image(cub->mlx, (char *)path, &w, &h);
	if (!img)
		return (-1);
	tex->img.ptr = img;
	tex->img.w = w;
	tex->img.h = h;
	tex->img.data = (int *)mlx_get_data_addr(img, &tex->img.bpp,
			&tex->img.line_len, &tex->img.endian);
	if (!tex->img.data)
	{
		mlx_destroy_image(cub->mlx, img);
		return (-1);
	}
	return (0);
}

char	*create_sprite_path(int frame_index)
{
	char	*num_str;
	char	*temp;
	char	*path;

	num_str = ft_itoa(frame_index);
	if (!num_str)
		return (NULL);
	temp = ft_strjoin("./assets/textures/enemy_idle_", num_str);
	free(num_str);
	if (!temp)
		return (NULL);
	path = ft_strjoin(temp, ".xpm");
	free(temp);
	return (path);
}

int	load_single_frame(t_cub *cub, t_sprite *sprite, int i, int *counter)
{
	char	*path;

	path = create_sprite_path(i);
	if (!path)
	{
		sprite->texture_ids[i] = DIR_NORTH;
		return (0);
	}
	if (load_texture_image(cub, path, *counter) == -1)
	{
		sprite->texture_ids[i] = DIR_NORTH;
		free(path);
		return (0);
	}
	sprite->texture_ids[i] = *counter;
	(*counter)++;
	free(path);
	return (0);
}

void	init_sprite_data(t_sprite *sprite)
{
	sprite->frame_count = SPRITE_FRAMES;
	sprite->frame_current = 0;
	sprite->last_update = 0;
	sprite->loaded = 1;
}

int	load_sprite_frames(t_cub *cub, t_sprite *sprite, int *tex_counter)
{
	int		i;

	sprite->texture_ids = malloc(sizeof(int) * SPRITE_FRAMES);
	if (!sprite->texture_ids)
		return (-1);
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		load_single_frame(cub, sprite, i, tex_counter);
		i++;
	}
	init_sprite_data(sprite);
	return (0);
}
