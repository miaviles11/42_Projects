/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:18:28 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 17:37:34 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	j = (char *) malloc(len + 1);
	if (!j)
		return (NULL);
	ft_strlcpy(j, s1, len + 1);
	ft_strlcat(j, s2, len + 1);
	return (j);
}

/*int	main(void)
{
	char	*s1 = "GOOD";
	char	*s2 = "TO BE REAL";
	char	*result = ft_strjoin(s1, s2);

	printf("%s", result);
	return (0);
}*/