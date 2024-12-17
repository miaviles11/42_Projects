/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:51:36 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 15:17:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	len;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (size == 0)
		return (len);
	count = 0;
	while (count < size - 1 && src[count] != '\0')
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (len);
}

/*int	main(void)
{
	const char	src[] = "Hola mundo";
	char		dest[8];

	ft_strlcpy(dest, src, sizeof(dest));
	printf("Str: %s\n", dest);
	return (0);
}*/
