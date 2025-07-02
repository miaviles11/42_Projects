/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:24:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/02 00:00:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command_node(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->arg)
	{
		i = 0;
		while (i < cmd->num_arg && cmd->arg[i])
		{
			free(cmd->arg[i]);
			i++;
		}
		free(cmd->arg);
	}
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	free(cmd);
}

void	free_command_list(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd)
	{
		temp = cmd->next;
		free_command_node(cmd);
		cmd = temp;
	}
}

void	cleanup_shell(t_msh *shell)
{
	int	i;

	if (!shell)
		return ;
	free_command_list(shell->cmd);
	if (shell->env)
	{
		i = 0;
		while (i < shell->num_env && shell->env[i])
		{
			free(shell->env[i]);
			i++;
		}
		free(shell->env);
	}
	if (shell->path)
		free(shell->path);
	free(shell);
	rl_clear_history();
}
