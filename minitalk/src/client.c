/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:05:19 by miaviles          #+#    #+#             */
/*   Updated: 2025/02/26 11:29:24 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

static int	validate_pid(char *pid_str)
{
	int	i;

	i = 0;
	while (pid_str[i])
	{
		if (!ft_isdigit(pid_str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	send_char(int pid, unsigned char c)
{
	int		bit;
	long	time;

	bit = 8;
	time = 0;
	while (bit--)
	{
		g_ack_received = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (!g_ack_received && time < TIMEOUT)
			time++;
		if (time == TIMEOUT)
		{
			ft_putstr_fd("\x1b[31mERROR, INCORRECT PID!\x1b[0m\n", 2);
			exit (1);
		}
	}
}

static void	send_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		send_char(pid, message[i]);
		i++;
	}
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !ft_strlen(argv[2]) || !validate_pid(argv[1]))
	{
		ft_putstr_fd("\x1b[31mERROR!\x1b[0m\n", 2);
		ft_putstr_fd("Formato: ./client [server_pid] \"Mensaje\"\n", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ack_handler);
	ft_printf("Enviando mensaje al servidor (PID: %d)...\n", pid);
	send_message(pid, argv[2]);
	ft_printf("Mensaje enviado correctamente.\n");
	return (0);
}
