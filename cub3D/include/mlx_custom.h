/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_custom.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:30:10 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/01 15:30:10 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CUSTOM_H
# define MLX_CUSTOM_H

# include "structs.h"

t_img	img_create(void *mlx, int w, int h);
void	img_destroy(void *mlx, t_img *img);
void	img_pixel_put(t_img *img, int x, int y, int color);

#endif
