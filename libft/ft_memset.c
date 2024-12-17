/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:00:12 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 17:34:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t		count;

	count = 0;
	while (count < n)
	{
		((unsigned char *)s)[count] = (unsigned char)c;
		count++;
	}
	return (s);
}
/*int main(void)
{
    char str[] = "42 Madrid";
    char c = 'a';
    size_t len = 1;

    printf("Original text: %s\n", str);
    ft_memset(str, c, len); 
    printf("Final text: %s\n", str);
    return 0;
}*/
