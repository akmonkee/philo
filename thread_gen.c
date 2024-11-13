/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:07:41 by msisto            #+#    #+#             */
/*   Updated: 2024/11/13 10:58:41 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void	*input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_check(philo))
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (input);
}

int	thread_create(t_table *table, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitor_routine, table->philos) != 0)
		destory_all(table, forks);
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_routine, &table->philos[i]) != 0)
			destory_all(table, forks);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		destory_all(table, forks);
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			destory_all(table, forks);
		i++;
	}
	return (0);
}
