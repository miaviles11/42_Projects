/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:07:17 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/03 16:12:14 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *str, t_bool e)
{
	int	len;

	len = ft_strlen(str);
	write(2, str, len);
	if (e)
		exit(EXIT_FAILURE);
}
