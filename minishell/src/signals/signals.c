/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 12:48:40 by carlsanc          #+#    #+#             */
/*   Updated: 2025/06/08 12:48:40 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile sig_atomic_t	g_interactive;

void	handle_parent_signal(int sign)
{
	if (sign == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (g_interactive)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sign == SIGQUIT)
	{
		if (!g_interactive)
		{
			write(STDERR_FILENO, "Quit: 3\n", 8);
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	handle_child_signal(int sign)
{
	if (sign == SIGINT)
		_exit(130);
	else if (sign == SIGQUIT)
		_exit(131);
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_parent_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGTERM, &sa, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_child_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
