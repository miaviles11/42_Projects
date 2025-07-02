/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:50:03 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:50:03 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	compare_env_variable_name(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s2[i] && s2[i] != '=')
		i++;
	if (ft_strlen(s1) != i)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*extract_env_value(const char *envVar)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	while (envVar[i] && envVar[i] != '=')
		i++;
	if (!envVar[i])
		return (ft_strdup(""));
	i++;
	len = ft_strlen(envVar) - i;
	result = malloc(len + 1);
	if (!result)
		exit_error("Error malloc", 17);
	ft_strlcpy(result, envVar + i, len + 1);
	return (result);
}

char	*split_variable_reminder(char *line, int index, t_cmd *cmd)
{
	int		len;
	int		i;
	char	*res;

	cmd->flags->dollar_special = 1;
	len = 0;
	while (line[index + len])
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		exit_error("Error malloc", 17);
	i = 0;
	while (i < len)
	{
		res[i] = line[index + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*replace_special_value_helper(char *s, int i, int error_value)
{
	char	*errorstr;
	char	*prefix;
	char	*suffix;
	char	*result;
	char	*temp;

	errorstr = ft_itoa(error_value);
	prefix = ft_substr(s, 0, i);
	suffix = ft_strdup(s + i + 2);
	result = ft_strjoin(prefix, errorstr);
	temp = result;
	result = ft_strjoin(result, suffix);
	free(temp);
	free(prefix);
	free(suffix);
	free(errorstr);
	free(s);
	return (result);
}
