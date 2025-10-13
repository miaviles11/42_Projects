/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:06 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:04:06 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

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
	else if (keycode == KEY_SPACE)
		cub->keys.space = 1;
	else if (keycode == KEY_E)
		handle_door_interaction(cub);
	return (0);
}
