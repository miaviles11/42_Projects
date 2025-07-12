/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:27:17 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 10:51:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philosophers)
	{
		pthread_mutex_destroy(&rules->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < rules->nb_philosophers)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->alive_lock);
	pthread_mutex_destroy(&rules->finished_lock);
	free(rules->philos);
	free(rules->forks);
}
