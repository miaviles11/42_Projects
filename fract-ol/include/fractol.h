/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:11:14 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/01 17:24:44 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
#include <math.h>

# define WIDTH 1920
# define HEIGHT 1420

typedef struct	s_fractol
{
	void	*mlx;         // Conexión a la MiniLibX
	void	*win;         // Ventana creada
	void	*img;         // Imagen donde se dibuja el fractal
	char	*img_data;    // Dirección de los datos de la imagen
	int		bpp;          // Bits por píxel de la imagen
	int		size_line;    // Tamaño de cada línea en bytes
	int		endian;       // Endianness de la imagen

	double	zoom;         // Factor de zoom para explorar el fractal
	double	offset_x;     // Desplazamiento horizontal (pan)
	double	offset_y;     // Desplazamiento vertical (pan)
	int		max_iter;     // Número máximo de iteraciones para el cálculo

	int		fractal_type; // Identificador del tipo de fractal (ej. Mandelbrot, Julia, etc.)
	double	c_re;         // Parte real de la constante (para Julia)
	double	c_im;         // Parte imaginaria de la constante (para Julia)
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