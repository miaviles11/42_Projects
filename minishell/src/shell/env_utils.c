/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:33:36 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/20 17:45:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_msh *shell, const char *var_name)
{
	int	i;
	int	len;

	i = 0;
	if (!shell || !var_name || !shell->env)
		return (NULL);
	len = strlen(var_name);
	while (i < shell->num_env)
	{
		if (strncmp(shell->env[i], var_name, len) == 0
			&& shell->env[i][len] == '=')
			return (strdup(shell->env[i] + len + 1));
		i++;
	}
	return (NULL);
}
