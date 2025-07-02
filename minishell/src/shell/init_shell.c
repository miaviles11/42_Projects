/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:40:42 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/20 17:57:45 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_shell_struct(t_msh *shell)
{
	shell->bash_lvl = 0;
	shell->total_chars = 0;
	shell->cmd = NULL;
	shell->path = NULL;
	shell->error_value = 0;
	shell->quote = 0;
	shell->pipe = 0;
	shell->redic = 0;
	shell->num_env = 0;
	return (1);
}

int	init_shell_env(t_msh *shell, char **envp)
{
	if (envp)
		while (envp[shell->num_env])
			shell->num_env++;
	shell->env = (char **)malloc(sizeof(char *) * (shell->num_env + 1));
	if (!shell->env)
		return (0);
	return (copy_env_values(shell, envp));
}

int	copy_env_values(t_msh *shell, char **envp)
{
	int	i;

	i = 0;
	while (i < shell->num_env)
	{
		shell->env[i] = strdup(envp[i]);
		if (!shell->env[i])
		{
			free_env_values(shell, i - 1);
			return (0);
		}
		i++;
	}
	shell->env[shell->num_env] = NULL;
	return (1);
}

void	free_env_values(t_msh *shell, int index)
{
	while (index >= 0)
		free(shell->env[index--]);
	free(shell->env);
}

t_msh	*initialize_shell(char **envp)
{
	t_msh	*shell;

	shell = (t_msh *)malloc(sizeof(t_msh));
	if (!shell)
		return (NULL);
	if (!init_shell_struct(shell))
		return (NULL);
	if (!init_shell_env(shell, envp))
		return (free(shell), NULL);
	shell->path = get_env_value(shell, "PATH");
	update_shell_level(shell);
	return (shell);
}
