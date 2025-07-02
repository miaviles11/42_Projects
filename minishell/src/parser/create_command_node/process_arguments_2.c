/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_arguments_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:49:30 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:49:30 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	split_arguments(char *s, char **arg)
{
	int	pos;
	int	start;
	int	i;

	start = 0;
	pos = 0;
	i = -1;
	while (s[++i])
	{
		if ((s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)) && s[i + 1]
			&& s[i + 1] != ' ')
			start = i + 1;
		if (s[i] == '"' || s[i] == '\'')
			i = get_next_quote(i + 1, s, s[i]);
		if (s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13) && (s[i + 1] == ' '
				|| s[i + 1] == '\0'))
		{
			arg[pos] = ft_substr(s, start, i - start + 1);
			if (!arg[pos])
				exit_error("Error malloc", 14);
			pos++;
		}
	}
	arg[pos] = NULL;
	return (i);
}

char	**extract_arguments(t_msh *shell, char *segment, t_cmd *command)
{
	char	**args;
	char	*processedsegment;

	processedsegment = segment;
	if (check_null_args(processedsegment) == -1)
		processedsegment = change_null_args(ft_strtrim(processedsegment, " "),
				command);
	args = malloc(sizeof(char *) * (command->num_arg + 1));
	if (!args)
		exit_error("Error malloc", 13);
	shell->total_chars += split_arguments(segment, args);
	if (check_null_args(segment) == -1)
		free(processedsegment);
	return (args);
}

int	check_null_args(char *s)
{
	int	i;
	int	dq_flag;
	int	sq_flag;

	i = 0;
	dq_flag = 1;
	sq_flag = 1;
	while (s[i])
	{
		if (s[i] == '"')
			dq_flag *= -1;
		if (s[i] == '\'')
			sq_flag *= -1;
		if (s[i] == ' ' && s[i + 1] == '"' && s[i + 2] == '"'
			&& s[i + 3] == ' ')
			return (-1);
		else if (s[i] == ' ' && s[i + 1] == '\'' && s[i + 2] == '\''
			&& s[i + 3] == ' ')
			return (-1);
		else if ((s[i] == '"' && s[i + 1] == '"' && sq_flag != -1)
			|| (s[i] == '\'' && s[i + 1] == '\'' && dq_flag != -1))
			return (-1);
		i++;
	}
	return (0);
}

static char	*cn_loop(char *s, t_cmd *cmd, int i)
{
	while (s[i])
	{
		if ((s[i] == '"' && s[i + 1] && s[i + 1] != '"')
			|| (s[i] == '\'' && s[i + 1] && s[i + 1] != '\''))
			i = get_next_quote(i + 1, s, s[i]);
		if (s[i] == ' ' && (s[i + 1] == '"' || s[i + 1] == '\'')
			&& (s[i + 2] == '"' || s[i + 2] == '\'')
			&& (s[i + 3] == ' ' || s[i + 3] == '\0'))
		{
			i++;
			s = quit_null_space(s, i);
			s = change_null_args(s, cmd);
		}
		else if ((s[i] == '"' && s[i + 1] == '"')
			|| (s[i] == '\'' && s[i + 1] == '\''))
		{
			s = quit_null(s, i);
			cmd->num_arg--;
			return (change_null_args(s, cmd));
		}
		i++;
	}
	return (s);
}

char	*change_null_args(char *s, t_cmd *cmd)
{
	return (cn_loop(s, cmd, 0));
}
