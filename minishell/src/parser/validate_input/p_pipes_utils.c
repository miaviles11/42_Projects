/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipes_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:26 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:26 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**extract_pipe_segments(char *s, char **segments)
{
	int	i;
	int	start;
	int	pos;

	i = 0;
	start = 0;
	pos = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(i + 1, s, s[i]);
		if ((s[i + 1] == '|' || s[i + 1] == '\0') && s[i] != '|')
		{
			segments[pos] = ft_substr(s, start, i - start + 1);
			if (!segments[pos])
				exit_error("Error malloc", 54);
			pos++;
		}
		if (s[i] == '|' && s[i + 1] && s[i + 1] != '|')
			start = i + 1;
		i++;
	}
	segments[pos] = NULL;
	return (segments);
}

int	validate_pipe_segment(char *segment)
{
	int	i;

	i = 0;
	while (segment[i])
	{
		if (segment[i] != ' ' && segment[i] != '\t' && segment[i] != '\n')
			return (0);
		i++;
	}
	put_error("bash", NULL, "syntax error near unexpected token `|' ");
	return (-1);
}
