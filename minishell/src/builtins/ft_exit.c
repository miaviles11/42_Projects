/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:45:05 by miaviles          #+#    #+#             */
/*   Updated: 2025/05/05 15:45:05 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	minishell_exit(t_msh *msh)
{
	int		status;
	t_cmd	*cmd;

	cmd = msh->cmd;
	if (cmd->arg && cmd->arg[1])
	{
		if (!is_numeric(cmd->arg[1]))
		{
			ft_printf("exit: %s: numeric argument required\n", cmd->arg[1]);
			exit(255);
		}
		if (cmd->arg[2])
		{
			ft_printf("exit: too many arguments\n");
			return (1);
		}
		status = ft_atoi(cmd->arg[1]);
		exit(status);
	}
	else
		exit(0);
	return (0);
}
