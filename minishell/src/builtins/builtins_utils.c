/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:44:14 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 15:44:14 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_existing_env_var(t_msh *msh, const char *name, const char *value)
{
	int		i;
	char	*temp;
	char	*new_var;

	i = 0;
	temp = ft_strjoin(name, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	while (i < msh->num_env)
	{
		if (ft_strncmp(msh->env[i], name, ft_strlen(name)) == 0
			&& msh->env[i][ft_strlen(name)] == '=')
		{
			free(msh->env[i]);
			msh->env[i] = new_var;
			setenv(name, value, 1);
			return (0);
		}
		i++;
	}
	free(new_var);
	return (1);
}

int	add_new_env_var(t_msh *msh, const char *name, const char *value)
{
	int		i;
	char	*temp;
	char	*new_var;
	char	**new_env;

	temp = ft_strjoin(name, "=");
	new_var = ft_strjoin(temp, value);
	free(temp);
	new_env = malloc(sizeof(char *) * (msh->num_env + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < msh->num_env)
	{
		new_env[i] = msh->env[i];
		i++;
	}
	new_env[msh->num_env] = new_var;
	new_env[msh->num_env + 1] = NULL;
	free(msh->env);
	msh->env = new_env;
	msh->num_env++;
	setenv(name, value, 1);
	return (0);
}

int	set_env_var(t_msh *msh, const char *name, const char *value)
{
	if (update_existing_env_var(msh, name, value) == 0)
		return (0);
	return (add_new_env_var(msh, name, value));
}

int	is_valid_identifier(const char *var)
{
	int	i;

	i = 1;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
