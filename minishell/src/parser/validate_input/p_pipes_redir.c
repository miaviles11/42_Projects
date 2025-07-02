/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_pipes_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:32 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:32 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	process_redirection(const char *s, int i, int *count)
{
	if (s[i] == '2' && s[i + 1] == '>')
	{
		(*count)++;
		if (s[i + 2] == '>')
			return (i + 3);
		else
			return (i + 2);
	}
	else if ((s[i] == '>' && s[i + 1] == '>') || (s[i] == '<'
			&& s[i + 1] == '<'))
	{
		(*count)++;
		return (i + 2);
	}
	else if (s[i] == '>' || s[i] == '<')
	{
		(*count)++;
		return (i + 1);
	}
	return (i + 1);
}

int	count_redirections(const char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(i + 1, (char *)s, s[i]);
		else
			i = process_redirection(s, i, &count);
	}
	return (count);
}

char	*extract_redirect_token(char *s)
{
	int		i;
	int		start;
	char	op;

	i = 0;
	while (s[i] && !is_redirect_operator(s[i]))
		i++;
	if (!s[i])
		return (ft_strdup(""));
	op = s[i];
	start = i;
	while (s[i] == op)
		i++;
	return (ft_substr(s, start, i - start));
}

int	validate_redirection_syntax(char **segments, int index)
{
	char	*segment;
	int		rt;
	char	*token;
	char	*tmp;
	char	*msg;

	segment = segments[index];
	rt = get_redirect_type(segment);
	if (rt == -1)
	{
		token = extract_redirect_token(segment);
		tmp = ft_strjoin("syntax error near unexpected token `", token);
		msg = ft_strjoin(tmp, "`");
		put_error("bash", NULL, msg);
		free(token);
		free(tmp);
		free(msg);
		return (-1);
	}
	return (0);
}
