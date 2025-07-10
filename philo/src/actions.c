/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:27:07 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/10 22:39:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleep_philo(t_philo *philo)
{
	print_state(philo, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep);
}

void	think_philo(t_philo *philo)
{
	long	cycle;

	print_state(philo, "is thinking");
	cycle = philo->rules->time_to_eat + philo->rules->time_to_sleep;
	if (philo->rules->time_to_die - cycle < 10)
		return ;
	usleep((philo->id * 50) % 200 + 100);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void take_forks(t_philo *philo)
{
	if (philo->rules->nb_philosophers % 2 == 1 && 
			philo->id == philo->rules->nb_philosophers)
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_state(philo, "has taken a fork");
	}
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_state(philo, "is eating");
	ft_usleep(philo->rules->time_to_eat);
}
