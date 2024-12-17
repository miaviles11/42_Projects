/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:09:09 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/12 13:47:13 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		return (0);
	while (count < n - 1 && s1[count] == s2[count] && s1[count] && s2[count])
		count++;
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

/*int	main(void)
{
	char	*s1 = "Hola";
	char	*s2 = "Halaa";

	int	result = ft_strncmp(s1, s2, 2);
	printf("%d", result);
	return (0);
}*/
