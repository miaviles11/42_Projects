/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arguments_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:49:23 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:49:23 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*extract_command(t_msh *shell, char *segment)
{
	int		i;
	int		start;
	char	*command;

	i = skip_spaces(segment, 0);
	i = skip_initial_redirections(segment, i);
	start = i;
	while (segment[i] && get_redirect_type(segment + i) == 0
		&& segment[i] != ' ' && !(segment[i] >= 9 && segment[i] <= 13))
	{
		i = skip_token(segment, i);
	}
	if (i > start)
		command = ft_substr(segment, start, i - start);
	else
		command = ft_strdup("");
	shell->total_chars += i;
	return (command);
}

int	count_arguments_parser(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '"' && s[i] != '\'') && (s[i + 1] == ' '
				|| s[i + 1] == '\0' || s[i + 1] == '"' || s[i + 1] == '\''))
			count++;
		if (s[i] == '"' || s[i] == '\'')
		{
			count++;
			i = get_next_quote(i + 1, s, s[i]);
		}
		i++;
	}
	return (count);
}
