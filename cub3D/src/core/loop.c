/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:31 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:31 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	init_screen(t_cub *cub)
{
	if (cub->screen.ptr)
		return (0);
	cub->screen.ptr = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->screen.ptr)
		return (-1);
	cub->screen.w = WIN_W;
	cub->screen.h = WIN_H;
	cub->screen.data = (int *)mlx_get_data_addr(cub->screen.ptr,
			&cub->screen.bpp,
			&cub->screen.line_len,
			&cub->screen.endian);
	return (0);
}

int	loop_hook(void *param)
{
	t_cub	*cub;
	double	dt;

	cub = (t_cub *)param;
	if (init_screen(cub))
		return (0);
	dt = timer_delta();
	movement_update(cub);
	draw_floor_ceil(cub);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->screen.ptr, 0, 0);
	timer_sleep(60, dt);
	return (0);
}
