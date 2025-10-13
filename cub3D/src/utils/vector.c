/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:28 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:28 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y});
}

t_vec	vec_mul(t_vec v, double s)
{
	return ((t_vec){v.x * s, v.y * s});
}

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

t_vec	vec_norm(t_vec v)
{
	double	len;

	len = vec_len(v);
	if (len == 0.0)
		return (v);
	v.x /= len;
	v.y /= len;
	return (v);
}
