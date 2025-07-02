/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:12 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:12 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	skip_quoted_segment(const char *s, int i, char quote)
{
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static int	count_valid_pipes(const char *inputline, t_msh *msh)
{
	int	i;
	int	pipecount;

	i = 0;
	pipecount = 0;
	while (inputline[i])
	{
		if (inputline[i] == '"' || inputline[i] == '\'')
		{
			i = skip_quoted_segment(inputline, i, inputline[i]);
			continue ;
		}
		if (inputline[i] == '|' && (inputline[i + 1] == '|'
				|| inputline[i + 1] == '\0'))
		{
			put_error("bash", NULL,
				"syntax error near unexpected token `|'");
			msh->error_value = 258;
			return (-1);
		}
		else if (inputline[i] == '|')
			pipecount++;
		i++;
	}
	return (pipecount);
}

int	count_pipes(const char *inputline, t_msh *msh)
{
	if (inputline[0] == '|')
	{
		put_error("bash", NULL, "syntax error near unexpected token `|'");
		msh->error_value = 258;
		return (-1);
	}
	return (count_valid_pipes(inputline, msh));
}

char	**split_pipes(char *inputline, t_msh *msh)
{
	char	**segments;
	int		i;

	segments = ft_calloc(count_pipes(inputline, msh) + 2, sizeof(char *));
	if (!segments)
		exit_error("Error malloc", 54);
	segments = extract_pipe_segments(inputline, segments);
	i = 0;
	while (segments[i])
	{
		if (validate_pipe_segment(segments[i]) == -1
			|| validate_redirection_syntax(segments, i) == -1)
		{
			msh->error_value = 258;
			while (i >= 0)
				free(segments[i--]);
			free(segments);
			return (NULL);
		}
		i++;
	}
	return (segments);
}
