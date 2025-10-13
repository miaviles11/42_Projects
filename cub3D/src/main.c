/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:31 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:31 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	error_exit(const char *msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	while (*msg)
	{
		write(STDERR_FILENO, msg, 1);
		msg++;
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
		i++;
	if (i < 5)
		return (0);
	if (file[i - 4] != '.' || file[i - 3] != 'c')
		return (0);
	if (file[i - 2] != 'u' || file[i - 1] != 'b')
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>");
	if (!has_cub_extension(argv[1]))
		error_exit("Invalid file extension: expected .cub");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit("Map file not found or not readable");
	if (close(fd) < 0)
		error_exit("Failed to close map file");
	if (cub3d_run(argv[1]) != 0)
		error_exit("cub3D terminated unexpectedly");
	return (EXIT_SUCCESS);
}
