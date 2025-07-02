/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:51 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:51 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_and_split_input(t_msh *shell, char *inputline, char ***segments)
{
	shell->quote = check_quotes_balance(inputline, shell);
	if (shell->quote == 0)
	{
		return (1);
	}
	shell->pipe = count_pipes(inputline, shell);
	if (shell->pipe == -1)
	{
		return (1);
	}
	*segments = split_pipes(inputline, shell);
	if (!(*segments))
	{
		return (1);
	}
	return (0);
}

int	parse_input_line(t_msh *shell, t_cmd **commandList, char *inputline)
{
	int		i;
	t_cmd	*newcommand;
	char	**splitsegments;

	shell->total_chars = 0;
	if (validate_and_split_input(shell, inputline, &splitsegments))
		return (0);
	*commandList = create_command_node(shell, splitsegments[0]);
	i = 1;
	while (i <= shell->pipe)
	{
		shell->total_chars = 0;
		newcommand = create_command_node(shell, splitsegments[i]);
		get_last_command_node(commandList)->next = newcommand;
		i++;
	}
	i = 0;
	while (splitsegments[i])
		free(splitsegments[i++]);
	free(splitsegments);
	return (1);
}
