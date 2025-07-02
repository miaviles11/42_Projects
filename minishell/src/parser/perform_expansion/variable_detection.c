/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_detection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:49:57 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:49:57 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	has_variable(const char *s)
{
	int	i;
	int	in_dq;
	int	in_sq;

	i = 0;
	in_dq = 0;
	in_sq = 0;
	while (s[i])
	{
		if (s[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (s[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (s[i] == '$' && !in_sq && s[i + 1] && s[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_variable_and_digit(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	if (s[i] == '$' && s[i + 1] && is_digit_special(s[i + 1]) == 1)
		return (0);
	return (1);
}

int	is_digit_special(int c)
{
	if (c == '*' || c == '@' || c == '\\')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

char	*extract_variable_name(char *line)
{
	int		i;
	int		length;
	char	*result;

	i = get_next_quote(0, line, '$') + 1;
	length = 0;
	while (line[i + length] && line[i + length] != ' '
		&& line[i + length] != '"' && line[i + length] != '\''
		&& special_char_ck(line[i + length]) == 0)
		length++;
	result = ft_calloc(length + 1, sizeof(char));
	if (!result)
		exit_error("Error malloc", 16);
	length = 0;
	while (line[i + length] && line[i + length] != ' '
		&& line[i + length] != '"' && line[i + length] != '\''
		&& special_char_ck(line[i + length]) == 0)
	{
		result[length] = line[i + length];
		length++;
	}
	return (result);
}

int	find_next_dollar(const char *s, int start)
{
	int	i;
	int	in_dq;
	int	in_sq;

	if (start < 0)
		i = 0;
	else
		i = start;
	in_dq = 0;
	in_sq = 0;
	while (s[i])
	{
		if (s[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else if (s[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (s[i] == '$' && !in_sq)
			return (i);
		i++;
	}
	return (-1);
}
