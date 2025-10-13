/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 11:30:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/08 21:58:45 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_bonus/cub3d.h"

static void	calculate_sprite_transform(t_cub *cub, t_sprite *sprite,
		double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sprite->pos.x - cub->player.pos.x;
	sprite_y = sprite->pos.y - cub->player.pos.y;
	inv_det = 1.0 / (cub->player.plane.x * cub->player.dir.y
			- cub->player.dir.x * cub->player.plane.y);
	*transform_x = inv_det * (cub->player.dir.y * sprite_x
			- cub->player.dir.x * sprite_y);
	*transform_y = inv_det * (-cub->player.plane.y * sprite_x
			+ cub->player.plane.x * sprite_y);
}

static void	swap_sprites(t_sprite_order *a, t_sprite_order *b)
{
	t_sprite_order	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	sort_sprites_by_distance(t_sprite_order *order, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (order[j].distance < order[j + 1].distance)
				swap_sprites(&order[j], &order[j + 1]);
			j++;
		}
		i++;
	}
}

static int	prepare_sprite_order(t_cub *cub, t_sprite_order *order)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < cub->sprites.count)
	{
		if (cub->sprites.sprites[i].loaded)
		{
			calculate_sprite_transform(cub, &cub->sprites.sprites[i],
				&order[count].transform_x, &order[count].transform_y);
			order[count].sprite = &cub->sprites.sprites[i];
			order[count].distance = order[count].transform_y;
			count++;
		}
	}
	return (count);
}

void	draw_sprites(t_cub *cub, int frame)
{
	t_sprite_order	order[100];
	int				i;
	int				count;

	(void)frame;
	count = prepare_sprite_order(cub, order);
	sort_sprites_by_distance(order, count);
	i = -1;
	while (++i < count)
	{
		if (order[i].transform_y > 0)
			render_sprite_column(cub, order[i].sprite,
				order[i].transform_x, order[i].transform_y);
	}
}
