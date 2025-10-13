/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:58:03 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/10 13:21:38 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

int	load_weapon_img(void *mlx, const char *path, t_img *out)
{
	void	*ptr;

	ft_bzero(out, sizeof(t_img));
	ptr = mlx_xpm_file_to_image(mlx, (char *)path, &out->w, &out->h);
	if (!ptr)
		return (-1);
	out->ptr = ptr;
	out->data = (int *)mlx_get_data_addr(ptr, &out->bpp,
			&out->line_len, &out->endian);
	if (!out->data)
	{
		mlx_destroy_image(mlx, ptr);
		out->ptr = NULL;
		return (-1);
	}
	return (0);
}

int	init_weapon(t_cub *c)
{
	if (c->weapon.initialized)
		return (0);
	if (load_weapon_img(c->mlx, "./assets/ui/weapon_idle.xpm",
			&c->weapon.idle))
		return (-1);
	if (load_weapon_img(c->mlx, "./assets/ui/weapon_fire.xpm",
			&c->weapon.fire))
		return (-1);
	c->weapon.fire_timer = 0;
	c->weapon.initialized = 1;
	return (0);
}

void	weapon_on_click(t_cub *c)
{
	if (init_weapon(c) == 0)
		c->weapon.fire_timer = WFIRE_TICKS;
}

void	draw_pixel_scaled(t_blit_data *bd, int x, int y)
{
	int	pd;
	int	ps;
	int	sx;
	int	sy;
	int	color;	

	pd = bd->dst->line_len / 4;
	ps = bd->src->line_len / 4;
	sy = (y * bd->src->h) / bd->sh;
	sx = (x * bd->src->w) / bd->sw;
	color = bd->src->data[sy * ps + sx];
	if ((color & 0x00FFFFFF) != 0)
		bd->dst->data[(bd->oy + y) * pd + (bd->ox + x)] = color;
}

void	blit_row(t_blit_data *bd, int y)
{
	int	x;

	if (bd->oy + y < 0 || bd->oy + y >= bd->dst->h)
		return ;
	x = 0;
	while (x < bd->sw)
	{
		if (bd->ox + x >= 0 && bd->ox + x < bd->dst->w)
			draw_pixel_scaled(bd, x, y);
		x++;
	}
}
