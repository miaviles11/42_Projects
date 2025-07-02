/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:55 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/20 19:38:56 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_exit_command(t_msh *shell)
{
	char	**args;
	int		code;

	if (shell->cmd && shell->cmd->cmd
		&& !ft_strncmp(shell->cmd->cmd, "exit", 5))
	{
		args = shell->cmd->arg;
		code = 0;
		return (handle_exit_command(shell, args, code));
	}
	return (0);
}

int	handle_exit_command(t_msh *shell, char **args, int code)
{
	if (args && args[0])
	{
		if (!is_numeric(args[0]))
		{
			ft_printf("exit: %s: numeric argument required\n", args[0]);
			exit(255);
		}
		if (args[1])
		{
			ft_printf("exit: too many arguments\n");
			shell->error_value = 1;
			free_command_list(shell->cmd);
			return (1);
		}
		code = ft_atoi(args[0]);
	}
	exit(code);
}

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		exit_error("Error malloc", 1);
	return (ptr);
}
