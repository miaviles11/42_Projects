/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:31:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/05 15:59:03 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractol	*init_fractol(void)
{
	t_fractol	*fractol;

	fractol = malloc(sizeof(t_fractol));
	if (!fractol)
		return (NULL);
	fractol->zoom = 1.0;
	fractol->offset_x = 0.0;
	fractol->offset_y = 0.0;
	return (fractol);
}

int	close_window(t_fractol *fractol)
{
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_image(fractol->mlx, fractol->img);
	mlx_destroy_display(fractol->mlx);
	free(fractol->mlx);
	free(fractol);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_fractol *fractol)
{
	if (keycode == 65307)
		close_window(fractol);
	else if (keycode == 65361)
		fractol->offset_x -= 0.1 / fractol->zoom;
	else if (keycode == 65363)
		fractol->offset_x += 0.1 / fractol->zoom;
	else if (keycode == 65362)
		fractol->offset_y -= 0.1 / fractol->zoom;
	else if (keycode == 65364)
		fractol->offset_y += 0.1 / fractol->zoom;
	render_fractal(fractol);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	double	mouse_re;
	double	mouse_im;

	mouse_re = 1.5 * (x - WIDTH / 2) / (0.5 * fractol->zoom * WIDTH)
		+ fractol->offset_x;
	mouse_im = (y - HEIGHT / 2) / (0.5 * fractol->zoom * HEIGHT)
		+ fractol->offset_y;
	if (button == 4)
		fractol->zoom *= 1.2;
	else if (button == 5)
		fractol->zoom /= 1.2;
	fractol->offset_x = mouse_re - (1.5 * (x - WIDTH / 2)
			/ (0.5 * fractol->zoom * WIDTH));
	fractol->offset_y = mouse_im - ((y - HEIGHT / 2)
			/ (0.5 * fractol->zoom * HEIGHT));
	render_fractal(fractol);
	return (0);
}
