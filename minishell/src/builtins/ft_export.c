/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:32:29 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 16:32:29 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_no_equal(t_msh *msh, const char *arg)
{
	char	*key;
	char	*existing_value;

	key = ft_strdup(arg);
	if (!key)
		return ;
	existing_value = getenv(key);
	if (existing_value)
		set_env_var(msh, key, existing_value);
	else
		set_env_var(msh, key, "");
	free(key);
}

void	update_env(t_msh *msh, const char *arg)
{
	char	*key;
	char	*value;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
	{
		handle_no_equal(msh, arg);
		return ;
	}
	key = ft_substr(arg, 0, equal_pos - arg);
	value = ft_strdup(equal_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	set_env_var(msh, key, value);
	free(key);
	free(value);
}

void	print_sorted_env(char **sorted)
{
	int		j;
	char	*eq;

	j = 0;
	while (sorted[j])
	{
		eq = ft_strchr(sorted[j], '=');
		if (eq)
		{
			*eq = '\0';
			printf("declare -x %s=\"%s\"\n", sorted[j], eq + 1);
			*eq = '=';
		}
		else
		{
			printf("declare -x %s\n", sorted[j]);
		}
		j++;
	}
}

int	export_no_args(t_msh *msh)
{
	char	**sorted;

	sorted = ft_split_sort_env(msh->env);
	if (!sorted)
		return (1);
	print_sorted_env(sorted);
	ft_free_split(sorted);
	return (0);
}

int	minishell_export(t_msh *msh, char **argv)
{
	int	i;

	if (!argv[1])
		return (export_no_args(msh));
	i = 1;
	while (argv[i])
	{
		if (is_valid_identifier(argv[i]))
			update_env(msh, argv[i]);
		else
			ft_printf("export: `%s': not a valid identifier\n", argv[i]);
		i++;
	}
	return (0);
}
