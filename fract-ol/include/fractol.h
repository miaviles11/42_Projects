/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:14 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/05 16:04:10 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1420
# define MAX_ITER 100

typedef struct s_fractol
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;

	double	zoom;
	double	offset_x;
	double	offset_y;

	int		fractal_type;
	double	c_re;
	double	c_im;
}	t_fractol;

int			main(int argc, char **argv);
void		render_fractal(t_fractol *fractol);

t_fractol	*init_fractol(void);
int			close_window(t_fractol *fractol);
int			key_hook(int keycode, t_fractol *fractol);
int			mouse_hook(int button, int x, int y, t_fractol *fractol);

void		render_mandelbrot(t_fractol *fractol);

void		render_julia(t_fractol *fractol);
int			is_valid_param(const char *str);

#endif