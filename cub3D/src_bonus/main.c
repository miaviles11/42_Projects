/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:58:11 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 16:58:11 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d.h"

static void	error_exit(const char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	while (*msg)
	{
		write(STDERR_FILENO, msg, 1);
		++msg;
	}
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

static int	has_cub_extension(const char *file)
{
	int	i;

	if (!file)
		return (0);
	i = 0;
	while (file[i])
		++i;
	if (i < 5)
		return (0);
	return (file[i - 4] == '.' && file[i - 3] == 'c' && file[i - 2] == 'u'
		&& file[i - 1] == 'b');
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>");
	if (!has_cub_extension(argv[1]))
		error_exit("Map file must have .cub extension");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Map file not found");
	close(fd);
	if (cub3d_run(argv[1]) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
