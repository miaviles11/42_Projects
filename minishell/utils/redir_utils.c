/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:14:06 by carlsanc          #+#    #+#             */
/*   Updated: 2025/03/15 13:14:06 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirect_operator(char c)
{
	return (c == '>' || c == '<');
}

int	get_redirect_type(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(i + 1, s, s[i]);
		if (!ft_strncmp(s + i, "<<<", 3))
			return (-1);
		if (!ft_strncmp(s + i, "2>>", 3))
			return (6);
		if (!ft_strncmp(s + i, "2>", 2) && !is_redirect_operator(s[i + 2]))
			return (5);
		if (!ft_strncmp(s + i, ">>", 2) && !is_redirect_operator(s[i + 2]))
			return (2);
		if (s[i] == '>' && !is_redirect_operator(s[i + 1]))
			return (1);
		if (!ft_strncmp(s + i, "<<", 2) && !is_redirect_operator(s[i + 2]))
			return (4);
		if (s[i] == '<' && !is_redirect_operator(s[i + 1]))
			return (3);
		if (is_redirect_operator(s[i]))
			return (-1);
	}
	return (0);
}

int	find_first_redirect_index(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (get_redirect_type(args[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	get_operator_for_type(int n)
{
	if (n == 1 || n == 2 || n == 5 || n == 6)
		return ('>');
	else if (n == 3 || n == 4)
		return ('<');
	return (0);
}

int	find_next_redirect_operator_index(int i, char *str)
{
	while (str[i] && !is_redirect_operator(str[i]))
		i++;
	return (i);
}
