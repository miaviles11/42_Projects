/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:37:02 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/30 19:43:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	print_string(char *str)
{
	int	len;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	print_number(int n, int unsign)
{
	int		len;
	char	*str;

	if (unsign)
		str = ft_utoa_base((unsigned long long)n, 10, 0);
	else
		str = ft_itoa(n);
	if (!str)
		return (0);
	len = print_string(str);
	free(str);
	return (len);
}

int	print_pointer(void *ptr)
{
	int		len;
	char	*hex_str;

	if (!ptr)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, "0x", 2);
	hex_str = ft_utoa_base((unsigned long long)ptr, 16, 0);
	if (!hex_str)
		return (0);
	len = print_string(hex_str);
	free(hex_str);
	return (len + 2);
}

int	print_hex(unsigned int n, int uppercase)
{
	int		len;
	char	*hex_str;

	hex_str = ft_utoa_base((unsigned long long)n, 16, uppercase);
	if (!hex_str)
		return (0);
	len = print_string (hex_str);
	free(hex_str);
	return (len);
}
