/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:21 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 10:54:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_philosopher_death(t_rules *rules, int i)
{
	unsigned long	last_meal_time;
	unsigned long	current_time;

	pthread_mutex_lock(&rules->philos[i].meal_lock);
	last_meal_time = rules->philos[i].last_meal;
	pthread_mutex_unlock(&rules->philos[i].meal_lock);
	current_time = get_time();
	if (current_time - last_meal_time >= rules->time_to_die)
	{
		pthread_mutex_lock(&rules->finished_lock);
		if (!rules->finished)
		{
			rules->finished = 1;
			pthread_mutex_unlock(&rules->finished_lock);
			pthread_mutex_lock(&rules->alive_lock);
			rules->all_alive = 0;
			pthread_mutex_unlock(&rules->alive_lock);
			print_state_died(&rules->philos[i]);
			return (1);
		}
		pthread_mutex_unlock(&rules->finished_lock);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (get_simulation_state(rules))
	{
		i = 0;
		while (i < rules->nb_philosophers && get_simulation_state(rules))
		{
			if (check_philosopher_death(rules, i))
			{
				set_simulation_state(rules, 0);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static int	check_all_philosophers_ate(t_rules *rules)
{
	int	i;
	int	done;

	done = 0;
	i = 0;
	while (i < rules->nb_philosophers)
	{
		pthread_mutex_lock(&rules->philos[i].meal_lock);
		if (rules->philos[i].meals_eaten >= rules->must_eat)
			done++;
		pthread_mutex_unlock(&rules->philos[i].meal_lock);
		i++;
	}
	return (done);
}

void	*monitor_meals(void *arg)
{
	t_rules	*rules;
	int		done;

	rules = (t_rules *)arg;
	if (rules->must_eat == -1)
		return (NULL);
	while (get_simulation_state(rules))
	{
		done = check_all_philosophers_ate(rules);
		if (done == rules->nb_philosophers)
		{
			pthread_mutex_lock(&rules->finished_lock);
			if (!rules->finished)
			{
				rules->finished = 1;
				pthread_mutex_unlock(&rules->finished_lock);
				set_simulation_state(rules, 0);
				break ;
			}
			pthread_mutex_unlock(&rules->finished_lock);
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	monitor_thread;
	pthread_t	meal_thread;

	if (parse_args(argc, argv, &rules))
		return (1);
	if (rules.must_eat == 0)
		return (1);
	if (init_simulation(&rules))
		return (1);
	if (start_threads(&rules))
		return (1);
	pthread_create(&monitor_thread, NULL, monitor, &rules);
	if (rules.must_eat != -1)
		pthread_create(&meal_thread, NULL, monitor_meals, &rules);
	pthread_join(monitor_thread, NULL);
	if (rules.must_eat != -1)
		pthread_join(meal_thread, NULL);
	wait_threads(&rules);
	cleanup(&rules);
	return (0);
}
