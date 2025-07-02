/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/01 18:56:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (get_simulation_state(philo->rules))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
void	wait_threads(t_rules *rules)
{
	int	i = 0;

	while (i < rules->nb_philosophers)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
}

void	start_threads(t_rules *rules)
{
	int	i;
	int	res;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		res = pthread_create(&rules->philos[i].thread, NULL,
			routine, &rules->philos[i]);
		if (res != 0)
			ft_error("Error creating threads", 1);
		usleep(100);
		i++;
	}
}