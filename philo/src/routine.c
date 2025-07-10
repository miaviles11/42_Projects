/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/10 21:50:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*single_philosopher(t_philo *philo)
{
	print_state(philo, "has taken a fork");
	while (get_simulation_state(philo->rules))
		usleep(100);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	if (philo->rules->nb_philosophers == 1)
		return (single_philosopher(philo));
	while (get_simulation_state(philo->rules))
	{
		take_forks(philo);
		if (!get_simulation_state(philo->rules))
		{
			release_forks(philo);
			break ;
		}
		eat(philo);
		release_forks(philo);
		sleep_philo(philo);
		think_philo(philo);
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
