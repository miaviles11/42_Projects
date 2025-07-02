/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 07:12:06 by carlsanc          #+#    #+#             */
/*   Updated: 2025/05/25 15:42:01 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_arguments_redirections(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

int	get_next_diff_op(int i, char *str)
{
	while (str[i] && !is_redirect_operator(str[i]))
		i++;
	return (i);
}

char	**keep_argument(char **args, int idx, char opChar)
{
	char	*temp;

	args = insert_argument_at_index(args,
			ft_substr(args[idx], 0,
				get_next_diff_op(0, args[idx])),
			idx + 1);
	temp = ft_strdup(ft_strchr(args[idx], opChar));
	free(args[idx]);
	args[idx] = temp;
	return (get_filename(args, idx, opChar, 2));
}

void	setup_heredocs_pre_scan(t_cmd *cmd, int heredoc_pipe[2], int *has_hd)
{
	int	i;
	int	idx;

	i = 0;
	idx = find_first_redirect_index(cmd->arg + i);
	while (idx != -1)
	{
		if (get_redirect_type(cmd->arg[i + idx]) == 4)
			setup_heredoc_pipe(heredoc_pipe, has_hd);
		i += idx + 2;
		idx = find_first_redirect_index(cmd->arg + i);
	}
}

void	apply_redirections(t_cmd *cmd, int heredoc_pipe[2])
{
	int	i;
	int	idx;

	i = 0;
	idx = find_first_redirect_index(cmd->arg + i);
	while (idx != -1)
	{
		process_single_redirection(cmd, &i, heredoc_pipe);
		idx = find_first_redirect_index(cmd->arg + i);
	}
}
