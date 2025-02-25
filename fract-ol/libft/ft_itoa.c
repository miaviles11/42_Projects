/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:45:24 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/08 14:55:22 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int n)
{
	int		len;

	len = 0;
	if (n == -2147483648)
		return (10);
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nb;

	nb = (long)n;
	len = intlen(n);
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(char) * (len +1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb >= 10)
	{
		len--;
		str[len] = (nb % 10) + '0';
		nb /= 10;
	}
	str[--len] = nb + '0';
	return (str);
}

/*int	main(void)
{
	char	*result;
	int		n;

	n = 11423434;
	result = ft_itoa(n);
	printf("%s", result);
	free(result);
	return (0);
}*/
