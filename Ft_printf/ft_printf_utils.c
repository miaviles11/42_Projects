/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 20:25:02 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/30 19:52:43 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

char	*ft_utoa_base(unsigned long long n, int base, int uppercase)
{
	char				*str;
	char				*digits;
	int					len;
	unsigned long		num_temp;

	digits = "0123456789abcdef";
	if (uppercase)
		digits = "0123456789ABCDEF";
	num_temp = n;
	len = 0;
	while (num_temp)
	{
		num_temp = num_temp / base;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = (n % base) + '0';
		n /= base;
	}
	return (str);
}
