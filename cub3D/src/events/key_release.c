/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:51 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:51 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_release(int keycode, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keycode == KEY_W)
		cub->keys.w = 0;
	else if (keycode == KEY_A)
		cub->keys.a = 0;
	else if (keycode == KEY_S)
		cub->keys.s = 0;
	else if (keycode == KEY_D)
		cub->keys.d = 0;
	else if (keycode == KEY_LEFT)
		cub->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		cub->keys.right = 0;
	return (0);
}
