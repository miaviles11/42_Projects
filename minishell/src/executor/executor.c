/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:39:24 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 17:39:24 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(t_msh *msh, t_cmd *cmd, char *executable)
{
	char	**argv;

	setup_child_signals();
	if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
		process_redirections(cmd);
	perform_expansion(msh, &cmd);
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

void	handle_command_execution(t_msh *msh, t_cmd *cmd, char *executable)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(executable);
		msh->error_value = 1;
		return ;
	}
	if (pid == 0)
	{
		exec_child(msh, cmd, executable);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->error_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		msh->error_value = 128 + WTERMSIG(status);
	free(executable);
}

void	execute_single_command(t_msh *msh, t_cmd *cmd)
{
	char	*exe;

	if (!cmd->cmd || cmd->cmd[0] == '\0')
	{
		redir_only_child(msh, cmd);
		msh->error_value = 0;
		return ;
	}
	perform_expansion(msh, &cmd);
	exe = find_executable(cmd->cmd);
	if (!exe)
	{
		ft_printf("Command not found: %s\n", cmd->cmd);
		msh->error_value = 127;
		return ;
	}
	handle_command_execution(msh, cmd, exe);
}

void	execute_pipeline(t_msh *msh)
{
	t_cmd	*current;
	int		pipe_fd[2];
	int		prev_pipe;

	current = msh->cmd;
	prev_pipe = STDIN_FILENO;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
				perror("pipe");
			process_cmd_with_pipe(msh, current, prev_pipe, pipe_fd);
			prev_pipe = pipe_fd[0];
		}
		else
			process_last_cmd(msh, current, prev_pipe);
		current = current->next;
	}
	if (!msh->cmd->background)
		wait_for_children();
}

void	execute_commands(t_msh *msh)
{
	if (!msh->cmd)
		return ;
	if (!msh->cmd->next && !msh->pipe)
	{
		if (is_builtin(msh->cmd->cmd))
			execute_builtin(msh, msh->cmd);
		else
			execute_single_command(msh, msh->cmd);
		return ;
	}
	execute_pipeline(msh);
}
