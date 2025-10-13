/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_custom.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 17:33:45 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/17 17:33:48 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CUSTOM_H
# define MLX_CUSTOM_H

# include "structs.h"

t_img	img_create(void *mlx, int w, int h);
void	img_destroy(void *mlx, t_img *img);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
