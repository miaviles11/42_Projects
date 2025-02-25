/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:31:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/24 18:39:33 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(t_fractol *fractol)
{
	mlx_destroy_window(fractol->mlx, fractol->win);
	free(fractol);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(fractol->mlx, fractol->win);
		free(fractol);
		exit (0);
	}
	return (0);
}