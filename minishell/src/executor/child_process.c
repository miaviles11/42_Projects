/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:44:22 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 16:50:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_executable(char *cmd)
{
	char	*path;

	path = check_command_path(cmd);
	if (path)
		return (path);
	return (search_in_path(cmd));
}

char	**prepare_argv(t_cmd *cmd)
{
	char	**argv;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (cmd->arg)
	{
		while (cmd->arg[i])
			i++;
	}
	argv = (char **)malloc(sizeof(char *) * (i + 2));
	if (!argv)
		return (NULL);
	argv[0] = cmd->cmd;
	while (++j < i)
		argv[j + 1] = cmd->arg[j];
	argv[i + 1] = NULL;
	return (argv);
}

static void	setup_redirections(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (output_fd != STDOUT_FILENO)
	{
		dup2(output_fd, STDOUT_FILENO);
		close(output_fd);
	}
}

void	setup_child_process(t_msh *msh, t_cmd *cmd, int input_fd, int output_fd)
{
	(void)msh;
	setup_child_signals();
	if (!cmd->cmd || cmd->cmd[0] == '\0')
	{
		if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
			process_redirections(cmd);
		_exit(0);
	}
	setup_redirections(input_fd, output_fd);
	if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
		process_redirections(cmd);
}

void	child_process(t_msh *msh, t_cmd *cmd, int input_fd, int output_fd)
{
	char	*executable;
	char	**argv;

	setup_child_process(msh, cmd, input_fd, output_fd);
	executable = find_executable(cmd->cmd);
	if (!executable)
	{
		ft_printf("Command not found: %s\n", cmd->cmd);
		_exit(127);
	}
	argv = prepare_argv(cmd);
	if (!argv)
	{
		free(executable);
		_exit(1);
	}
	execve(executable, argv, cmd->env);
	perror("execve");
	free(executable);
	free(argv);
	_exit(1);
}
