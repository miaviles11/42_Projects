/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:51 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	minishell_env(t_msh *msh)
{
	int		i;
	char	*equal_sign;

	i = 0;
	while (msh->env[i] != NULL)
	{
		equal_sign = ft_strchr(msh->env[i], '=');
		if (equal_sign != NULL && *(equal_sign + 1) != '\0')
			ft_printf("%s\n", msh->env[i]);
		i++;
	}
	return (0);
}
