/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:03:40 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/05 16:02:22 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(int iter)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	if (iter == MAX_ITER)
		return (0x000000);
	t = (double)iter / (double)MAX_ITER;
	red = (int)(sin(5 * t) * 127 + 128);
	green = (int)(cos(7 * t) * 127 + 128);
	blue = (int)(sin(11 * t + 3.14) * 127 + 128);
	return ((red << 16) | (green << 8) | blue);
}

static void	put_pixel(t_fractol *fractol, int x, int y, int color)
{
	int	index;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	index = (x * fractol->bpp / 8) + (y * fractol->size_line);
	*(int *)(fractol->img_data + index) = color;
}

static int	calc_julia(double pr, double pi, double c_re, double c_im)
{
	int		iter;
	double	old_re;
	double	old_im;
	double	new_re;
	double	new_im;

	iter = 0;
	old_re = pr;
	old_im = pi;
	while ((old_re * old_re + old_im * old_im) <= 4 && iter < MAX_ITER)
	{
		new_re = old_re * old_re - old_im * old_im + c_re;
		new_im = 2 * old_re * old_im + c_im;
		old_re = new_re;
		old_im = new_im;
		iter++;
	}
	return (iter);
}

int	is_valid_param(const char *str)
{
	int	i;
	int	has_dot;

	i = 0;
	has_dot = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (has_dot)
				return (0);
			has_dot = 1;
		}
		else if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	render_julia(t_fractol *fractol)
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
			pi = (y - HEIGHT / 2) / (0.5 * fractol->zoom * HEIGHT)
				+ fractol->offset_y;
			iter = calc_julia(pr, pi, fractol->c_re, fractol->c_im);
			put_pixel(fractol, x, y, get_color(iter));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
