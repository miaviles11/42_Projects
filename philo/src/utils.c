/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/03 18:35:10 by miaviles         ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (ft_error("Only digits are allowed", -1));
		digit = str[i] - '0';
		if (nb > (INT_MAX - digit) / 10)
			return (ft_error("Error: Overflow", -1));
		nb = nb * 10 + digit;
		i++;
	}
	return (nb);
}

void	ft_usleep(unsigned long time_in_ms)
{
	unsigned long	start;

	start = get_time();
	while (get_time() - start < time_in_ms)
		usleep(100);
}

unsigned long	get_time(void)
{
	struct timeval		tv;
	unsigned long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}
