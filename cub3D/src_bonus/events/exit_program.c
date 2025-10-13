/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:04:12 by carlsanc          #+#    #+#             */
/*   Updated: 2025/10/09 17:04:12 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_bonus/cub3d.h"

int	exit_program(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	cub_cleanup(cub);
	exit(0);
	return (0);
}
