/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:34:47 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 16:40:32 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_duplicate_env(char **env, int *len)
{
	char	**sorted;
	int		i;

	if (!env)
		return (NULL);
	*len = 0;
	while (env[*len])
		(*len)++;
	sorted = malloc(sizeof(char *) * (*len + 1));
	if (!sorted)
		exit_error("Error malloc", 1);
	i = 0;
	while (i < *len)
	{
		sorted[i] = ft_strdup(env[i]);
		if (!sorted[i])
			exit_error("Error malloc", 1);
		i++;
	}
	sorted[*len] = NULL;
	return (sorted);
}

char	**ft_sort_env_array(char **sorted, int len)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

char	**ft_split_sort_env(char **env)
{
	char	**sorted;
	int		len;

	len = 0;
	sorted = ft_duplicate_env(env, &len);
	if (!sorted)
		return (NULL);
	return (ft_sort_env_array(sorted, len));
}
