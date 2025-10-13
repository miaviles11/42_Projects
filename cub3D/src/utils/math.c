/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:18 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:18 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	ft_abs_d(double v)
{
	if (v < 0.0)
		return (-v);
	return (v);
}

double	ft_max_d(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_min_d(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
