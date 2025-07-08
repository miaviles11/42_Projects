/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:19:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/07/08 18:25:19 by miaviles         ###   ########.fr       */
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

typedef struct	s_rules t_rules;

typedef struct	s_philo
{
	int				id;                   // ID único (del 1 al n)
	int				meals_eaten;          // Contador de comidas realizadas
	long			last_meal;            // Marca de tiempo de la última comida
	pthread_t		thread;               // Hilo del filósofo
	pthread_mutex_t	*left_fork;           // Puntero a su tenedor izquierdo
	pthread_mutex_t	*right_fork;          // Puntero a su tenedor derecho
	pthread_mutex_t	meal_lock;
	t_rules			*rules;               // Acceso a las reglas/globales
}	t_philo;

typedef struct s_rules
{
	int				nb_philosophers;      // Total de filósofos
	unsigned long	time_to_die;          // Tiempo antes de morir sin comer (ms)
	unsigned long	time_to_eat;          // Tiempo que tarda en comer (ms)
	unsigned long	time_to_sleep;        // Tiempo que duerme tras comer (ms)
	int				must_eat;             // Nº de veces que debe comer cada uno (-1 si no se especifica)
	long			start_time;           // Marca de tiempo de inicio de la simulación
	int				all_alive;            // Bandera de control de vida (1 = sí, 0 = no)
	pthread_mutex_t	alive_lock;			  // protege el aceso a all_alive
	pthread_mutex_t	*forks;               // Array de mutexes (uno por tenedor)
	pthread_mutex_t	print_lock;           // Mutex para imprimir sin mezclar mensajes
	struct s_philo	*philos;              // Array de filósofos
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