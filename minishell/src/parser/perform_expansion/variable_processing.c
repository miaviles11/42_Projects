/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:50:13 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:50:13 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*quit_variable_and_digit(char *s)
{
	int		i;
	int		j;
	char	*result;
	int		len;

	len = ft_strlen(s);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		exit_error("Error malloc", 15);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] && is_digit_special(s[i + 1]) == 1)
		{
			i += 2;
			continue ;
		}
		result[j++] = s[i++];
	}
	result[j] = '\0';
	free(s);
	return (result);
}

int	is_literal_dollar(const char *line)
{
	if (!line || line[0] != '$')
		return (0);
	if (line[1] == '\0')
		return (1);
	if (line[1] != '{' && line[1] != '?' && !ft_isalnum(line[1])
		&& line[1] != '_')
		return (1);
	return (0);
}

void	init_flags(t_cmd *cmd)
{
	if (!cmd->flags)
	{
		cmd->flags = calloc(1, sizeof(*(cmd->flags)));
		if (!cmd->flags)
			exit_error("Error malloc flags", 12);
	}
}

int	special_char_ck(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || c == '_')
	{
		return (0);
	}
	return (-1);
}

char	*join_special(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;
	size_t	i;
	size_t	j;

	len1 = ft_strlen(s1);
	if (len1 > 0 && (s1[len1 - 1] == '"' || s1[len1 - 1] == '\''))
		len1--;
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		exit_error("Error malloc", 51);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = -1;
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}
