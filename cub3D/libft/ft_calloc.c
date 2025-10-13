/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 19:17:21 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/08 13:11:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;

	array = (void *) malloc(nmemb * size);
	if (!array)
		return (NULL);
	ft_bzero(array, size * nmemb);
	return (array);
}

/*int   main(void)
{
    size_t  n = 100000000000;
    size_t  size = sizeof(int);

    int *array = (int *)ft_calloc(n, size);
    if (!array)
    {
        printf("No se pudo asignar la memoria\n");
        return (1);
    }

    size_t  count = 0;
    while (count < n)
    {
        printf("array[%zu] = %d\n", count, array[count]);
        count++;
    }
    
    free(array);
    return (0);
}*/