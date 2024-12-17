/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:23:58 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/08 13:11:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*array;
	unsigned int	count;

	if (!s || !f)
		return (NULL);
	array = (char *)malloc(ft_strlen(s) + 1);
	if (!array)
		return (NULL);
	count = 0;
	while (s[count])
	{
		array[count] = f(count, s[count]);
		count++;
	}
	array[count] = '\0';
	return (array);
}

/*char	to_uppercase(unsigned int i, char c)
{
    (void)i;

    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}*/

/*int	main(void)
{
    char *str = "Goob to be real";
    char *result;

    result = ft_strmapi(str, to_uppercase);

    if (result)
    {
        printf("Original: %s\n", str);
        printf("Modificated: %s\n", result);
        free(result);
    }
    else
        printf("Error\n");
    return (0);
}*/