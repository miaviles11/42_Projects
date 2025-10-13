/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  :+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:40:38 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/07 21:30:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

void	weapon_on_click(t_cub *c);
void	shoot_try(t_cub *c);

int	configure_notify(void *param)
{
	(void)param;
	return (0);
}

int	set_hooks(t_cub *cub)
{
	if (!cub || !cub->win)
		return (-1);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 6, 1L << 6, mouse_move, cub);
	mlx_hook(cub->win, 4, 1L << 2, mouse_press, cub);
	mlx_hook(cub->win, 17, 0, exit_program, cub);
	mlx_hook(cub->win, 33, 1L << 19, configure_notify, cub);
	mlx_loop_hook(cub->mlx, loop_hook, cub);
	return (0);
}

static void	recenter_mouse(t_cub *cub)
{
	int	center_x;
	int	center_y;

	center_x = WIN_W / 2;
	center_y = WIN_H / 2;
	mlx_mouse_move(cub->mlx, cub->win, center_x, center_y);
	cub->mouse_x = center_x;
}

int	mouse_move(int x, int y, void *param)
{
	t_cub	*cub;
	int		dx;
	int		center_x;

	(void)y;
	cub = (t_cub *)param;
	center_x = WIN_W / 2;
	if (cub->first_mouse)
	{
		cub->mouse_x = center_x;
		cub->first_mouse = 0;
		return (0);
	}
	dx = x - center_x;
	if (dx != 0)
	{
		rotate_player(&cub->player, dx * MOUSE_SENSITIVITY);
		recenter_mouse(cub);
	}
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_cub	*cub;

	(void)x;
	(void)y;
	cub = (t_cub *)param;
	if (button == 1)
	{
		weapon_on_click(cub);
		shoot_try(cub);
	}
	return (0);
}
