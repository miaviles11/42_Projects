/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:15:40 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/12 12:45:17 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)&s[len]);
	while (len > 0)
	{
		len--;
		if (s[len] == (char)c)
			return ((char *)&s[len]);
	}
	if (s[len] == (char)c)
		return ((char *)&s[len]);
	return (NULL);
}

/*int	main(void)
{
	char	*s = "Hello friend";

	char	*result = ft_strrchr(s, 'e');
	printf("%s", result);
	return (0);	
}*/
