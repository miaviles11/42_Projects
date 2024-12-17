/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:35:58 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/13 12:53:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bubblesort(int *array, int count)
{
	int	i;
	int	v;
	int	temp;

	if (!array || count <= 1)
		return ;
	v = 1;
	while (v)
	{
		v = 0;
		i = 0;
		while (i < count - 1)
		{
			if (array[i] > array[i + 1])
			{
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				v = 1;
			}
			i++;
		}
		count--;
	}
}
