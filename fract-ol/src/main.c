/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:08:55 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/05 16:35:35 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_julia_values(int ac, char **av, t_fractol *fractol)
{
	fractol->fractal_type = 1;
	if (ac == 4 && is_valid_param(av[2]) && is_valid_param(av[3]))
	{
		fractol->c_re = ft_atof(av[2]);
		fractol->c_im = ft_atof(av[3]);
	}
	else
	{
		ft_printf("\nInvalid parameters type, try:");
		ft_printf("\nUsage: ./fractol julia [c_re] [c_im]\n");
		ft_printf("\nExamples:\n");
		ft_printf("./fractol julia 0.285 0.01\n");
		ft_printf("./fractol julia 0.355 0.355\n");
		ft_printf("./fractol julia -0.4 0.6\n");
		ft_printf("./fractol julia -0.70176 -0.3842\n");
		ft_printf("./fractol julia -0.75 0.11\n");
		ft_printf("./fractol julia -0.1 0.651\n");
		ft_error_clean("", TRUE, fractol);
	}
}

static void	set_fractal_type(int ac, char **av, t_fractol *fractol)
{
	if (ft_strncmp(av[1], "mandelbrot", 11) == 0 && ac == 2)
		fractol->fractal_type = 0;
	else if (ft_strncmp(av[1], "julia", 6) == 0)
	{
		set_julia_values(ac, av, fractol);
		if (fractol->c_re < -2 || fractol->c_re > 2
			|| fractol->c_im < -2 || fractol->c_im > 2)
		{
			ft_printf("Error: Julia parameters must be between -2 and 2.");
			ft_error_clean("", TRUE, fractol);
		}
	}
	else
	{
		ft_printf("\nInvalid fractal type, try:\n\n");
		ft_printf("./fractol mandelbrot\n or\n./fractol julia [c_re] [c_im]\n");
		ft_printf("\nExamples:\n./fractol julia -0.8 0.156\n");
		ft_error_clean("", TRUE, fractol);
	}
}

static void	init_mlx(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		ft_error_clean("MLX init failed\n", TRUE, fractol);
	fractol->win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "Fract'ol");
	if (!fractol->win)
		ft_error_clean("Window creation failed\n", TRUE, fractol);
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	mlx_clear_window(fractol->mlx, fractol->win);
	if (!fractol->img)
		ft_error_clean("Image creation failed\n", TRUE, fractol);
	fractol->img_data = mlx_get_data_addr(fractol->img, &fractol->bpp,
			&fractol->size_line, &fractol->endian);
}

void	render_fractal(t_fractol *fractol)
{
	mlx_clear_window(fractol->mlx, fractol->win);
	if (fractol->fractal_type == 0)
		render_mandelbrot(fractol);
	else if (fractol->fractal_type == 1)
		render_julia(fractol);
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fractol	*fractol;

	if (argc < 2)
	{
		ft_printf("Usage: ./fractol [mandelbrot/julia]\n");
		return (1);
	}
	fractol = init_fractol();
	if (!fractol)
		return (1);
	set_fractal_type(argc, argv, fractol);
	init_mlx(fractol);
	render_fractal(fractol);
	mlx_key_hook(fractol->win, key_hook, fractol);
	mlx_hook(fractol->win, 4, 1L << 2, mouse_hook, fractol);
	mlx_hook(fractol->win, 17, 0, close_window, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
