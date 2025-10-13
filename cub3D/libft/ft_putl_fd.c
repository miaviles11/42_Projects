/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putl_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:53:52 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 18:27:02 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_putl_fd(long n, int fd)
{
	size_t	i;

	i = 0;
	if (n == (-__LONG_MAX__) - 1)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('9', fd);
		n = 223372036854775808;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		i++;
		n = -n;
	}
	if (n >= 10)
		i += ft_putl_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
	return (i + 1);
}

/*int	main(void)
{
	ft_putnbr_fd(-83648, 1);
	return (0);
}*/
