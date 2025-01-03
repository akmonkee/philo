/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:01:40 by akmonke           #+#    #+#             */
/*   Updated: 2024/11/18 15:24:37 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(philo_t *philo)
{
	print_status("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
}

void	think(philo_t *philo)
{
	print_status("is thinking", philo, philo->id);
}

void	eat(philo_t *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->r_fork);
	}
	pthread_mutex_lock(philo->l_fork);
	print_status("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	print_status("is eating", philo, philo->id);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
