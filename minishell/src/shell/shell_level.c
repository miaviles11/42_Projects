/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:23:46 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/20 17:48:23 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_shell_level(t_msh *shell)
{
	char	*shlvl_str;
	int		shlvl;

	shlvl_str = get_env_value(shell, "SHLVL");
	shlvl = 1;
	if (shlvl_str)
	{
		shlvl = atoi(shlvl_str);
		free(shlvl_str);
		shlvl++;
	}
	shell->bash_lvl = shlvl;
	update_shlvl_env(shell, shlvl);
}

void	update_shlvl_env(t_msh *shell, int shlvl)
{
	char	*new_shlvl;
	char	*new_shlvl_entry;

	new_shlvl = ft_itoa(shlvl);
	if (!new_shlvl)
		return ;
	new_shlvl_entry = ft_strjoin("SHLVL=", new_shlvl);
	free(new_shlvl);
	if (!new_shlvl_entry)
		return ;
	set_env_value(shell, "SHLVL", new_shlvl_entry + 6);
	free(new_shlvl_entry);
}
