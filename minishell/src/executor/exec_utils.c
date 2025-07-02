/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:19:08 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 17:40:46 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_for_children(void)
{
	pid_t	wpid;
	int		status;

	wpid = wait(&status);
	while (wpid > 0)
		;
}

char	*check_command_path(char *cmd)
{
	if (cmd[0] == '/' || cmd[0] == '.' || ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

static char	*build_full_path(char *dir, char *cmd)
{
	char	*full_path;
	char	*temp;

	full_path = ft_strjoin(dir, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, cmd);
	free(temp);
	return (full_path);
}

char	*search_in_path(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	if (!(path_env) || !(paths))
		return (NULL);
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

void	execute_last_cmd(t_msh *msh, t_cmd *cmd)
{
	char	**argv;
	char	*exe;

	if (is_builtin(cmd->cmd))
	{
		execute_builtin_with_redirection(msh, cmd, STDOUT_FILENO);
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
