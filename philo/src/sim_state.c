/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 18:34:31 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 10:49:02 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_simulation_state(t_rules *rules, int value)
{
	pthread_mutex_lock(&rules->alive_lock);
	rules->all_alive = value;
	pthread_mutex_unlock(&rules->alive_lock);
}

int	get_simulation_state(t_rules *rules)
{
	int	state;

	pthread_mutex_lock(&rules->alive_lock);
	state = rules->all_alive;
	pthread_mutex_unlock(&rules->alive_lock);
	return (state);
}
