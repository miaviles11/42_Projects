/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:30:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 11:43:08 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	draw_pixel_safe(t_cub *cub, int xy[2], int color)
{
	int	*dst;

	if (xy[0] >= 0 && xy[0] < WIN_W && xy[1] >= 0 && xy[1] < WIN_H)
	{
		dst = cub->screen.data + xy[1] * WIN_W + xy[0];
		*dst = color;
	}
}

void	draw_rect(t_cub *cub, int rect[4])
{
	int	i;
	int	j;
	int	xy[2];

	j = 0;
	while (j < rect[3])
	{
		i = 0;
		while (i < rect[2])
		{
			xy[0] = rect[0] + i;
			xy[1] = rect[1] + j;
			draw_pixel_safe(cub, xy, 0xDD000000);
			i++;
		}
		j++;
	}
}

void	draw_enemy_counter_box(t_cub *cub)
{
	int	rect[4];

	rect[0] = WIN_W - 150;
	rect[1] = 15;
	rect[2] = 140;
	rect[3] = 40;
	draw_rect(cub, rect);
}

void	draw_enemy_counter_text(t_cub *cub)
{
	char	*count_str;
	char	*full_text;
	int		vars[4];

	vars[0] = WIN_W - 150;
	vars[1] = 15;
	count_str = ft_itoa(cub->enemies_alive);
	if (!count_str)
		return ;
	full_text = ft_strjoin("Enemies: ", count_str);
	free(count_str);
	if (!full_text)
		return ;
	vars[2] = ft_strlen(full_text);
	vars[3] = vars[0] + (140 - vars[2] * 6) / 2;
	mlx_string_put(cub->mlx, cub->win, vars[3], vars[1] + 27,
		0xFFFFFF, full_text);
	free(full_text);
}
