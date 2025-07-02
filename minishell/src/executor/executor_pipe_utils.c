/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 23:27:06 by marvin            #+#    #+#             */
/*   Updated: 2025/06/10 23:27:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	last_cmd_child(t_msh *msh, t_cmd *cmd, int prev_pipe)
{
	setup_last_cmd_redirections(prev_pipe);
	if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
		process_redirections(cmd);
	perform_expansion(msh, &cmd);
	execute_last_cmd(msh, cmd);
}

void	wait_fg(t_msh *msh, pid_t pid, int background)
{
	int	status;

	if (background)
		return ;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->error_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		msh->error_value = 128 + WTERMSIG(status);
}
