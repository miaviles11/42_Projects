/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/08 18:24:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->rules->time_to_eat / 2);
	if (philo->rules->nb_philosophers == 1)
	{
		print_state(philo, "has taken a fork");
		while (get_simulation_state(philo->rules))
			usleep(100);
		return (NULL);
	}
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
	int	i;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		pthread_join(rules->philos[i].thread, NULL);
		i++;
	}
}

int	start_threads(t_rules *rules)
{
	int	i;
	int	res;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		res = pthread_create(&rules->philos[i].thread, NULL,
				routine, &rules->philos[i]);
		if (res != 0)
			return (ft_error("Error creating threads", 1));
		i++;
	}
	return (0);
}
