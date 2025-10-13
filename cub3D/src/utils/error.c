/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:41:13 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:41:13 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	cub_error(t_cub *cub, const char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		while (*msg)
		{
			write(2, msg, 1);
			msg++;
		}
		write(2, "\n", 1);
	}
	cub_cleanup(cub);
	return (-1);
}
