/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:05:58 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/01 16:22:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			count;
	unsigned char	*ptr;

	c = (unsigned char)c;
	ptr = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		if (ptr[count] == c)
			return ((void *)(ptr + count));
		count++;
	}
	return (NULL);
}

/*int main() 
{
    const char str[] = "Hola que tal!";
    char *ptr = ft_memchr(str, 'a', sizeof(str));
    if (ptr != NULL) {
        printf("Encontrado en la posición: %ld\n", ptr - str);
    } else {
        printf("No encontrado.\n");
    }
    return 0;
}*/