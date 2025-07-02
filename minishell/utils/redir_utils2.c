/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:48:53 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:48:53 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*preprocess_redirections(const char *line)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*out;
	t_idx	idx;

	i = 0;
	j = 0;
	quote = 0;
	idx.i = &i;
	idx.j = &j;
	out = xmalloc(ft_strlen(line) * 2 + 1);
	while (line[i])
	{
		if (!(handle_quotes(&idx, out, line, &quote)
				|| handle_double_redirections(&idx, out, line)
				|| handle_stderr_redirection(&idx, out, line)
				|| handle_single_redirection(&idx, out, line)))
			out[j++] = line[i++];
	}
	out[j] = '\0';
	return (out);
}

int	handle_quotes(t_idx *idx, char *out, const char *line, char *quote)
{
	size_t	*i;
	size_t	*j;

	i = idx->i;
	j = idx->j;
	if (!*quote && (line[*i] == '"' || line[*i] == '\''))
	{
		*quote = line[*i];
		out[(*j)++] = line[(*i)++];
		return (1);
	}
	if (*quote && line[*i] == *quote)
	{
		out[(*j)++] = line[(*i)++];
		*quote = 0;
		return (1);
	}
	if (*quote)
	{
		out[(*j)++] = line[(*i)++];
		return (1);
	}
	return (0);
}

int	handle_double_redirections(t_idx *idx, char *out, const char *line)
{
	size_t	*i;
	size_t	*j;

	i = idx->i;
	j = idx->j;
	if (line[*i] == '<' && line[*i + 1] == '<')
	{
		out[(*j)++] = '<';
		out[(*j)++] = '<';
		(*i) += 2;
		if (line[*i] && line[*i] != ' ')
			out[(*j)++] = ' ';
		return (1);
	}
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		out[(*j)++] = '>';
		out[(*j)++] = '>';
		(*i) += 2;
		if (line[*i] && line[*i] != ' ')
			out[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

int	handle_stderr_redirection(t_idx *idx, char *out, const char *line)
{
	size_t	*i;
	size_t	*j;

	i = idx->i;
	j = idx->j;
	if (line[*i] == '2' && line[*i + 1] == '>')
	{
		out[(*j)++] = '2';
		if (line[*i + 2] == '>')
		{
			out[(*j)++] = '>';
			out[(*j)++] = '>';
			(*i) += 3;
		}
		else
		{
			out[(*j)++] = '>';
			(*i) += 2;
		}
		if (line[*i] && line[*i] != ' ')
			out[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

int	handle_single_redirection(t_idx *idx, char *out, const char *line)
{
	size_t	*i;
	size_t	*j;

	i = idx->i;
	j = idx->j;
	if (line[*i] == '<' || line[*i] == '>')
	{
		out[(*j)++] = line[(*i)++];
		if (line[*i] && line[*i] != ' ')
			out[(*j)++] = ' ';
		return (1);
	}
	return (0);
}
