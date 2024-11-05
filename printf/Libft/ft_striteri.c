/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:34:58 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/08 13:11:23 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	index;

	if (!s || !f)
		return ;
	index = 0;
	while (s[index] != '\0')
	{
		f(index, &s[index]);
		index++;
	}
}

/*static void   ft_add_count(unsigned int n, char *c)
{
	n = 2;
    *c = *c + n;
}*/

/*int	main(void)
{
	char str[] = "Hola que tal?";

	ft_striteri(str, ft_add_count);
        
	printf("La cadena después de la función: %s\n", str);

	return (0);
}*/