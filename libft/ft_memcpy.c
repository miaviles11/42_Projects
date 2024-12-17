/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:36:12 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/12 13:35:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	if (!dest && !src)
		return (NULL);
	count = 0;
	ptr = (unsigned char *)dest;
	ptr2 = (const unsigned char *)src;
	while (count < n)
	{
		ptr[count] = ptr2[count];
		count++;
	}
	return (dest);
}

/*int	main(void)
{
	char	src[20] = "hola";
	char	dest[20] = "que tal";

	ft_memcpy(dest, src, 4);
	printf("dest = %s\n", dest);
	return (0);
}*/
