/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:07:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 17:14:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_cmd_with_pipe(t_msh *msh, t_cmd *cmd, int prev_pipe,
	int *pipe_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		setup_pipe_redirections(prev_pipe, pipe_fd);
		if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
			process_redirections(cmd);
		perform_expansion(msh, &cmd);
		execute_cmd_in_pipe(msh, cmd);
	}
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->error_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		msh->error_value = 128 + WTERMSIG(status);
}

void	setup_pipe_redirections(int prev_pipe, int *pipe_fd)
{
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
}

void	process_last_cmd(t_msh *msh, t_cmd *cmd, int prev_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ((void)perror("fork"));
	if (pid == 0)
		last_cmd_child(msh, cmd, prev_pipe);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	wait_fg(msh, pid, cmd->background);
}

void	setup_last_cmd_redirections(int prev_pipe)
{
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
}

void	execute_cmd_in_pipe(t_msh *msh, t_cmd *cmd)
{
	char	**argv;
	char	*exe;

	if (is_builtin(cmd->cmd))
	{
		execute_builtin_with_redirection(msh, cmd, STDOUT_FILENO);
		_exit(msh->error_value);
	}
	else
	{
		argv = prepare_argv(cmd);
		exe = find_executable(cmd->cmd);
		execve(exe, argv, msh->env);
		perror("execve");
		_exit(1);
	}
}
