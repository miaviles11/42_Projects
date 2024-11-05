/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:46:44 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 15:31:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*d;
	size_t	count;
	size_t	len;

	count = 0;
	len = ft_strlen(s);
	d = (char *) malloc(len + 1);
	if (!d)
		return (NULL);
	while (s[count] != '\0')
	{
		d[count] = s[count];
		count++;
	}
	d[count] = '\0';
	return (d);
}

/*int	main(void)
{
	const char	*s = "hello";

	char *result = ft_strdup(s);
	printf("%s", result);
	free(result);
	return (0);
}*/
