/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:51:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/08 18:24:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_lock);
	pthread_mutex_lock(&philo->rules->alive_lock);
	if (philo->rules->all_alive)
	{
		timestamp = get_time() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->rules->alive_lock);
	pthread_mutex_unlock(&philo->rules->print_lock);
}

void	print_state_died(t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_lock);
	timestamp = get_time() - philo->rules->start_time;
	printf("%ld %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->rules->print_lock);
}
