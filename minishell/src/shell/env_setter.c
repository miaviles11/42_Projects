/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:22:55 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/20 18:43:43 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_env_value(t_msh *shell, const char *var_name, const char *value)
{
	int	i;
	int	len;

	i = 0;
	if (!shell || !var_name || !value)
		return (-1);
	len = strlen(var_name);
	while (i < shell->num_env)
	{
		if (check_env_var(shell->env[i], var_name, len))
			return (update_existing_env(shell, i, var_name, value));
		i++;
	}
	return (add_new_env(shell, var_name, value));
}

int	check_env_var(char *env_entry, const char *var_name, int len)
{
	return (strncmp(env_entry, var_name, len) == 0
		&& env_entry[len] == '=');
}

int	update_existing_env(t_msh *shell, int i, const char *var_name,
						const char *value)
{
	char	*new_entry;
	int		len;

	len = strlen(var_name);
	free(shell->env[i]);
	new_entry = malloc(len + strlen(value) + 2);
	if (!new_entry)
		return (-1);
	create_env_entry(new_entry, var_name, value);
	shell->env[i] = new_entry;
	return (0);
}

int	add_new_env(t_msh *shell, const char *var_name, const char *value)
{
	char	**new_env;
	char	*new_entry;
	int		len;

	len = strlen(var_name);
	new_env = realloc(shell->env, sizeof(char *) * (shell->num_env + 2));
	if (!new_env)
		return (-1);
	shell->env = new_env;
	new_entry = malloc(len + strlen(value) + 2);
	if (!new_entry)
		return (-1);
	create_env_entry(new_entry, var_name, value);
	shell->env[shell->num_env] = new_entry;
	shell->env[shell->num_env + 1] = NULL;
	shell->num_env++;
	return (0);
}

void	create_env_entry(char *entry, const char *var_name, const char *value)
{
	strcpy(entry, var_name);
	strcat(entry, "=");
	strcat(entry, value);
}
