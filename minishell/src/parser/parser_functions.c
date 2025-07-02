/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:47:46 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:47:46 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_command_node(t_cmd *node, t_msh *shell, int cmd_idx)
{
	if (node->arg && node->arg[cmd_idx])
	{
		node->cmd = ft_strdup(node->arg[cmd_idx]);
		node->arg = remove_argument_at_index(node->arg, cmd_idx);
		node->num_arg--;
	}
	else
	{
		node->cmd = ft_strdup("");
	}
	node->env = shell->env;
	node->next = NULL;
}

t_cmd	*create_command_node(t_msh *shell, char *segment)
{
	int		cmd_idx;
	t_cmd	*node;

	node = ft_calloc(1, sizeof(t_cmd));
	if (!node)
		exit_error("Error malloc", 9);
	node->num_arg = count_arguments_parser(segment);
	if (node->num_arg > 0)
		node->arg = extract_arguments(shell, segment, node);
	else
		node->arg = NULL;
	cmd_idx = 0;
	while (node->arg && node->arg[cmd_idx]
		&& get_redirect_type(node->arg[cmd_idx]) > 0)
		cmd_idx += 2;
	setup_command_node(node, shell, cmd_idx);
	return (node);
}

void	expand_command_arguments(t_msh *msh, t_cmd **command,
	char *var_reminder)
{
	int		i;
	char	*tmp;

	if (!(*command)->arg)
		return ;
	i = 0;
	while ((*command)->arg[i])
	{
		if (has_variable((*command)->arg[i]))
			(*command)->arg[i] = substitute_variables(msh, *command,
					(*command)->arg[i], &var_reminder);
		if (needs_home_expansion((*command)->arg[i]))
			(*command)->arg[i] = expand_home_directory((*command)->arg[i]);
		tmp = str_noquotes((*command)->arg[i]);
		free((*command)->arg[i]);
		(*command)->arg[i] = tmp;
		i++;
	}
}

void	perform_expansion(t_msh *msh, t_cmd **command)
{
	char	*var_reminder;
	char	*tmp;

	var_reminder = NULL;
	if (has_variable((*command)->cmd))
		(*command)->cmd = substitute_variables(msh, *command, (*command)->cmd,
				&var_reminder);
	if (needs_home_expansion((*command)->cmd))
		(*command)->cmd = expand_home_directory((*command)->cmd);
	tmp = str_noquotes((*command)->cmd);
	free((*command)->cmd);
	(*command)->cmd = tmp;
	expand_command_arguments(msh, command, var_reminder);
}

t_cmd	*get_last_command_node(t_cmd **cmd)
{
	t_cmd	*current;

	current = *cmd;
	while (current && current->next)
		current = current->next;
	return (current);
}
