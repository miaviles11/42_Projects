/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:10:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/25 19:42:41 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(int iter, int max_iter)
{
	if (iter == max_iter)
		return (0x000000);
	return (0x00FF00 * iter / max_iter);
}

static void	put_pixel(t_fractol *fractol, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	index = (x * fractol->bpp / 8) + (y * fractol->size_line);
	*(int *)(fractol->img_data + index) = color;
}

static int	calc_mandelbrot(double pr, double pi, int max_iter)
{
	int	iter;
	double	old_re;
	double	old_im;
	double	new_re;
	double	new_im;

	iter = 0;
	old_re = 0;
	old_im = 0;
	while ((old_re * old_re + old_im * old_im) <= 4 && iter < max_iter)
	{
		new_re = old_re * old_re - old_im * old_im + pr;
		new_im = 2 * old_re * old_im + pi;
		old_re = new_re;
		old_im = new_im;
		iter++;
	}
	return (iter);
}

void	render_mandelbrot(t_fractol *fractol)
{
	int		x;
	int		y;
	int		iter;
	double	pr;
	double	pi;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pr = 1.5 * (x - WIDTH / 2) / (0.5 * fractol->zoom * WIDTH)
				+ fractol->offset_x;
			pi = 1.5 * (y - HEIGHT / 2) / (0.5 * fractol->zoom * HEIGHT)
				+ fractol->offset_y;
			iter = calc_mandelbrot(pr, pi, fractol->max_iter);
			put_pixel(fractol, x, y, get_color(iter, fractol->max_iter));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}