/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:48 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:48 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == KEY_ESC)
		exit_program(cub);
	else if (keycode == KEY_W)
		cub->keys.w = 1;
	else if (keycode == KEY_A)
		cub->keys.a = 1;
	else if (keycode == KEY_S)
		cub->keys.s = 1;
	else if (keycode == KEY_D)
		cub->keys.d = 1;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 1;
	return (0);
}
