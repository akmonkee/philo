/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:04:49 by msisto            #+#    #+#             */
/*   Updated: 2024/10/30 14:20:37 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct philo_s
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}		philo_t;

typedef struct table_s
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	philo_t			*philos;
}		table_t;

//input check//
void	no_alpha(int ac, char **av);
//struct init//
void	table_builder(table_t *table, philo_t *philos);
void	fork_maker(pthread_mutex_t *forks, int num);
void	arg_init(philo_t *philos, char **av);
void	philo_maker(philo_t *philos, table_t *table, pthread_mutex_t *forks, char **av);
//utils//
void	print_status(char *str, philo_t *philo, int id);
void	destory_all(table_t *table, pthread_mutex_t *forks);
size_t	get_current_time(void);
int		ft_atoi(char *str);
int		ft_usleep(size_t milliseconds);
//thread//
int		dead_lock(philo_t *philo);
void	*philo_routine(void	*input);
int		thread_create(table_t *table, pthread_mutex_t *forks);
//philo actions//
void	sleeping(philo_t *philo);
void	think(philo_t *philo);
void	eat(philo_t *philo);
//monitor actions//
int		philo_dead_check(philo_t *philo);
int		check_for_deads(philo_t *philos);
int		all_have_eaten(philo_t	*philos);
void	*monitor_routine(void *input);

#endif
