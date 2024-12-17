/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:22:17 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/12 13:34:19 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			count;

	if (!dest && !src)
		return (NULL);
	if ((unsigned char *)dest > (unsigned char *)src)
	{
		count = n;
		while (count > 0)
		{
			count--;
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
		}
	}
	else
	{
		count = 0;
		while (count < n)
		{
			((unsigned char *)dest)[count] = ((unsigned char *)src)[count];
			count ++;
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	src[20] = "Hola";
	char	dest[20] = "que tal";

	ft_memmove(dest, src, 10);
	printf("dest = %s\n", dest);
	return (0);
}*/
