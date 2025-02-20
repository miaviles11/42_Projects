/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:59:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/20 19:02:10 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main(void)
{
	char	*line;
	int		fd;

	ft_printf("Testing ft_printf:\n");
	ft_printf("Hello %s!\n", "world");
	ft_printf("\nTesting get_next_line:\n");
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		ft_printf("%s\n", line);
		free(line);
	}
	close(fd);
	ft_printf("\nTesting ft_putchar_fd:\n");
	ft_putchar_fd('A', 1);
	return (0);
}
