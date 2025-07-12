/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:21:12 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/10 16:36:04 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_args(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
		return (ft_error("./philo nº_of_philosophers time_to_die time_to_eat"
				" time_to_sleep [nº_of_times_each_philosopher_must_eat]", 1));
	rules->nb_philosophers = atoi_safe(argv[1]);
	if (rules->nb_philosophers < 1)
		return (ft_error("one or more philosophers needed", 1));
	if (rules->nb_philosophers > 200)
		return (ft_error("200 philosophers max", 1));
	rules->time_to_die = atoi_safe(argv[2]);
	if (rules->time_to_die <= 0)
		return (ft_error("time to die must be more than 0", 1));
	rules->time_to_eat = atoi_safe(argv[3]);
	if (rules->time_to_eat <= 0)
		return (ft_error("time to eat must be more than 0", 1));
	rules->time_to_sleep = atoi_safe(argv[4]);
	if (rules->time_to_sleep <= 0)
		return (ft_error("time to sleep must be more than 0", 1));
	rules->must_eat = -1;
	if (argc == 6)
	{
		rules->must_eat = atoi_safe(argv[5]);
		if (rules->must_eat < 0)
			return (ft_error("must_eat must be 0 or more", 1));
	}
	return (0);
}
