/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:55 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/25 19:44:05 by miaviles         ###   ########.fr       */
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
	fractol->max_iter = 50;
	return (fractol);
}

static void	set_fractal_type(t_fractol *fractol, char *arg)
{
	if (ft_strncmp(arg, "mandelbrot", 9) == 0)
		fractol->fractal_type = 0;
	else if (ft_strncmp(arg, "julia", 5) == 0)
	{
		fractol->fractal_type = 1;
		fractol->c_re = -0.7;
		fractol->c_im = 0.27015;
	}
	else
		ft_error_clean("Invalid fractal type.\n", TRUE, fractol);
}

static void	init_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		ft_error_clean("MLX init failed\n", TRUE, fractol);
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fract'ol");
	if(!fractol->win)
		ft_error_clean("Window creation failed\n", TRUE, fractol);
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img)
		ft_error_clean("Image creation failed\n", TRUE, fractol);
	fractol->img_data = mlx_get_data_addr(fractol->img, &fractol->bpp,
		&fractol->size_line, &fractol->endian);
}

int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	if (argc != 2)
	{
		ft_printf("Usage: ./fractol [mandelbrot/julia]\n");
		return (1);
	}
	fractol = init_fractol();
	if (!fractol)
		return (1);
	set_fractal_type(fractol, argv[1]);
	init_mlx(fractol);
	render_mandelbrot(fractol);
	mlx_key_hook(fractol->win, key_hook, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
