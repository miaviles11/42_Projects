/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:02:41 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/10 13:11:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static int	init_zbuffer(t_cub *cub)
{
	int	i;

	cub->z_buffer = (double *)malloc(sizeof(double) * WIN_W);
	if (!cub->z_buffer)
		return (-1);
	i = 0;
	while (i < WIN_W)
	{
		cub->z_buffer[i] = 0.0;
		++i;
	}
	return (0);
}

void	setup_mouse_deferred(t_cub *cub)
{
	if (!cub || !cub->mlx || !cub->win)
		return ;
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_move(cub->mlx, cub->win, WIN_W / 2, WIN_H / 2);
	cub->mouse_x = WIN_W / 2;
	cub->first_mouse = 1;
}

int	init_mlx(t_cub *cub)
{
	if (!cub)
		return (-1);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (-1);
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		return (-1);
	if (init_zbuffer(cub) == -1)
		return (-1);
	cub->screen.ptr = NULL;
	cub->screen.data = NULL;
	cub->screen.w = 0;
	cub->screen.h = 0;
	cub->screen.bpp = 0;
	cub->screen.line_len = 0;
	cub->screen.endian = 0;
	setup_mouse_deferred(cub);
	return (0);
}
