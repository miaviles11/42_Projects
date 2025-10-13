/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_custom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:21 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:21 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_img	img_create(void *mlx, int w, int h)
{
	t_img	img;

	img.ptr = mlx_new_image(mlx, w, h);
	if (!img.ptr)
	{
		ft_bzero(&img, sizeof(t_img));
		return (img);
	}
	img.data = (int *)mlx_get_data_addr(img.ptr, &img.bpp,
			&img.line_len, &img.endian);
	img.w = w;
	img.h = h;
	return (img);
}

void	img_destroy(void *mlx, t_img *img)
{
	if (img && img->ptr)
	{
		mlx_destroy_image(mlx, img->ptr);
		ft_bzero(img, sizeof(t_img));
	}
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int	*dst;

	if (!img || !img->data)
		return ;
	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = img->data + y * (img->line_len / 4) + x;
	*dst = color;
}
