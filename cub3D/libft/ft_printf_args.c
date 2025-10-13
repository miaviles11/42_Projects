/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:37:02 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 18:20:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

size_t	print_pointer(size_t ptr)
{
	int		len;

	len = 0;
	if (!ptr)
		return (print_string("(nil)"));
	write(1, "0x", 2);
	len += print_hex(ptr, 0);
	return (len + 2);
}

size_t	print_hex(size_t n, int uppercase)
{
	int		len;

	len = 0;
	if (n == 0)
		return (len += print_char('0'));
	if (n >= 16)
		len += print_hex(n / 16, uppercase);
	if (n % 16 <= 9)
		len += print_char((n % 16 + '0'));
	else if (uppercase == 0)
		len += print_char((n % 16 - 10 + 'a'));
	else if (uppercase)
		len += print_char((n % 16 - 10 + 'A'));
	return (len);
}
