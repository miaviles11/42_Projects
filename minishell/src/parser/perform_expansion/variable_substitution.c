/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_substitution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:50:18 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:50:18 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*substitute_variables(t_msh *msh, t_cmd *cmd, char *s,
		char **varReminder)
{
	char	*prev_s;

	if (!cmd->flags)
	{
		cmd->flags = calloc(1, sizeof(*(cmd->flags)));
		if (!cmd->flags)
			exit_error("Error malloc flags", 12);
	}
	if (check_variable_and_digit(s) == 0)
		s = quit_variable_and_digit(s);
	prev_s = NULL;
	while (has_variable(s))
	{
		cmd->flags->dollar_special = 0;
		prev_s = ft_strdup(s);
		s = substitute_variable_value(msh, cmd, s, varReminder);
		handle_special_case(cmd, &s, varReminder);
		if (ft_strcmp(prev_s, s) == 0)
		{
			free(prev_s);
			break ;
		}
		free(prev_s);
	}
	return (s);
}

char	*substitute_variable_value(t_msh *msh, t_cmd *cmd, char *line,
		char **varReminder)
{
	char	*tmp;

	if (is_literal_dollar(line))
		return (line);
	tmp = expand_translation(msh, line);
	if (tmp != line)
		return (tmp);
	tmp = expand_braced_substring(msh, line);
	if (tmp != line)
		return (tmp);
	if (ft_strnstr(line, "$?", ft_strlen(line)))
		return (replace_special_value(line, msh->error_value));
	init_flags(cmd);
	if (check_variable_and_digit(line) == 0)
		line = quit_variable_and_digit(line);
	return (handle_special_variable(msh, cmd, line, varReminder));
}

void	handle_special_case(t_cmd *cmd, char **s, char **varReminder)
{
	char	*temp;

	if (cmd->flags->dollar_special == 1 && varReminder && *varReminder)
	{
		temp = join_special(*s, *varReminder);
		free(*s);
		*s = temp;
		free(*varReminder);
		*varReminder = NULL;
		cmd->flags->dollar_special = 0;
	}
}

char	*handle_special_variable(t_msh *msh, t_cmd *cmd, char *line,
		char **varReminder)
{
	char	*varname;
	int		i;
	int		nameindex;
	int		namelen;

	varname = extract_variable_name(line);
	if (!varname)
		return (line);
	i = find_next_dollar(line, -1);
	if (i == -1)
	{
		free(varname);
		return (line);
	}
	nameindex = i + 1;
	namelen = ft_strlen(varname);
	i = nameindex + namelen - 1;
	(handle_special_chars(line, i, varReminder, cmd));
	return (compare_variable_name(msh, line, varname));
}

int	handle_special_chars(char *line, int i, char **varReminder, t_cmd *cmd)
{
	if (line[i + 1] && ((special_char_ck(line[i + 1]) == -1
				&& line[i + 1] != '$' && line[i + 1] != '"')
			|| (line[i + 1] == '$'
				&& (i + 1) == find_next_dollar(line, i))))
	{
		if (varReminder)
		{
			*varReminder = ft_strdup(line + i + 1);
			cmd->flags->dollar_special = 1;
			line[i + 1] = '\0';
		}
		return (1);
	}
	return (0);
}
