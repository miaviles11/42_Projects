/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:51:04 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 16:51:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_child(t_cmd *cmd)
{
	int	code;

	code = 0;
	if (cmd->arg && cmd->arg[1])
	{
		if (!is_numeric(cmd->arg[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", cmd->arg[1]);
			code = 255;
		}
		else if (cmd->arg[2])
		{
			ft_printf("exit: too many arguments\n");
			_exit(1);
		}
		else
			code = ft_atoi(cmd->arg[1]);
	}
	_exit(code);
}

void	execute_builtin_with_redirection(t_msh *msh, t_cmd *cmd, int out_fd)
{
	if (out_fd != STDOUT_FILENO && dup2(out_fd, STDOUT_FILENO) == -1)
		exit_error("dup2 failed", 1);
	if (out_fd != STDOUT_FILENO)
		close(out_fd);
	if (!ft_strncmp(cmd->cmd, "exit", 5))
		exit_child(cmd);
	else if (!ft_strncmp(cmd->cmd, "env", 4))
		minishell_env(msh);
	else if (!ft_strncmp(cmd->cmd, "echo", 5))
		minishell_echo(msh);
	else if (!ft_strncmp(cmd->cmd, "cd", 3))
		minishell_cd(msh, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "pwd", 4))
		minishell_pwd(msh);
	else if (!ft_strncmp(cmd->cmd, "export", 7))
		minishell_export(msh, cmd->arg);
	else if (!ft_strncmp(cmd->cmd, "unset", 6))
		minishell_unset(msh, cmd->arg);
	else
		ft_printf("Command not found: %s\n", cmd->cmd);
	_exit(msh->error_value);
}

int	exec_builtin(t_msh *msh, char **argv)
{
	if (!msh || !argv || !argv[0])
		return (1);
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (minishell_cd(msh, argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (minishell_pwd(msh));
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (minishell_echo(msh));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (minishell_exit(msh));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (minishell_env(msh));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (minishell_export(msh, argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (minishell_unset(msh, argv));
	return (0);
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "cd", 3) == 0 || ft_strncmp(cmd_name, "pwd",
			4) == 0 || ft_strncmp(cmd_name, "echo", 5) == 0
		|| ft_strncmp(cmd_name, "exit", 5) == 0 || ft_strncmp(cmd_name, "env",
			4) == 0 || ft_strncmp(cmd_name, "export", 7) == 0
		|| ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_msh *msh, t_cmd *cmd)
{
	int		saved_out;
	int		saved_err;
	char	**argv;

	saved_out = dup(STDOUT_FILENO);
	saved_err = dup(STDERR_FILENO);
	argv = NULL;
	if (cmd->arg && find_first_redirect_index(cmd->arg) != -1)
		process_redirections(cmd);
	setup_builtin_args(msh, cmd, &argv);
	if (!argv)
	{
		cleanup_builtin(saved_out, saved_err);
		return ;
	}
	msh->error_value = exec_builtin(msh, argv);
	free(argv);
	cleanup_builtin(saved_out, saved_err);
}
