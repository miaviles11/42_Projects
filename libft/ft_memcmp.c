/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:17:15 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/01 16:22:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			count;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	count = 0;
	if (n == 0)
		return (0);
	while (count < n)
	{
		if (ptr1[count] != ptr2[count])
			return (ptr1[count] - ptr2[count]);
		count++;
	}
	return (0);
}

/*int	main(void)
{
	char	*s1 = "Hello";
	char	*s2 = "Trello";

	int	result = ft_memcmp(s1, s2, 6);
	printf("%d", result);
	return (0);
}*/