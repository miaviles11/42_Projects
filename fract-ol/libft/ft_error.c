/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:07:17 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/24 16:33:02 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *str, t_bool e)
{
	int	len;

	len = ft_strlen(str);
	ft_printf("%s\n", str);
	if (e)
		exit(EXIT_FAILURE);
}
