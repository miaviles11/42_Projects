/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:18:52 by miaviles          #+#    #+#             */
/*   Updated: 2024/12/20 15:56:46 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static int				bit_count = 0;
	static unsigned char	c = 0;

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
}

int	main(void)
{
	ft_printf("Servidor iniciado. PID: %d\n", getpid());
	ft_printf("Esperando mensajes...\n");
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
