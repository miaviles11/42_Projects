/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:39:15 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 15:17:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	len_d;
	size_t	len_s;

	len_d = 0;
	len_s = 0;
	while (src[len_s] != '\0')
		len_s++;
	while (len_d < size && dst[len_d] != '\0')
		len_d++;
	if (len_d == size)
		return (size + len_s);
	count = 0;
	while (src[count] != '\0' && (len_d + count) < (size - 1))
	{
		dst[len_d + count] = src[count];
		count++;
	}
	dst[len_d + count] = '\0';
	return (len_d + len_s);
}

/*int	main(void)
{
	char	buffer1[20] = "Hola";
	char	buffer2[10] = "Adios";
	char	buffer3[5] = "Hi";
	size_t result;

	result = ft_strlcat(buffer1, "mundo", 10);
	printf("%zu, %s\n", result, buffer1);
	result = ft_strlcat(buffer2, "mundo", 30);
	printf("%zu, %s\n", result, buffer2);
	result = ft_strlcat(buffer3, "mundo", 30);
	printf("%zu, %s\n", result, buffer3);
	return (0);
}*/