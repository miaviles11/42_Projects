/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:51:04 by carlsanc          #+#    #+#             */
/*   Updated: 2025/05/05 16:51:04 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_stdin_to_stdout(void)
{
	char	buf[4096];
	ssize_t	n;

	n = read(STDIN_FILENO, buf, sizeof(buf));
	while (n > 0)
	{
		write(STDOUT_FILENO, buf, n);
		n = read(STDIN_FILENO, buf, sizeof(buf));
	}
}

static void	redir_child(t_cmd *cmd)
{
	if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
		process_redirections(cmd);
	if (!isatty(STDIN_FILENO))
		copy_stdin_to_stdout();
	_exit(0);
}

static void	wait_and_set_status(t_msh *msh, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->error_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		msh->error_value = 128 + WTERMSIG(status);
}

void	redir_only_child(t_msh *msh, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
		redir_child(cmd);
	wait_and_set_status(msh, pid);
}
