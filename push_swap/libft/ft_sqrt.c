/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:53:00 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/13 12:52:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nmb)
{
	int	i;

	if (nmb < 0)
		return (-1);
	if (nmb < 4)
		return (1);
	i = 2;
	while (i * i < nmb)
		i++;
	if (i * i - nmb < nmb - (i - 1) * (i - 1))
		return (i);
	return (i - 1);
}
