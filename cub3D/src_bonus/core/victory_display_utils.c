/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   victory_display_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 23:05:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/09 11:43:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

static void	put_pixel(t_cub *cub, int xy[2], int color)
{
	int	*dst;

	if (xy[0] >= 0 && xy[0] < WIN_W && xy[1] >= 0 && xy[1] < WIN_H)
	{
		dst = cub->screen.data + xy[1] * WIN_W + xy[0];
		*dst = color;
	}
}

static void	draw_rect_util(t_cub *cub, int r[4])
{
	int	i;
	int	j;
	int	xy[2];

	j = -1;
	while (++j < r[3])
	{
		i = -1;
		while (++i < r[2])
		{
			xy[0] = r[0] + i;
			xy[1] = r[1] + j;
			put_pixel(cub, xy, 0xDD000000);
		}
	}
}

static void	draw_border_util(t_cub *cub, int r[4])
{
	int	i;
	int	xy[2];

	i = -1;
	while (++i < r[2])
	{
		xy[0] = r[0] + i;
		xy[1] = r[1];
		put_pixel(cub, xy, 0x00FF00);
		xy[1] = r[1] + r[3] - 1;
		put_pixel(cub, xy, 0x00FF00);
	}
	i = -1;
	while (++i < r[3])
	{
		xy[0] = r[0];
		xy[1] = r[1] + i;
		put_pixel(cub, xy, 0x00FF00);
		xy[0] = r[0] + r[2] - 1;
		put_pixel(cub, xy, 0x00FF00);
	}
}

void	draw_victory_box(t_cub *cub)
{
	int	r[4];

	r[0] = WIN_W / 2 - 250;
	r[1] = WIN_H / 2 - 100;
	r[2] = 500;
	r[3] = 200;
	draw_rect_util(cub, r);
	draw_border_util(cub, r);
}

void	draw_victory_text(t_cub *cub)
{
	int		pos[6];
	char	*msgs[3];

	pos[0] = WIN_W / 2;
	pos[1] = WIN_H / 2;
	msgs[0] = "V I C T O R Y";
	msgs[1] = "All enemies eliminated!";
	msgs[2] = "Press ESC to exit";
	pos[2] = pos[0] - (ft_strlen(msgs[0]) * 6) / 2;
	pos[3] = pos[0] - (ft_strlen(msgs[1]) * 6) / 2;
	pos[4] = pos[0] - (ft_strlen(msgs[2]) * 6) / 2;
	pos[5] = -1;
	while (++pos[5] < 9)
		mlx_string_put(cub->mlx, cub->win, pos[2] + (pos[5] % 3) - 1,
			pos[1] - 40 + (pos[5] / 3) - 1, 0x00FF00, msgs[0]);
	mlx_string_put(cub->mlx, cub->win, pos[3], pos[1] + 10, 0xFFFFFF, msgs[1]);
	mlx_string_put(cub->mlx, cub->win, pos[4], pos[1] + 50, 0xFFFF00, msgs[2]);
}
