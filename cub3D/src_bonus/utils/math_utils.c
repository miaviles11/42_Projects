/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:57:29 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:57:29 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

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
