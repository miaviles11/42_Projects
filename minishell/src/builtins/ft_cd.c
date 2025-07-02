/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:05 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:05 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	change_to_oldpwd(t_msh *msh, char *oldpwd, char *current_pwd)
{
	if (getcwd(current_pwd, 1024) == NULL)
	{
		if (!getenv("PWD"))
		{
			ft_printf("cd: PWD no disponible\n");
			return (1);
		}
		ft_strlcpy(current_pwd, getenv("PWD"), 1024);
	}
	if (chdir(oldpwd) != 0)
	{
		perror("cd");
		return (1);
	}
	set_env_var(msh, "PWD", oldpwd);
	set_env_var(msh, "OLDPWD", current_pwd);
	ft_printf("%s\n", oldpwd);
	return (0);
}

static int	change_directory(t_msh *msh, char *path, char *cwd)
{
	char	old_cwd[1024];

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		if (!getenv("PWD"))
		{
			ft_printf("cd: PWD no disponible\n");
			return (1);
		}
		ft_strlcpy(old_cwd, getenv("PWD"), sizeof(old_cwd));
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	set_env_var(msh, "OLDPWD", old_cwd);
	if (getcwd(cwd, 1024) != NULL)
		set_env_var(msh, "PWD", cwd);
	return (0);
}

int	minishell_cd(t_msh *msh, char **argv)
{
	char	cwd[1024];
	char	*oldpwd;
	char	*path;

	if (argv[1] && argv[1][0] == '-' && argv[1][1] == '\0')
	{
		oldpwd = getenv("OLDPWD");
		if (!oldpwd)
		{
			ft_printf("cd: OLDPWD not set\n");
			return (1);
		}
		return (change_to_oldpwd(msh, oldpwd, cwd));
	}
	if (argv[1])
		path = argv[1];
	else
		path = getenv("HOME");
	if (!path)
	{
		ft_printf("cd: HOME not set\n");
		return (1);
	}
	return (change_directory(msh, path, cwd));
}
