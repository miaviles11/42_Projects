/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:46:21 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/01 19:00:06 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	while (rules->all_alive)
	{
		i = 0;
		while (i < rules->nb_philosophers && rules->all_alive)
		{
			if (get_time() - rules->philos[i].last_meal > rules->time_to_die)
			{
				pthread_mutex_lock(&rules->print_lock);
				if (rules->all_alive)
				{
					rules->all_alive = 0;
					printf("%ld %d died\n", get_time() - rules->start_time,
						rules->philos[i].id);
				}
				pthread_mutex_unlock(&rules->print_lock);
				break;
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_rules	*rules;
	int		i;
	int		done;

	rules = (t_rules *)arg;
	if (rules->must_eat == -1)
		return (NULL);
	while (rules->all_alive)
	{
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
		if (done == rules->nb_philosophers)
		{
			pthread_mutex_lock(&rules->print_lock);
			rules->all_alive = 0;
			pthread_mutex_unlock(&rules->print_lock);
			break ;
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

	parse_args(argc, argv, &rules);
	init_simulation(&rules);
	start_threads(&rules);
	pthread_create(&monitor_thread, NULL, monitor, &rules);
	if (rules.must_eat != -1)
		pthread_create(&meal_thread, NULL, monitor_meals, &rules);
	pthread_join(monitor_thread, NULL);
	if (rules.must_eat != -1)
		pthread_join(meal_thread, NULL);
	wait_threads(&rules);
	if (rules.must_eat != -1 && rules.all_alive == 0)
		printf("Todos los filósofos han comido lo suficiente 🍝\n");
	cleanup(&rules);
	return (0);
}
