/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:51:19 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:51:19 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_extra_arguments(char **argv)
{
	ft_printf("Error: minishell no acepta argumentos adicionales\n");
	ft_printf("Uso: %s\n", argv[0]);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*shell;

	if (argc != 1)
		handle_extra_arguments(argv);
	shell = initialize_shell(envp);
	if (!shell)
		return (1);
	shell->error_value = 0;
	setup_signals();
	run_shell_loop(shell);
	cleanup_shell(shell);
	return (shell->error_value);
}
