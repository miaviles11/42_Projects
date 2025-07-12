/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:19:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/12 10:49:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				nb_philosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				must_eat;
	long			start_time;
	int				all_alive;
	int				finished;
	pthread_mutex_t	alive_lock;
	pthread_mutex_t	finished_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	struct s_philo	*philos;
}	t_rules;

/*actions.c*/
void			sleep_and_think(t_philo *philo);
void			release_forks(t_philo *philo);
void			take_forks(t_philo *philo);
void			eat(t_philo *philo);

/*clean.c*/
void			cleanup(t_rules *rules);

/*init.c*/
int				init_philos(t_rules *rules);
int				init_simulation(t_rules *rules);

/*logs.c*/
void			print_state(t_philo *philo, char *msg);
void			print_state_died(t_philo *philo);

/*routine.c*/
void			*routine(void *arg);
void			wait_threads(t_rules *rules);
int				start_threads(t_rules *rules);

/*main.c*/
void			*monitor(void *arg);
void			*monitor_meals(void *arg);
int				main(int argc, char **argv);

/*parse.c*/
int				parse_args(int argc, char **argv, t_rules *rules);

/*sim_state*/
void			set_simulation_state(t_rules *rules, int value);
int				get_simulation_state(t_rules *rules);

/*utils.c*/
int				ft_error(char *msg, int error);
int				atoi_safe(const char *str);
void			ft_usleep(unsigned long time_in_ms);
unsigned long	get_time(void);

#endif