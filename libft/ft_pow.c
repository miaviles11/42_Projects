/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 15:22:16 by miaviles          #+#    #+#             */
/*   Updated: 2025/03/01 17:31:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double base, int exp)
{
	double	result;

	result = 1.0;
	if (exp < 0)
	{
		base = 1 / base;
		exp = -exp;
	}
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}
