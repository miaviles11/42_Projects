/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:18:52 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/27 15:53:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	c = 0;

	(void)context;
	if (info->si_pid == 0)
		return ;
	c |= (sig == SIGUSR2);
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			ft_printf("\n[INFO] Mensaje completo recibido. Esperando más...\n");
		else
			ft_putchar_fd(c, 1);
		bit_count = 0;
		c = 0;
	}
	else
		c <<= 1;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Servidor iniciado. PID: %d\n", getpid());
	ft_printf("Esperando mensajes...\n");
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
