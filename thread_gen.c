/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:07:41 by msisto            #+#    #+#             */
/*   Updated: 2024/11/11 10:36:09 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(philo_t *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void	*input)
{
	philo_t	*philo;

	philo = (philo_t *)input;
	if (philo->id % 2 == 0)
		ft_usleep(5);
	while (!dead_check(philo))
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (input);
}

int	thread_create(table_t *table, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitor_routine, table->philos) != 0)
		destory_all(table, forks);
	while (i < table->philos[0].num_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine, &table->philos[i]) != 0)
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
