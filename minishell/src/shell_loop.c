/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:51:25 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:51:25 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_interactive = 1;

void	run_shell_loop(t_msh *shell)
{
	char	*raw_line;
	char	*line;
	t_cmd	*old_cmd;
	int		interactive;

	interactive = isatty(STDIN_FILENO);
	while (1)
	{
		raw_line = get_input_line(interactive);
		if (!raw_line)
			break ;
		if (process_raw_line(&raw_line))
			continue ;
		if (interactive)
			add_history(raw_line);
		line = preprocess_redirections(raw_line);
		free(raw_line);
		process_command_line(shell, line, &old_cmd);
		free(line);
	}
	if (interactive)
		write(STDOUT_FILENO, "exit\n", 5);
}

char	*get_input_line(int interactive)
{
	char	*raw_line;

	if (interactive)
	{
		g_interactive = 1;
		raw_line = readline("minishell-> ");
	}
	else
	{
		g_interactive = 0;
		raw_line = get_next_line(STDIN_FILENO);
	}
	return (raw_line);
}

int	process_raw_line(char **raw_line)
{
	size_t	len;

	len = ft_strlen(*raw_line);
	if (len > 0 && (*raw_line)[len - 1] == '\n')
		(*raw_line)[len - 1] = '\0';
	if (is_line_empty(*raw_line))
	{
		free(*raw_line);
		return (1);
	}
	return (0);
}

void	process_command_line(t_msh *shell, char *line, t_cmd **old_cmd)
{
	*old_cmd = shell->cmd;
	if (parse_input_line(shell, &shell->cmd, line))
	{
		execute_command(shell);
	}
	if (*old_cmd != shell->cmd)
		free_command_list(*old_cmd);
}

void	execute_command(t_msh *shell)
{
	g_interactive = 0;
	if (is_exit_command(shell))
		return ;
	if (!shell->pipe && shell->cmd && shell->cmd->cmd
		&& is_builtin(shell->cmd->cmd))
	{
		execute_builtin(shell, shell->cmd);
	}
	else if (shell->cmd)
	{
		execute_commands(shell);
	}
	g_interactive = 1;
}
