/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:55:02 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/12 13:04:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	count;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s - start < len)
		len = len_s - start;
	if (len_s <= start)
		len = 0;
	count = 0;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (!subs)
		return (NULL);
	while (count < len)
	{
		subs[count] = s[start + count];
		count++;
	}
	subs[count] = '\0';
	return (subs);
}
/*int	main(void)
{
	char	*s = "GOOD TO BE REAL";

	char	*result = ft_substr(s, 16, 20);
	printf("%s", result);
	free(result);
	return (0);
}*/
