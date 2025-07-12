/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 11:05:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *msg, int error)
{
	printf("%s\n", msg);
	return (error);
}

int	atoi_safe(const char *str)
{
	int	i;
	int	digit;
	int	nb;

	i = 0;
	nb = 0;
	if (str[i] == '-')
		return (ft_error("Negative numbers not allowed", 0));
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_error("Only digits are allowed", 0));
		digit = str[i] - '0';
		if (nb > (INT_MAX - digit) / 10)
			return (ft_error("Error: Overflow", 0));
		nb = nb * 10 + digit;
		i++;
	}
	return (nb);
}

void	ft_usleep(unsigned long time_in_ms)
{
	unsigned long	start;
	unsigned long	current;

	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= time_in_ms)
			break ;
		if (time_in_ms - (current - start) > 10)
			usleep(5000);
		else
			usleep(100);
	}
}

unsigned long	get_time(void)
{
	struct timeval		tv;
	unsigned long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
