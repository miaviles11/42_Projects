/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:55:53 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/01 16:22:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	if (*little == '\0')
		return ((char *)big);
	b = 0;
	while (b < len && big[b] != '\0')
	{
		l = 0;
		while (little[l] != '\0' && (b + l) < len && big[b + l] == little[l])
			l++;
		if (little[l] == '\0')
			return ((char *)&big[b]);
		b++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char	*big = "Hello world";
	const char	*little = "world";

	char	*result = ft_strnstr(big, little, 12);
	printf("%s", result);
	return (0);
}*/