/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:51:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/01 17:50:05 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_state(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print_lock);
	if (philo->rules->all_alive)
	{
		timestamp = get_time() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->rules->print_lock);
}
