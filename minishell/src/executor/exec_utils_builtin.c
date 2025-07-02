/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:32:36 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 17:33:38 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_builtin_args(t_msh *msh, t_cmd *cmd, char ***argv)
{
	int	argc;
	int	j;

	argc = 0;
	perform_expansion(msh, &cmd);
	while (cmd->arg && cmd->arg[argc])
		argc++;
	*argv = malloc(sizeof(char *) * (argc + 2));
	if (!(*argv))
		return ;
	(*argv)[0] = cmd->cmd;
	j = 0;
	while (j < argc)
	{
		(*argv)[j + 1] = cmd->arg[j];
		j++;
	}
	(*argv)[argc + 1] = NULL;
}

void	cleanup_builtin(int saved_out, int saved_err)
{
	dup2(saved_out, STDOUT_FILENO);
	dup2(saved_err, STDERR_FILENO);
	close(saved_out);
	close(saved_err);
}
