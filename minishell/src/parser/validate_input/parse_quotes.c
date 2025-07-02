/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:39 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:39 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	both_quotes_exist(const char *s, int *i, char quote)
{
	int	pairing;

	pairing = 1;
	while (s[*i + 1] && s[*i + 1] != quote)
		(*i)++;
	if (s[*i + 1] == quote)
		pairing++;
	(*i)++;
	return (pairing);
}

int	check_quotes_balance(const char *s, t_msh *shell)
{
	int	i;
	int	simple_count;
	int	double_count;

	i = 0;
	simple_count = 0;
	double_count = 0;
	while (s[i])
	{
		if (s[i] == '"')
			double_count += both_quotes_exist(s, &i, '"');
		else if (s[i] == '\'')
			simple_count += both_quotes_exist(s, &i, '\'');
		if ((double_count % 2) != 0 || (simple_count % 2) != 0)
		{
			shell->quote = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_next_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
