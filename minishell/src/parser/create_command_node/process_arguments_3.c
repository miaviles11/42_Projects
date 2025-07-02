/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arguments_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:49:36 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:49:36 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	skip_spaces(const char *s, int i)
{
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	return (i);
}

int	skip_token(const char *s, int i)
{
	if (s[i] == '\"' || s[i] == '\'')
		return (get_next_quote(i + 1, (char *)s, s[i]) + 1);
	return (i + 1);
}

int	get_operator_length(int rtype)
{
	if (rtype == 1 || rtype == 3)
		return (1);
	if (rtype == 2 || rtype == 4 || rtype == 5)
		return (2);
	return (3);
}

int	skip_initial_redirections(const char *s, int i)
{
	int	rtype;
	int	len;

	rtype = get_redirect_type((char *)s + i);
	while (rtype > 0)
	{
		len = get_operator_length(rtype);
		i += len;
		i = skip_spaces(s, i);
		while (s[i] && get_redirect_type((char *)s + i) == 0 && s[i] != ' '
			&& !(s[i] >= 9 && s[i] <= 13))
			i = skip_token(s, i);
		i = skip_spaces(s, i);
	}
	return (i);
}
