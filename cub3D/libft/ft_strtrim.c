/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:02:35 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/03 17:23:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*array;
	size_t	start;
	size_t	end;
	size_t	count;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	array = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!array)
		return (NULL);
	count = 0;
	while (start < end)
		array[count++] = s1[start++];
	array[count] = '\0';
	return (array);
}

/*int	main(void)
{
	char	*s1 = "----42--c--";

	char	*result = ft_strtrim(s1, "-");
	printf("%s", result);
	return (0);
}*/