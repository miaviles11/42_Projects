/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:49:41 by miaviles          #+#    #+#             */
/*   Updated: 2024/10/11 15:18:08 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

/*int	main(void)
{
	int fd = open("dardo", O_RDWR | O_CREAT, 0600);
	ft_putstr_fd("good", fd);
	return (0);
}*/