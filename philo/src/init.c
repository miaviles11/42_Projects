/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:04 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 11:04:09 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_philos(t_rules *rules)
{
	int	i;
	int	res;

	i = 0;
	rules->start_time = get_time();
	while (i < rules->nb_philosophers)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].rules = rules;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork
			= &rules->forks[(i + 1) % rules->nb_philosophers];
		rules->philos[i].meals_eaten = 0;
		rules->philos[i].last_meal = rules->start_time;
		res = pthread_mutex_init(&rules->philos[i].meal_lock, NULL);
		if (res != 0)
			return (ft_error("Error initializing meal_lock", 1));
		i++;
	}
	return (0);
}

static int	init_forks(t_rules *rules)
{
	int	i;
	int	res;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		res = pthread_mutex_init(&rules->forks[i++], NULL);
		if (res != 0)
			return (ft_error("Error initializing forks", 1));
	}
	return (0);
}

static int	init_global_mutexes(t_rules *rules)
{
	int	res;

	res = pthread_mutex_init(&rules->print_lock, NULL);
	if (res != 0)
		return (ft_error("Error initializing print_lock", 1));
	res = pthread_mutex_init(&rules->alive_lock, NULL);
	if (res != 0)
		return (ft_error("Error initializing alive_lock", 1));
	res = pthread_mutex_init(&rules->finished_lock, NULL);
	if (res != 0)
		return (ft_error("Error initializing finished_lock", 1));
	return (0);
}

int	init_simulation(t_rules *rules)
{
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philosophers);
	if (!rules->forks)
		return (ft_error("Error allocating forks", 1));
	rules->philos = malloc(sizeof(t_philo) * rules->nb_philosophers);
	if (!rules->philos)
	{
		free(rules->forks);
		return (ft_error("Error allocating philosophers", 1));
	}
	if (init_forks(rules))
		return (1);
	if (init_global_mutexes(rules))
		return (1);
	rules->all_alive = 1;
	rules->finished = 0;
	if (init_philos(rules))
		return (1);
	return (0);
}
