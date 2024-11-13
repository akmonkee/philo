/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:17:15 by msisto            #+#    #+#             */
/*   Updated: 2024/11/13 10:47:19 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal >= philo->time_to_die))
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_for_deads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philo_dead_check(&philos[i]) == 1)
		{
			print_status("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[i].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[i].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_have_eaten(t_philo	*philos)
{
	int	i;
	int	ate_all;

	i = 0;
	ate_all = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			ate_all++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (ate_all == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *input)
{
	t_philo	*philos;

	philos = (t_philo *)input;
	while (1)
		if (all_have_eaten(philos) == 1 || check_for_deads(philos) == 1)
			break ;
	return (input);
}
