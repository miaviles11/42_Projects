/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:50:08 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:50:08 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	needs_home_expansion(const char *s)
{
	if (s && s[0] == '~' && (!s[1] || s[1] == '/'))
		return (1);
	return (0);
}

char	*expand_home_directory(char *s)
{
	char	*home;
	char	*rest;
	char	*result;

	rest = ft_strdup(s + 1);
	home = ft_strdup(getenv("HOME"));
	if (!home)
		exit_error("Error malloc", 50);
	result = ft_strjoin(home, rest);
	free(home);
	free(rest);
	free(s);
	return (result);
}

char	*expand_translation(t_msh *msh, char *line)
{
	char	*inside;
	char	*suffix;
	char	*res;
	int		end;

	(void)msh;
	if (!detect_translation(line, &end))
		return (line);
	inside = ft_substr(line + 2, 0, end - 2);
	suffix = ft_strdup(line + end + 1);
	res = ft_strjoin(inside, suffix);
	free(inside);
	free(suffix);
	free(line);
	return (res);
}

int	detect_translation(const char *line, int *end)
{
	int	i;

	if (!line || line[0] != '$' || line[1] != '"')
		return (0);
	i = get_next_quote(2, (char *)line, '"');
	if (line[i] != '"')
		return (0);
	*end = i;
	return (1);
}

char	*replace_special_value(char *s, int error_value)
{
	int	i;
	int	j;

	i = get_next_quote(0, s, '?') - 1;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
			s = replace_special_value_helper(s, i, error_value);
		j = i;
		i = get_next_quote(0, s, '$');
		if (j == i)
			break ;
	}
	return (s);
}
