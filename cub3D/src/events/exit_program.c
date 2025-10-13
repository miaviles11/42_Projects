/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:39:41 by carlsanc          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:41 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_program(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub_cleanup(cub);
	exit(0);
	return (0);
}
