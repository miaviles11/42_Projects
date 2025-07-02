/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_braced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:49:52 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:49:52 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parse_braced(const char *line, int *colon, int *end)
{
	int	i;

	if (!line || line[0] != '$' || line[1] != '{')
		return (0);
	i = 2;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i] != ':')
		return (0);
	*colon = i;
	while (line[i] && line[i] != '}')
		i++;
	if (line[i] != '}')
		return (0);
	*end = i;
	return (1);
}

char	*expand_braced_substring(t_msh *msh, char *line)
{
	char	*name;
	char	*value;
	char	*res;
	int		colon;
	int		end;

	if (!parse_braced(line, &colon, &end))
		return (line);
	name = ft_substr(line + 2, 0, colon - 2);
	value = get_env_value(msh, name);
	free(name);
	if (!value)
		value = ft_strdup("");
	res = process_braced_value(value, ft_atoi(line + colon + 1),
			ft_strdup(line + end + 1));
	free(value);
	free(line);
	return (res);
}

char	*process_braced_value(char *value, int offset, char *suffix)
{
	char	*substr;
	char	*res;

	if (offset < (int)ft_strlen(value))
		substr = ft_strdup(value + offset);
	else
		substr = ft_strdup("");
	res = ft_strjoin(substr, suffix);
	free(substr);
	free(suffix);
	return (res);
}

char	*compare_variable_name(t_msh *msh, char *line, char *nameVar)
{
	int		envindex;
	char	*varvalue;

	envindex = 0;
	while (envindex < msh->num_env)
	{
		if (compare_env_variable_name(nameVar, msh->env[envindex]) == 0)
		{
			free(nameVar);
			varvalue = extract_env_value(msh->env[envindex]);
			return (replace_variable_in_line(line, varvalue));
		}
		envindex++;
	}
	free(nameVar);
	return (replace_variable_in_line(line, ft_strdup("")));
}

char	*replace_variable_in_line(char *line, char *var)
{
	int		pos;
	int		name_len;
	int		new_len;
	char	*new_line;

	pos = find_next_dollar(line, 0);
	if (pos < 0)
		return (line);
	name_len = 1;
	while (line[pos + name_len] && special_char_ck(line[pos + name_len]) == 0)
		name_len++;
	new_len = pos + ft_strlen(var) + ft_strlen(line + pos + name_len) + 1;
	new_line = malloc(new_len);
	if (!new_line)
		exit_error("Error malloc", 18);
	ft_strlcpy(new_line, line, pos + 1);
	ft_strlcat(new_line, var, new_len);
	ft_strlcat(new_line, line + pos + name_len, new_len);
	free(line);
	free(var);
	return (new_line);
}
