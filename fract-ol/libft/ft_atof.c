/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 17:33:25 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/01 17:36:54 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	parse_decimal(const char *str, int *i)
{
	double	decimal;
	int		j;

	decimal = 0.0;
	j = 0;
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			decimal = decimal * 10.0 + (str[*i] - '0');
			(*i)++;
			j++;
		}
	}
	return (decimal / ft_pow(10.0, j));
}

double	ft_atof(const char *str)
{
	double	f;
	int		sign;
	int		i;

	i = 0;
	f = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		f = f * 10.0 + (str[i] - '0');
		i++;
	}
	f += parse_decimal(str, &i);
	return (f * sign);
}
